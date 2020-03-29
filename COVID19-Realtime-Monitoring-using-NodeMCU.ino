#include <ESP8266WiFi.h>
#include <Wire.h>  
#include <ESP8266HTTPClient.h>

const char* ssid = "Enter your ssid"; // put your router name
const char* password = "Enter your password";// put your password 
const char* host = "api.thingspeak.com";
int effect_value;
int Rec_value;
int death_value;

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid,password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  
HTTPClient http;
http.begin("api.thingspeak.com", 80, "/apps/thinghttp/send_request?api_key=0KBJX49TND86W7E2"); //add your api
int httpCode = http.GET();
if(httpCode > 0) {
if(httpCode == HTTP_CODE_OK) {
String yourvalue = http.getString();
String TEffect_value = yourvalue.substring(0, yourvalue.length());
effect_value = TEffect_value.toInt();
String TRec_value = yourvalue.substring(sizeof(effect_value)+2, yourvalue.length());
Rec_value = TRec_value.toInt();
String TDeath_value = yourvalue.substring(sizeof(effect_value), yourvalue.length() - TRec_value.length());
death_value = TDeath_value.toInt();
//Serial.println(yourvalue);
//Serial.print("Coronavirus Cases:");
//Serial.print(effect_value);
//Serial.println();
//Serial.print("Deaths:");
//Serial.print(death_value);
//Serial.println();
//Serial.print("Recovered:");
//Serial.print(Rec_value);
//Serial.println();


}
} else {
Serial.printf("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
}
http.end();
delay(1000);
 sendCasesToNextion(); 
 sendDeathsToNextion();
 sendRecoveredToNextion();
}
void sendCasesToNextion()
{
  String command = "cor.txt=\""+String(effect_value)+"\"";
  Serial.print(command);
  endNextionCommand();
}

void sendDeathsToNextion()
{
  String command = "dea.txt=\""+String(death_value)+"\"";
  Serial.print(command);
  endNextionCommand();
}
void sendRecoveredToNextion()
{
  String command = "rec.txt=\""+String(Rec_value)+"\"";
  Serial.print(command);
  endNextionCommand();
}
void endNextionCommand()
{
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}
