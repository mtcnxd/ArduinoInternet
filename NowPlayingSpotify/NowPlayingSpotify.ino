#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>

const char* ssid = "SMARTHOME";
const char* password = "100%smart";
String url = "https://api.spotify.com/v1/me/player/currently-playing";
String Bearer = "BQAEQ7oCqei6fzJTd6RL-I9ZlYpjmAav2hiUBEGeb5-ZmSqXm8ltucOvFCxO7s44rGE3RKjA4Yp-W339dvYBuTxoXouumdxbnaxbwErzzq-9hdy6Pnju8PG53ysxaQSAlNwbFCHa292d9CdaG4VGg0JKAmLcF1CJKqcoqzvwZKM";
String authorization = "Bearer " + Bearer;

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(9600);
  setupWiFi();

}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    std::unique_ptr<BearSSL::WiFiClientSecure> client (new BearSSL::WiFiClientSecure);

    client->setInsecure();

    HTTPClient http;
    http.begin(*client, url);
    http.addHeader("Authorization", "Bearer " + Bearer);
    int httpResponseCode = http.GET();
    String payload = http.getString();

    const size_t capacity = 2 * JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(2) + 6 * JSON_OBJECT_SIZE(1) + 3 * JSON_OBJECT_SIZE(2) + 2 * JSON_OBJECT_SIZE(4) + 2 * JSON_OBJECT_SIZE(5) + 4 * JSON_OBJECT_SIZE(8) + 550;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, payload);
    JsonObject object = doc.as<JsonObject>();

    String jsonArtist = object["item"]["album"]["artists"];

    Serial.println(jsonArtist);

    deserializeJson(doc, jsonArtist);
    JsonObject artist = doc.as<JsonObject>();

    Serial.println((String) artist);

    delay(5000);
  }
}

void setupWiFi() {
  delay(100);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  randomSeed(micros());

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
