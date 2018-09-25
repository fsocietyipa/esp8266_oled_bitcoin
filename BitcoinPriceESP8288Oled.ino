#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 OLED(OLED_RESET);

int buttonPin = D3;
 
const char* ssid = "*******";
const char* password = "*******";
 
void setup () {  
  Serial.begin(115200);

  pinMode(buttonPin, INPUT);
  
  OLED.begin();
  OLED.clearDisplay();
  OLED.setTextWrap(false);
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
    
    OLED.setCursor(0,0);
    OLED.clearDisplay();
    OLED.println("Connecting.");
    OLED.display();
    delay(300);
    OLED.setCursor(0,0);
    OLED.clearDisplay();
    OLED.println("Connecting..");
    OLED.display();
    delay(300);
    OLED.setCursor(0,0);
    OLED.clearDisplay();
    OLED.println("Connecting...");
    OLED.display();
    delay(300);
    
  }

    OLED.setCursor(0,0);
    OLED.clearDisplay();
    OLED.println("Connected to " + String(ssid));
    OLED.println("IP: "+ WiFi.localIP().toString());
    OLED.println("Press button!");
    OLED.display();
 
}

void getBitcoinPrice() {
  
  OLED.setCursor(0,0);
  OLED.clearDisplay();
  OLED.println("Loading...");
  OLED.display();
  
  delay(1000);
  if (WiFi.status() == WL_CONNECTED) {
 
    HTTPClient http; 
 
    http.begin("http://api.coindesk.com/v1/bpi/currentprice.json"); 
    int httpCode = http.GET(); 

    
    if (httpCode > 0) {

      String payload = http.getString(); 
      
      DynamicJsonDocument doc;
      deserializeJson(doc, payload);
      JsonObject root = doc.as<JsonObject>();
      
      double price    = root["bpi"]["USD"]["rate_float"];
      Serial.println("Bitcoin price is: " + String(price) + "$");
      
      OLED.setCursor(0,0);
      OLED.clearDisplay();
      OLED.println("Bitcoin price is:");
      OLED.println(String(price) + " dollar");
      OLED.display();
    }
 
    http.end();
 
  }
}
 
void loop() {
  
int buttonStatus = digitalRead(buttonPin);

if (buttonStatus == LOW) {
  getBitcoinPrice();
}

 
}
