#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

const char* ssid = "dryy";
const char* password = "hachikoq";

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
const char* serverName = "http://192.168.1.100:5000/post-data";

#define DHTTYPE DHT22
#define DHTPIN  4

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    String serverPath = serverName;

    http.begin(serverPath.c_str());

    // Specify content-type header
    http.addHeader("Content-Type", "application/json");

    // Prepare JSON payload
    String httpRequestData = "{\"temperature\":\"" + String(t) + "\",\"humidity\":\"" + String(h) + "\"}";

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    }
    else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }

  // Send data every 10 seconds
  delay(10000);
}