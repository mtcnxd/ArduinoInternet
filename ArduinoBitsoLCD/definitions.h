#include <Arduino.h>

const char* ssid = "SMARTHOME";
const char* password = "100%smart";

String url = "https://api.bitso.com/v3/ticker/?book=";
String coin[] = {"bch_mxn", "bat_mxn", "ltc_mxn"};

int timeUpdate = 5000;
