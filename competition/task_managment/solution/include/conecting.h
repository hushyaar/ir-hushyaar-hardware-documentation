#include "Arduino.h"
#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
#define LED_BUILTIN 4

void conecting(void *arg)
{ for( ;; ){
       // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  vTaskDelay(2000/ portTICK_RATE_MS);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
  vTaskDelay(2000/ portTICK_RATE_MS);
  Serial.println("conecting");
}
}