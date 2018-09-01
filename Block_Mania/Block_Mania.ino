/////////////////////MAIN VARIABLES//////////////////
#define lc 0
#define sc 1
#define lm1 3
#define lm2 5
#define rm1 6
#define rm2 9

int s1, s2, s3, s4, s5, s6, s7, s8;

float error = 0.0;
float prev_error = 0.0;

float Kp = 35.0;     //25
float Kd = 85.0;   //100
float P = 0.0;
float D = 0.0;
float pd = 0.0;
float lms, rms;
float bs = 170.0;      //125
int left = 0, right = 0;
int leftthres = 400;
int rightthres = 400;
int blockLength = 0;
int countL = 0;
int countS = 0;
int sensorState;
int blockThres = 2500;
int i = 0;
int j = 0;


//////////////////////////////////SETUP//////////////////////

void setup()
{
  pinMode(lm1, OUTPUT); //LEFT
  pinMode(lm2, OUTPUT); //LEFTback
  pinMode(rm1, OUTPUT); //RIGHT
  pinMode(rm2, OUTPUT); //RIGHTback
  pinMode(A0, INPUT);   //IR
  pinMode(A2, INPUT);   //IR
  pinMode(A3, INPUT);   //IR
  pinMode(A4, INPUT);   //IR
  pinMode(A5, INPUT);   //IR
  pinMode(A1, INPUT);   //IR
  pinMode(2, INPUT);    //IR
  pinMode(4, INPUT);    //IR

  pinMode(7, INPUT);    //THE IR FOR BLOCKS

  Serial.begin(1200);

  pinMode(8, OUTPUT);   //LARGE LED
  pinMode(13, OUTPUT);  //SMALL LED
}

//////////////////////////////////ERROR_MAPPING/////////////

void error_map() {

  if ((s3 == sc) && ((s4 == lc) || (s5 == lc)) && (s6 == sc)) {
    error = 0;
  }//FOR ONE OF THE TWO CENTRE PINS

  else if ((s3 == sc) && (s4 == lc) && (s5 == lc) && (s6 == sc)) {
    error = 0;
  }//FOR BOTH CENTRE PINS

  else if ((s3 == lc) && (s4 == lc) && (s5 == lc) && (s6 == sc)) {    //(s5 == lc)
    error = -0.5;
  }

  else if ((s3 == sc) && (s4 == lc) && (s5 == lc) && (s6 == lc)) {   //(s4 == lc)
    error = 0.5;
  }

  else if ((s2 == sc) && (s3 == lc) && (s4 == lc) && (s5 == sc)) {
    error = -1;
  }

  else if ((s4 == sc) && (s5 == lc) && (s6 == lc) && (s7 == sc)) {
    error = 1;
  }

  else if ((s2 == lc) && (s3 == lc) && (s4 == lc) && (s5 == sc)) {
    error = -1.5;
  }

  else if ((s4 == sc) && (s5 == lc) && (s6 == lc) && (s7 == lc)) {
    error = 1.5;
  }

  else if ((s1 == sc) && (s2 == lc) && (s3 == lc) && (s4 == sc)) {
    error = -2;
  }

  else if ((s5 == sc) && (s6 == lc) && (s7 == lc) && (s8 == sc)) {
    error = 2;
  }

  else if ((s1 == lc) && (s2 == lc) && (s3 == lc) && (s4 == sc)) {
    error = -2.5;
  }

  else if ((s5 == sc) && (s6 == lc) && (s7 == lc) && (s8 == lc)) {
    error = 2.5;
  }

}

/////////////////////////////////////READsENSOR/////////////////

void readsensors() {
  s1 = digitalRead(A0);
  s2 = digitalRead(A1);
  s3 = digitalRead(A2);
  s4 = digitalRead(A3);
  s5 = digitalRead(A4);
  s6 = digitalRead(A5);
  s7 = digitalRead(2);
  s8 = digitalRead(4);
}

