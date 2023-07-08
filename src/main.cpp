#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "wifi_secrets.h"

#include "ESPAsyncTCP.h"
#include "ESPAsyncWebServer.h"

#define PIN_LED 16
#define PIN_RELAY 5

enum RelayState { UNDEF, ENABLED, DISABLED };

AsyncWebServer server(80);
const char* API_PARAM_RELAY_ACTIVATION = "relayActivation";
const char* API_VALUE_RELAY_ENABLED = "true";
const char* API_VALUE_RELAY_DISABLED = "false";
const char* API_REPONSE_MIME_TYPE = "application/json";
const char* API_REPONSE_RELAY_DISABLED = "{relayActivation=false}";
const char* API_REPONSE_RELAY_ENABLED = "{relayActivation=true}";
const char* API_REPONSE_MISSING_PARAM = R"({
  "error": {
    "message": "missing parameter",
    "parameter": "relayActivation"
})";
const char* API_REPONSE_WRONG_PARAM = R"({
  "error": {
    "message": "wrong parameter value",
    "parameter": "relayActivation"
})";

RelayState relayActivation = DISABLED;

bool blinkLED(int);
bool activateRelay(bool);
RelayState evaluateRelayState(String);

void notFound(AsyncWebServerRequest *request) {
    request->send(404);
}

void setup() {
  // setup serial port
  Serial.begin(115200);
  Serial.println("Serial port configured!");

  // setup LED
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // setup Relay
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);

  // setup WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // setup API
  //FIXME: timeout when receiving a POST request with wrong param name
  //FIXME: timeout when receiving a POST request without param
  server.on("/relay", HTTP_POST, [](AsyncWebServerRequest *request){
    String paramRelayAction;

    if (request->hasParam(API_PARAM_RELAY_ACTIVATION),false) {
      request->send(400, API_REPONSE_MIME_TYPE, API_REPONSE_MISSING_PARAM);
    }

    paramRelayAction = request->getParam(API_PARAM_RELAY_ACTIVATION, true)->value();
  
    switch (evaluateRelayState(paramRelayAction)) {
      case DISABLED:
        activateRelay(false);
        request->send(200, API_REPONSE_MIME_TYPE, API_REPONSE_RELAY_DISABLED);
        break;
      case ENABLED:
        activateRelay(true);
        request->send(200, API_REPONSE_MIME_TYPE, API_REPONSE_RELAY_ENABLED);
        break;
      default:
        request->send(400, API_REPONSE_MIME_TYPE, API_REPONSE_WRONG_PARAM);
        break;
    }
  });

  server.on("/relay", HTTP_GET, [](AsyncWebServerRequest *request){
    switch(relayActivation) {
      case ENABLED:
        request->send(200, API_REPONSE_MIME_TYPE, API_REPONSE_RELAY_ENABLED);
        break;
      case DISABLED:
        request->send(200, API_REPONSE_MIME_TYPE, API_REPONSE_RELAY_DISABLED);
        break;
      default:
        request->send(500);
        break;
    }
  });

  server.onNotFound(notFound);

  server.begin();
}

void loop() {
}

bool blinkLED(int delayValue) {
  if(delay > 0) {
    digitalWrite(PIN_LED, HIGH);
    Serial.println("LED turned ON!");
    delay(delayValue);
    digitalWrite(PIN_LED, LOW);
    Serial.println("LED turned OFF!");
    return true;
  }
  return false;
}

bool activateRelay(bool activate) {
  if(activate){
    digitalWrite(PIN_RELAY, HIGH);
    relayActivation = ENABLED;
    Serial.println("Relay turned ON!");
    return true;
  }
  
  digitalWrite(PIN_RELAY, LOW);
  relayActivation = DISABLED;
  Serial.println("Relay turned OFF!");
  return false;
}

RelayState evaluateRelayState(String evaluated){
  if (evaluated == API_VALUE_RELAY_ENABLED) {
    return ENABLED;
  } 
  if (evaluated == API_VALUE_RELAY_DISABLED) {
    return DISABLED;
  } 
  return UNDEF;
}
