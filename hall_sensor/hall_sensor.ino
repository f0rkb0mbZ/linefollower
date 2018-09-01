int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A4, INPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
sensorValue = analogRead(A4);
/*if(sensorValue == 1){
  Serial.println("Magnet Detected!");
  analogWrite(11, 127);
  //delay(10);
}
else {
  Serial.println("Magnet not detected!");
  analogWrite(11, 127);
  //delay(10);
}*/
Serial.println(sensorValue);
delay(100);

}
