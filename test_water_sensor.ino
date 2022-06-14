int watersensor = 34;
int relay = 35;
int valuewatersensor = 0;

void setup() {
  Serial.begin(9600);
  pinMode(watersensor, INPUT);
  pinMode(relay, OUTPUT);

  digitalWrite(relay, HIGH);
}

void loop() {
  valuewatersensor = digitalRead(watersensor);

  Serial.println(valuewatersensor);
  delay (1000);

}
