#include<Wire.h>

#define SLAVE_ADDR 11
void setup() {
  Wire.begin();
  

}

void loop() {
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write("Hello");
  Wire.endTransmission();
  delay(1000);
}
