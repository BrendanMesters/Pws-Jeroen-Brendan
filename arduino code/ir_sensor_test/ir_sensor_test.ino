#include <SharpIR.h>


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
SharpIR sharp("A1", 25, 93, 1080);
}

void loop() {
  // put your main code here, to run repeatedly:
}
