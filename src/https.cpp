#include <Arduino.h>
#include <WiFiClientSecure.h>

#include "https.h"

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char *fingerprint = "11 55 6F 15 DA 87 92 29 AA BD 46 5B C7 7D 5B 02 4F D2 C4 C7";
const int httpsPort = 443;

String connectToHttpsServer(const char *host, const char *path) {
    // Use WiFiClientSecure class to create TLS connection
    WiFiClientSecure client;
    Serial.print("connecting to ");
    Serial.println(host);
    if (!client.connect(host, httpsPort)) {
        Serial.println("connection failed");
        return "NULL";
    }

    if (client.verify(fingerprint, host)) {
        Serial.println("certificate matches");
    } else {
        Serial.println("certificate doesn't match");
    }

    String url = path;
    Serial.print("requesting URL: ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "User-Agent: BuildFailureDetectorESP8266\r\n" +
                 "Connection: close\r\n\r\n");

    Serial.println("request sent");
    while (client.connected()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") {
            Serial.println("headers received");
            break;
        }
    }
    String line = client.readStringUntil('\n');
    Serial.println("reply was:");
    Serial.println(line);
    Serial.println("closing connection");

    return line;
}
