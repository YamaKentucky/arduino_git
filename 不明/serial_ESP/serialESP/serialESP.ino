int LED = 18;
int count = 0;

void setup() {
  pinMode(LED, OUTPUT);

  Serial.begin(115200);
}

void twinkle(){
  if ((count % 2) == 1) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}

void loop() {
  Serial.print("count = ");
  Serial.println(count);
  twinkle();
  delay(1000);

  count++;
}
