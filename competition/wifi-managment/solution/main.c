#include <ESPping.h>
#include <ping.h>
#include <WiFi.h>
#include <ESP8266WiFi.h>

const char* ssid = "test"; // wifi name
const char* password = "12345678"; // password
unsigned int timestart = 0;

void setup() {

  Serial.begin (115200);
  delay(10);
  Serial.println("");
  Serial.println("scan start");
  Serial.println("Searching The Network");
  pinMode(12 ,OUTPUT);
  WiFi.mode(WIFI_STA);

}

void loop() {
  
  not_connected ();
  
  WiFi.begin (ssid, password);

  try_to_connect ();

  check_internet ();

}

void not_connected (void)
{

for ( int i = 0; i < 5 ; i++ )
  {
  digitalWrite(12, 1);
  delay(1000);
  digitalWrite(12, 0);
  delay(1000);
  }

}

void try_to_connect (void)
{

while (WiFi.status() != WL_CONNECTED)
  {   
    
    for ( int i = 0; i < 5 ; i++ )
    {
      digitalWrite(12, 1);
      delay(2000);
      digitalWrite(12, 0);
      delay(2000);
      Serial.print('.');
      timestart++;
    }

    if (timestart >= 5) 
    {
      Serial.println("");
      Serial.println("Unable To Detect Wi-Fi Network");
      Serial.println("Resetting ESP32 ...");
      //delay(5000);
      ESP.restart(); // ریست کردن ESP32
    }
  }

}

void check_internet (void)
{

while (WiFi.status() == WL_CONNECTED)
  {
    bool success = Ping.ping("www.google.com");

   if (success)
   {
     Serial.println("Connected to the internet");
      for ( int i = 0; i<50 ; i++ )
     {
       digitalWrite(12, 1);
       delay(5000);
       digitalWrite(12, 0);
       delay(5000);
      }
    } else 
   {
     Serial.println("Not connected to the internet");
     for ( int i = 0; i < 5 ; i++ )
      {
        digitalWrite(12, 1);
        delay(3000);
        digitalWrite(12, 0);
        delay(3000);
      }
    }
  }

}
