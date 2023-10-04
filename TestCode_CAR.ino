#include <ESP8266WiFi.h>

const char *ssid = "CarMCU";
const char *password = "1212312121";

const int COMMAND_LENGTH = 3; // Define the length of each command

const int R_motorSpeedPin = D5;
const int R_motorPin1 = D1; 
const int R_motorPin2 = D2; 

const int L_motorSpeedPin = D6;
const int L_motorPin1 = D3; 
const int L_motorPin2 = D4; 

const int LED_Status = D7;

WiFiServer server(80); // Create a server on port 80
WiFiClient client;

void setup() {
  pinMode(LED_Status, OUTPUT);
  pinMode(R_motorPin1, OUTPUT);
  pinMode(R_motorPin2, OUTPUT);
  pinMode(R_motorSpeedPin, OUTPUT);
  pinMode(L_motorPin1, OUTPUT);
  pinMode(L_motorPin2, OUTPUT);
  pinMode(L_motorSpeedPin, OUTPUT);
  Serial.begin(115200);
  delay(10);

  // Set up NodeMCU as an Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  //Serial.print("Access Point IP address: ");
  //Serial.println(myIP);

  server.begin();
}

void loop() {
  if (!client || !client.connected()) {
    client = server.available();
  }

  // Handle incoming commands from the remote (ESP32)
  while (client.connected()) {
    digitalWrite(LED_Status, HIGH); 
    if (client.available() >= COMMAND_LENGTH) {
      // Read the fixed-length command
      char command[COMMAND_LENGTH];
      client.readBytes(command, COMMAND_LENGTH);
      Serial.println(command);

      // Process the received command
      processCommand(command);
    }
  }
  digitalWrite(LED_Status, LOW); 
}

void processCommand(const char* command) {
   if (strcmp(command, "FFF@") == 0) {
      digitalWrite(R_motorPin1, HIGH); 
      digitalWrite(R_motorPin2, LOW);
      digitalWrite(R_motorSpeedPin, 1);
      digitalWrite(L_motorPin1, HIGH); 
      digitalWrite(L_motorPin2, LOW);
      digitalWrite(L_motorSpeedPin, 1);
      
   } else if (strcmp(command, "BBB@") == 0) {
      digitalWrite(R_motorPin1, LOW); 
      digitalWrite(R_motorPin2, HIGH);
      digitalWrite(R_motorSpeedPin, 1);
      digitalWrite(L_motorPin1, LOW); 
      digitalWrite(L_motorPin2, HIGH);
      digitalWrite(L_motorSpeedPin, 1);
   } else if (strcmp(command, "RRR@") == 0) {
      digitalWrite(R_motorPin1, LOW); 
      digitalWrite(R_motorPin2, HIGH);
      digitalWrite(R_motorSpeedPin, 1);
      digitalWrite(L_motorPin1, HIGH); 
      digitalWrite(L_motorPin2, LOW);
      digitalWrite(L_motorSpeedPin, 1);
   } else if (strcmp(command, "LLL@") == 0) {
      digitalWrite(R_motorPin1, HIGH); 
      digitalWrite(R_motorPin2, LOW);
      digitalWrite(R_motorSpeedPin, 1);
      digitalWrite(L_motorPin1, LOW); 
      digitalWrite(L_motorPin2, HIGH);
      digitalWrite(L_motorSpeedPin, 1);
   }
   else{
    digitalWrite(R_motorPin1, LOW); 
    digitalWrite(R_motorPin2, LOW);
    digitalWrite(R_motorSpeedPin, 0);
    digitalWrite(L_motorPin1, LOW); 
    digitalWrite(L_motorPin2, LOW);
    digitalWrite(L_motorSpeedPin, 0);
    }
}
