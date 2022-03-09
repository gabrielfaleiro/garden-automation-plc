void setup() {
  // put your setup code here, to run once:
  pinMode(Q0_5, OUTPUT);
}

void loop() {
  int outVal = 0;
  outVal = digitalRead(Q0_5);
  digitalWrite(Q0_5, !outVal);
  delay(1000);
}
