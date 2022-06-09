#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <Ticker.h>

#include "wifi.h"

// https://github.com/esp8266/Arduino/issues/2735

const char* ssid = "PT";
const char* password = "judgedevin";
Ticker wifiReconnect;

// Private function declarations

void eventWiFi(WiFiEvent_t event);
void dbg_printf(const char* format, ...);
String connectionStatus(int which);
void reconnectWiFi();
bool isAutoConnected();
bool hasWifiConfigChanged();
void connectWiFi();

// Public function definitions

void setUpWiFi() {
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(false);
    WiFi.onEvent(eventWiFi);
    WiFi.mode(WIFI_STA);
    if (!isAutoConnected() || hasWifiConfigChanged()) {
        connectWiFi();
    }

    // wifiReconnect.attach(10.0, reconnectWiFi);  // Try to reconnect in 10s

    // WiFi.begin(ssid, password);
    // while (WiFi.status() != WL_CONNECTED) {
    //     delay(500);
    //     Serial.print(".");
    // }
    // Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

// Private function definitions

void dbg_printf(const char* format, ...) {
    static char sbuf[1400];  // For debug lines
    va_list varArgs;         // For variable number of params

    va_start(varArgs, format);                       // Prepare parameters
    vsnprintf(sbuf, sizeof(sbuf), format, varArgs);  // Format the message
    va_end(varArgs);                                 // End of using parameters

    Serial.print(sbuf);
}

void eventWiFi(WiFiEvent_t event) {
    switch (event) {
        case WIFI_EVENT_STAMODE_CONNECTED:
            dbg_printf("[WiFi] %d, Connected\n", event);
            break;

        case WIFI_EVENT_STAMODE_DISCONNECTED:
            dbg_printf("[WiFi] %d, Disconnected - Status %d, %s\n", event, WiFi.status(), connectionStatus(WiFi.status()).c_str());
            break;

        case WIFI_EVENT_STAMODE_AUTHMODE_CHANGE:
            dbg_printf("[WiFi] %d, AuthMode Change\n", event);
            break;

        case WIFI_EVENT_STAMODE_GOT_IP:
            dbg_printf("[WiFi] %d, Got IP\n", event);

            // Connected, do connected stuff

            break;

        case WIFI_EVENT_STAMODE_DHCP_TIMEOUT:
            dbg_printf("[WiFi] %d, DHCP Timeout\n", event);
            break;

        case WIFI_EVENT_SOFTAPMODE_STACONNECTED:
            dbg_printf("[AP] %d, Client Connected\n", event);
            break;

        case WIFI_EVENT_SOFTAPMODE_STADISCONNECTED:
            dbg_printf("[AP] %d, Client Disconnected\n", event);
            break;

        case WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED:
            //      dbg_printf("[AP] %d, Probe Request Recieved\n", event);
            break;
    }
}

String connectionStatus(int which) {
    switch (which) {
        case WL_CONNECTED:
            return "Connected";
            break;

        case WL_NO_SSID_AVAIL:
            return "Network not availible";
            break;

        case WL_CONNECT_FAILED:
            return "Wrong password";
            break;

        case WL_IDLE_STATUS:
            return "Idle status";
            break;

        case WL_DISCONNECTED:
            return "Disconnected";
            break;

        default:
            return "Unknown";
            break;
    }
}

void reconnectWiFi() {
    dbg_printf("[WiFi] Status %d, %s - Reconnecting...\n", WiFi.status(), connectionStatus(WiFi.status()).c_str());
    if (WiFi.status() == 0) {
        connectWiFi();
    }
    //WiFi.reconnect();
}

bool isAutoConnected() {
    int connRes = WiFi.waitForConnectResult();
    if (connRes == WL_CONNECTED) {
        // dbg_printf("[WiFi] Auto-connected to %s, IP address: " IPSTR "\n", WiFi.SSID().c_str(), IP2STR(WiFi.localIP()));
        return true;
    } else {
        // dbg_printf("[WiFi] Auto-connect to %s failed - Status %d, %s\n", WiFi.SSID().c_str(), WiFi.status(), connectionStatus(WiFi.status()).c_str());
        return false;
    }
}

bool hasWifiConfigChanged() {
    if (strcmp(WiFi.SSID().c_str(), ssid) != 0) {
        dbg_printf("[WiFi] Config Changed, Disconnecting...\n");
        WiFi.setAutoReconnect(false);
        WiFi.disconnect();
        return true;
    } else {
        return false;
    }
}

void connectWiFi() {
    dbg_printf("[WiFi] Connecting...\n", ssid);
    WiFi.begin(ssid, password);
    int connRes = WiFi.waitForConnectResult();
    if (connRes != WL_CONNECTED) {
        dbg_printf("[WiFi] Connection to %s failed - Status %d, %s, Retrying in 10s...\n", WiFi.SSID().c_str(), WiFi.status(), connectionStatus(WiFi.status()).c_str());
        WiFi.disconnect();
        //ESP.restart();
    } else {
        // dbg_printf("[WiFi] Connected to %s, IP address: " IPSTR "\n", WiFi.SSID().c_str(), IP2STR(WiFi.localIP()));
    }
}