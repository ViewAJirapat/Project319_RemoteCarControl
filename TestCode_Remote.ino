#include <WiFi.h>
#include <WiFiClient.h>

#define VRX_PIN  34 
#define VRY_PIN  35 

#define LED_Status 18

String command = "NNN";

const char* ssid = "CarMCU";
const char* password = "1212312121";
const char* serverIP = "192.168.4.1"; // Replace with NodeMCU's IP address
const int serverPort = 80;

const int COMMAND_LENGTH = 3; // Define the length of each command

int valueX = 0 ; // to store the X-axis value
int valueY = 0 ; // to store the Y-axis value

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(LED_Status, OUTPUT);
  
  // Connect ESP32 to the NodeMCU's Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void loop() {
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);
//  Serial.println(valueX);
//  Serial.println(valueY);
//  Serial.println("---------------------------");
//  delay(500);
  if((valueX > 1920) && (valueY < 10)){
   Serial.println("Move left");
   command = "LLL";}
  else if((valueX > 1900) && (valueY > 4000)){
   Serial.println("Move right");
   command = "RRR";}
  else if((valueX < 10) && (valueY > 1500)){
   Serial.println("Move down");
   command = "BBB";}
  else if((valueX > 4000) && (valueY > 1500)){
   Serial.println("Move up");
   command = "FFF";}
  else{command = "NNN";}
  delay(100);

  WiFiClient client;

  if(client.connect(serverIP, serverPort))
  {
    digitalWrite(LED_Status, HIGH); 
    client.print(command);
    client.stop();
    Serial.println("Command sent");
  }
  else
  {
    Serial.println("Connection failed");
    digitalWrite(LED_Status, LOW); 
  }
  delay(300);
}
