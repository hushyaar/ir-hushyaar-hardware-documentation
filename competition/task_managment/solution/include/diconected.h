#include "Arduino.h"
#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
void diconected(void *arg)
{
  for( ;; ){
       // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  vTaskDelay(1000/ portTICK_RATE_MS);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
  vTaskDelay(1000/ portTICK_RATE_MS);
  Serial.println("diconected");
  }
}
