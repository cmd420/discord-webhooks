#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "DiscordWebhook.h"

#define SSID "<your ssid>"
#define PASS "<your password>"
#define DISCORD_WEBHOOK_URL "<your discord webhook url>"

ESP8266WiFiMulti wifi_multi;
DiscordWebhook discord_webhook;

void connect_to_wifi()
{
    WiFi.mode(WIFI_STA);
    wifi_multi.addAP(SSID, PASS);

    Serial.printf("Connecting to %s\n", SSID);
    while (wifi_multi.run() != WL_CONNECTED)
        delay(50);
    Serial.println("Connected to WiFi");
}

void setup()
{
    Serial.begin(115200);
    connect_to_wifi();

    discord_webhook.begin(DISCORD_WEBHOOK_URL);
    bool success = discord_webhook.send("Hello World!");

    Serial.printf("Sending webhook %s\n", success ? "succeeded!" : "failed.");
}

void loop()
{
}