#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

void setup()
{
  Serial.begin(115200);
  WiFiManager wifiManager;
  // Descomentar para resetear configuración
  //wifiManager.resetSettings();
  wifiManager.autoConnect("ESP8266");
  Serial.println("Ya estás conectado");
}

void loop()
{
}
