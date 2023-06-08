#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>


#define WIFI_SSID "Z.A. Studios @ 2.4GHz"
#define WIFI_PASSWORD "lastkiss"

#define BOT_TOKEN "5656418080:AAFiSiR0KfMzWnuFbkh37S5aKrxfikPr3IY"
#define CHAT_ID "5017324763"

#define TOUCH_THRESHOLD 25

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void callback(){ }

void setup(){
  Serial.begin(115200);
  Serial.print("Connecting to Wifi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  uint32_t notConnectedCounter = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.println("Wifi connecting...");
    notConnectedCounter++;
    if(notConnectedCounter > 100) { // Reset board if not connected after 15s
        Serial.println("Resetting due to Wifi not connecting...");
        ESP.restart();
  }
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  
  bot.sendMessage(CHAT_ID, "Arianna needs help!", "");
  Serial.print("Sending message...");
  
  touchAttachInterrupt(T4, callback, TOUCH_THRESHOLD);
  esp_sleep_enable_touchpad_wakeup();
  Serial.print("Entering deep sleep...");
  esp_deep_sleep_start();
}

void loop(){}
