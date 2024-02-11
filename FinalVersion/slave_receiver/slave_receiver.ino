#include<Wire.h>

#define ANSWERSIZE 28

String answer = "Hello From Slave!! (Arduino)";

void setup() {
  Wire.begin(0x04);
  Serial.begin(9600);
}

void loop() {
  Wire.onReceive(reader);
  delay(1000);
  Wire.onRequest(writer);
  delay(1000);

}

void reader(int howMany) {
  for(int i=0;i<howMany;i++){
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println(".");
}

void writer(){
  byte response[ANSWERSIZE];
  for (byte i=0;i<ANSWERSIZE;i++){
    response[i] = (byte)answer.charAt(i);
  }
  Wire.write(response,sizeof(response));
}
