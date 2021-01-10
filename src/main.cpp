#include <Arduino.h>
#include <ArduinoJson.h>


#include "Ubidots.h"

const char* UBIDOTS_TOKEN = "BBFF-GQKrdvNvAZiFZ3o0Tj6J5cneiHNPde";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Crazy Engineer's"; // Put here your Wi-Fi SSID
const char* WIFI_PASS = "Alita:Battle Angel1"; // Put here your Wi-Fi password

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

StaticJsonDocument<200> doc;
void send_messages();
void setup() {
  Serial.begin(9600);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  ubidots.setDebug(true);
}

void loop() {

  send_messages();
  delay(5000);
}

void send_messages(){
  String input = "{\"org_dis\":0,\"inorg_dis\":4, \"Gas0\":40, \"Gas1\":50, \"dis\":60,\"User1\":70, \"User2\":80}";

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, input);
  JsonObject obj = doc.as<JsonObject>();

  // Send some values
  double org_dis = obj["org_dis"];
  double inorg_dis = obj["inorg_dis"];
  double Gas0 = obj["Gas0"];
  double Gas1 = obj["Gas1"];
  double dis = obj["dis"];
  double User1 = obj["User1"];
  double User2 = obj["User2"];


  if(Serial.available()>0){
    input = Serial.readString();

    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
    // Send some values
    org_dis = obj["org_dis"];
    inorg_dis = obj["inorg_dis"];
    Gas0 = obj["Gas0"];
    Gas1 = obj["Gas1"];
    dis = obj["dis"];
    User1 = obj["User1"];
    User2 = obj["User2"];
  }
  
  // Testing here, you should set the default value of org_dis to -1
  if(org_dis != -1){
    // Send values
    ubidots.add("org_dis", org_dis); 
    ubidots.add("inorg_dis", inorg_dis);
    ubidots.add("Gas0", Gas0);
    ubidots.add("Gas1", Gas1);
    ubidots.add("dis", dis);
    ubidots.add("User1", User1);
    ubidots.add("User2", User2);

    bool bufferSent = false;
    bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

    if (bufferSent) {
      // Do something if values were sent properly
      Serial.println("Values were sent by the device");
    }
  }
}