int blockCount = 0;
int breakSwitch = 1;
int sensorState = 0;
int i = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  pinMode(8, INPUT);
  pinMode(A0, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorState = digitalRead(7);
  breakSwitch = digitalRead(A0);
  Serial.println(sensorState);
  Serial.println("\n");

  if (sensorState == 1)
  {
    blockCount = blockCount + 1;
    digitalWrite(13, HIGH);
    delay(500);
  }
  else
  {
    digitalWrite(13, LOW);
  }
  if (breakSwitch == 0)
  {
    Serial.println(blockCount);
    while(i < blockCount)
    {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(500);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(500);
      i = i + 1;
    }
  }

}
