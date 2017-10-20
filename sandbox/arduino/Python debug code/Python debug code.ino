int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(String(int(10)));
  Serial.println("OK");
  delay(10000);
  
}