//////////////////////ALL MOVEMENTS///////////////////////

void compute_speed()
{
  lms = bs + pd;
  rms = bs - pd;
}
void linefollow()
{
  analogWrite(lm1, lms);
  analogWrite(lm2, 0);
  analogWrite(rm1, rms + 10);
  analogWrite(rm2, 0);
}
void stop_lfr()
{
  analogWrite(lm1, 0);
  analogWrite(lm2, 0);
  analogWrite(rm1, 0);
  analogWrite(rm2, 0);
}

void sharp_left_turn() {
  analogWrite(lm1, 0);
  analogWrite(lm2, 80);
  analogWrite(rm1, 80);
  analogWrite(rm2, 0);
}

void sharp_right_turn() {
  analogWrite(lm1, 80);
  analogWrite(lm2, 0);
  analogWrite(rm1, 0);
  analogWrite(rm2, 80);
}


//////////////////////////BLINKNG///////////////////
void blinkL()
{
  digitalWrite(8, HIGH);
  delay(20);
  digitalWrite(8, LOW);
  delay(20);
}

void blinkS()
{
  digitalWrite(13, HIGH);
  delay(20);
  digitalWrite(13, LOW);
  delay(20);
}

////////////////////////PID/////////////////////////


void pid()
{
  readsensors();           //READ THE SENSOR
  error_map();             //MAP THE ERRORS TO THE VALUES


  if (s1 == lc)
  { //IF THE LEFTMOST PIN IS ON THE LINE
    left = 0;              //SET LEFT AS 0
  }


  if (s8 == lc)
  { //IF THE RIGHTMOST PIN IS ON THE LINE
    right = 0;             //SET RIGHT AS ZERO
  }


  //WHEN THE BOT IS OUT OF THE LINE
  if ((s1 != lc) && (s2 != lc) && (s3 != lc) && (s4 != lc) && (s5 != lc) && (s6 != lc) && (s7 != lc) && (s8 != lc))
  {
    if ((left > leftthres) && (right < rightthres))
    {
      readsensors();        //READ THE SENSOR
      while ((s4 != lc) && (s5 != lc))
      {
        sharp_right_turn(); //TURN RIGHT UNTILL U FIND THE LINE
        readsensors();
      }
    }
    else if ((left < leftthres) && (right > rightthres))
    {
      readsensors();
      while ((s4 != lc) && (s5 != lc))
      {
        sharp_left_turn(); //TURN LEFT UNLESS U FIND LINE
        readsensors();     //CHECK SENSOR AND READ
      }
    }
  }


  left = left + 1;
  right = right + 1;


  if (left > 20000)
  {
    left = 1000;
  }
  if (right > 20000)
  {
    right = 1000;
  }

  //ERROR CALCULATION
  P = Kp * error;
  D = Kd * (error - prev_error);
  pd = P + D;
  compute_speed();
  linefollow();
  prev_error = error;


  if ((s1 == lc) && (s2 == lc) && (s3 == lc) && (s4 == lc) && (s5 == lc) && (s6 == lc) && (s7 == lc) && (s8 == lc))
  {
    stop_lfr();
    //THTE BLINKING FOR COUNTS
    for (int k = 0; k < countS + countL; k++)
    {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }
    exit(1);
  }
}


///////////////////////////////LOOP///////////////////////////////////////////////

void loop()
{

  pid();

  sensorState = digitalRead(7);

  if (sensorState == 1)
  {
    while (sensorState != 0)
    {
      sensorState = digitalRead(7);
      blockLength++;
      pid();
    }//end of while

    if (blockLength < blockThres)
    {
      blinkS();
      countS += 1;
      Serial.println("small");
      Serial.println(countS);
    }

    if (blockLength > blockThres)
    {
      blinkL();
      countL += 1;
      Serial.println("large");
      Serial.println(countL);
    }

    blockLength = 0;
  }
}


