
#include <WiFi.h>
#include "conected.h"
#include "conecting.h"
#include "diconected.h"
//======================================
const char* ssid     = "ali"; // Change this to your WiFi SSID
const char* password = "1234567890"; // Change this to your WiFi password
#define LED_BUILTIN 4
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
TaskHandle_t myTaskHandle = NULL;
TaskHandle_t myTaskHandle2 = NULL;
TaskHandle_t myTaskHandle3 = NULL;
//=============================




void setup()
{
    Serial.begin(115200);
      // initialize LED digital pin as an output.
     pinMode(LED_BUILTIN, OUTPUT);

    // We start by connecting to a WiFi network



    WiFi.begin(ssid, password);
    xTaskCreate(conected, "conected", 4096, NULL, 10, &myTaskHandle);
    xTaskCreate(conecting, "conecting", 4096, NULL,10, &myTaskHandle2);
    xTaskCreate(diconected, "diconected", 4096, NULL,10, &myTaskHandle3);
    vTaskSuspend(myTaskHandle);
    vTaskSuspend(myTaskHandle2);
    vTaskSuspend(myTaskHandle3);
   /* while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }*/

}
int status=0;
void loop(){
  status= WiFi.status();
  if(status==WL_DISCONNECTED) {
    vTaskSuspend(myTaskHandle);
   vTaskSuspend(myTaskHandle2);
    vTaskResume(myTaskHandle3);


  }else if(status==WL_CONNECTED) {
   vTaskResume(myTaskHandle);
   vTaskSuspend(myTaskHandle2);
    vTaskSuspend(myTaskHandle3);


  }else {
  vTaskSuspend(myTaskHandle);
   vTaskResume(myTaskHandle2);
    vTaskSuspend(myTaskHandle3);
    

  }
}