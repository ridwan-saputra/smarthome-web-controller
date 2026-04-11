#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

const char *ssid = "your ssid";
const char *password = "your password";

// ke atas rahasia
const int buzzer = 5;

// Pin relay tiap ruangan (edit sesuai kebutuhan)
const int relayPin[5] = {0, 26, 25, 16, 32}; // index 0 kosong, pakai 1-4

// State tiap ruangan
bool lampState[5] = {false, false, false, false, false};

void connectWifi()
{
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    digitalWrite(buzzer, LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// Factory function buat bikin handler per ruangan
void handleGet(int roomId)
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", lampState[roomId] ? "ON" : "OFF");
}

void handlePost(int roomId)
{
  lampState[roomId] = !lampState[roomId];
  digitalWrite(relayPin[roomId], lampState[roomId] ? HIGH : LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", lampState[roomId] ? "ON" : "OFF");
}

// Handler per ruangan
void getRoom1()
{
  Serial.println("GET room1 called"); // cek apakah ini pernah terpanggil
  handleGet(1);
}
void getRoom2() { handleGet(2); }
void getRoom3() { handleGet(3); }
void getRoom4() { handleGet(4); }

void setRoom1()
{
  Serial.println("GET room1 called"); // cek apakah ini pernah terpanggil
  handlePost(1);
}
void setRoom2() { handlePost(2); }
void setRoom3() { handlePost(3); }
void setRoom4() { handlePost(4); }

void setup()
{
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);

  // Setup pin relay
  for (int i = 1; i <= 4; i++)
  {
    pinMode(relayPin[i], OUTPUT);
    digitalWrite(relayPin[i], LOW);
  }

  delay(5000);
  connectWifi();

  // Register endpoints
  server.on("/lamp/room1", HTTP_GET, getRoom1);
  server.on("/lamp/room1", HTTP_POST, setRoom1);

  server.on("/lamp/room2", HTTP_GET, getRoom2);
  server.on("/lamp/room2", HTTP_POST, setRoom2);

  server.on("/lamp/room3", HTTP_GET, getRoom3);
  server.on("/lamp/room3", HTTP_POST, setRoom3);

  server.on("/lamp/room4", HTTP_GET, getRoom4);
  server.on("/lamp/room4", HTTP_POST, setRoom4);

  server.begin();
  Serial.println("Server started..");
}

void loop()
{
  server.handleClient();
}