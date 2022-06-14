int watersensor = 34;
int valuewatersensor = 0;

void setup() {
  Serial.begin(9600);
  pinMode(watersensor, INPUT);

}

void loop() {
  valuewatersensor = digitalRead(watersensor);

  Serial.println(valuewatersensor);
  delay (1000);

}
