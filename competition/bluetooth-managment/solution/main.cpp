#include "BluetoothSerial.h"
#include "esp_bt_device.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"

#define LED_PIN 2

BluetoothSerial SerialBT;
bool deviceFound = false;
String targetDevice = "TARGET_DEVICE_NAME";

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32");
  esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE_DISCOVERABLE);
  esp_bt_gap_register_callback(esp_bt_gap_cb);
}

void loop() {
  if (deviceFound) {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
  } else {
    digitalWrite(LED_PIN, LOW);
    esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0);
    delay(10000);
  }
}

void esp_bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {
  if (event == ESP_BT_GAP_DISC_RES_EVT) {
    char bda_str[18];
    sprintf(bda_str, "%02X:%02X:%02X:%02X:%02X:%02X",
            param->disc_res.bda[0], param->disc_res.bda[1], param->disc_res.bda[2],
            param->disc_res.bda[3], param->disc_res.bda[4], param->disc_res.bda[5]);
    String deviceAddress = String(bda_str);
    if (deviceAddress == targetDevice) {
      deviceFound = true;
      esp_bt_gap_cancel_discovery();
    }
  }
}
