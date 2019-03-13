/*
 * ESP8266 NodeMCU AJAX Demo
 * Updates and Gets data from webpage without page refresh
 * https://circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "index.h" //Our HTML webpage contents with javascripts

#define LED1 0  //On board LED
#define LED2 4  //On board LED
#define SWITCH1 12  //On board LED
#define SWITCH2 13  //On board LED

int switch1State = 0;
int switch2State = 0;
int switch1AfterState = 0;
int switch2AfterState = 0;

#define DHTPIN            2  
#define DHTTYPE           DHT11     // DHT 22 (AM2302)
DHT_Unified dht1(DHTPIN, DHTTYPE);

//SSID and Password of your WiFi router
const char *ssid = "BESIR66";
const char *password = "ahmetw66.";

IPAddress ip(192, 168, 1, 73);  
IPAddress gateway(192,168,1,1); 
IPAddress subnet(255,255,255,0); 
ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleADC() {
 String t_type = server.arg("LEDtype"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 int a = 0;
 if(t_type == "1"){
  a = digitalRead(LED1);
 }
 if(t_type == "2"){
  a = digitalRead(LED2);
 }
 
 String adcValue = "0";
 if(a==0)
 adcValue = "1";
 
 server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}

void handleTemp() {  
    sensors_event_t event;  
    float temp, humi;
    
    dht1.temperature().getEvent(&event);
    temp = event.temperature;
    
    dht1.humidity().getEvent(&event);
    humi = event.relative_humidity;
 
    server.send(200, "text/plane", String(temp) + "ºC / " + String(humi) + "φ"); //Send ADC value only to client ajax request
}

void handleLED() {
 Serial.print("handleLED - ");
 String ledState = "OFF";
 String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 String t_type = server.arg("LEDtype"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.print("LEDtype: ");
 Serial.print(t_type);
 Serial.print(" LEDstate: ");
 Serial.print(t_state);
 Serial.print(". ");
 
 if(t_type.equals("1")){
   if(t_state == "1")
   {
    switch1State = 0; //Feedback parameter
   }
   else if(t_state == "0")
   {
    switch1State = 1; //Feedback parameter
   }
   ledState = String(switch1State);
 }
 
 if(t_type.equals("2")){
   if(t_state == "1")
   {
    switch2State = 0; //Feedback parameter
   }
   else
   {
    switch2State = 1; //Feedback parameter
   }
   ledState = String(switch2State);
 }
 
 Serial.print("switch1State: ");
 Serial.print(switch1State);
 
 Serial.print(" switch2State: ");
 Serial.print(switch2State);
 Serial.print("  finalState LED1/LED12: ");
 Serial.print(digitalRead(LED1));
 Serial.print(" / ");
 Serial.println(digitalRead(LED2));
 
 server.send(200, "text/plane", ledState); //Send web page
}

//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  
  //Wifi Network settings
  WiFi.mode(WIFI_AP);
  WiFi.config(ip, gateway, subnet); delay(50);
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Onboard LED port Direction output
  pinMode(LED1,OUTPUT); 
  pinMode(LED2,OUTPUT); 
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(SWITCH2, INPUT_PULLUP);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/setLED", handleLED);
  server.on("/readADC", handleADC);
  server.on("/handleTemp", handleTemp);
 
  // Initialize device.
  dht1.begin();
  
  switch1AfterState == digitalRead(SWITCH1) == 1 ? 0 : 1;
  switch2AfterState == digitalRead(SWITCH2) == 1 ? 0 : 1;
  
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests  
  if(switch1State == 0)
    digitalWrite(LED1,HIGH); //LED OFF
  else if(switch1State == 1)
    digitalWrite(LED1,LOW); //LED ON

  if(switch2State == 0)
    digitalWrite(LED2,HIGH); //LED OFF
  else if(switch2State == 1)
    digitalWrite(LED2,LOW); //LED ON
  
  if(switch1AfterState == digitalRead(SWITCH1)){
    switch1AfterState = digitalRead(SWITCH1) == 1 ? 0 : 1;
      switch1State = switch1State == 1 ? 0 : 1;
       Serial.print("switch1 has changed - switch1State: ");
       Serial.println(switch1State);
      delay(200);
  }
  
  if(switch2AfterState == digitalRead(SWITCH2)){
      switch2AfterState = digitalRead(SWITCH2) == 1 ? 0 : 1;
      switch2State = switch2State == 1 ? 0 : 1;
       Serial.print("switch2 has changed - switch2State: ");
       Serial.println(switch2State);
      delay(200);
  }
    
}
