#include <WiFi.h>
#include <HTTPClient.h>
#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"

// WiFi credentials
const char* ssid = "Infinix Hot 11";
const char* password = "F@1234568";

// Google Web App URL
const char* googleScriptURL = "https://script.google.com/macros/s/AKfycbyLG7gmdL9R48JeNgS1Qy74QgSpb9FhrPwi2rQWJZyel2OZ7WsVNdD-Ee1NtVY_mWAIwg/exec";

// Student records
struct Student {
  String mac;
  String name;
  String rollNo;
};

// Student list
Student students[] = {
  {"88:9F:6F:67:7D:89", "Ayesha", "22"},
  {"98:09:cf:89:2d:e9", "Hafsa",  "6"},
  {"d4:63:de:fc:0e:ef", "Amaila", "12"},
  {"F4:5C:89:77:88:99", "Fakhra", "10"},
  {"D8:BF:C0:DE:AD:BE", "Diya",   "30"},
  {"E0:94:67:FE:DC:BA", "Nimra",  "25"}
};

const int studentCount = sizeof(students) / sizeof(students[0]);

BluetoothSerial SerialBT;
bool scanned = false;

// Function to send student info to Google Sheet
void sendToGoogleSheet(const String& name, const String& rollNo) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(googleScriptURL) + "?name=" + name + "&roll=" + rollNo;

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("✅ Marked present: " + name + " (" + rollNo + ")");
    } else {
      Serial.println("❌ HTTP error code: " + String(httpCode));
    }

    http.end();
  } else {
    Serial.println("❌ WiFi not connected.");
  }
}

// Bluetooth scan callback
void btCallback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {
  if (event == ESP_BT_GAP_DISC_RES_EVT) {
    char bda_str[18];
    sprintf(bda_str, "%02X:%02X:%02X:%02X:%02X:%02X",
            param->disc_res.bda[0], param->disc_res.bda[1], param->disc_res.bda[2],
            param->disc_res.bda[3], param->disc_res.bda[4], param->disc_res.bda[5]);

    String foundMAC = String(bda_str);
    Serial.println("🔍 Found Device: " + foundMAC);

    for (int i = 0; i < studentCount; i++) {
      if (foundMAC.equalsIgnoreCase(students[i].mac)) {
        Serial.println("🎯 Recognized: " + students[i].name);
        sendToGoogleSheet(students[i].name, students[i].rollNo);
      }
    }
  } else if (event == ESP_BT_GAP_DISC_STATE_CHANGED_EVT) {
    if (param->disc_st_chg.state == ESP_BT_GAP_DISCOVERY_STOPPED) {
      Serial.println("🔁 Scan complete.");
      scanned = true;
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected.");

  // Initialize Bluetooth (no need for low-level ESP-IDF setup)
  if (!btStart()) {
    Serial.println("❌ Bluetooth start failed.");
    return;
  }

  esp_bt_gap_register_callback(btCallback);

  Serial.println("✅ Bluetooth initialized. Ready to scan.");
}

void loop() {
  Serial.println("\n📡 Starting Bluetooth scan...");
  scanned = false;
  esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0);

  while (!scanned) {
    delay(500);
  }

  Serial.println("⏳ Waiting 1 minute before next scan...\n");
  delay(60000);  // Wait 1 minute
}
