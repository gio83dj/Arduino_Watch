#include <TimeLib.h>

int digit1 = 10; // (00:0X) Cifra più a DESTRA 
int digit2 = 11; // (00:X0)
int digit3 = 12; // (0X:00)
int digit4 = 13; // (X0:00) Cifra "1" iniziale 
int digitDP = 0; // (00X00) Puntini

int segA = 8;   //Display pin a
int segB = 7;   //Display pin b
int segC = 6;   //Display pin c
int segD = 5;   //Display pin d
int segE = 4;   //Display pin e
int segF = 3;   //Display pin f
int segG = 2;   //Display pin g
int segDP = 9;  //Display pin dot

byte SW0 = A0;
byte SW1 = A1;
byte SW2 = A2;

int delayTime = 2000;

int num1;
int num2;
int num3;
int num4;

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segDP, OUTPUT);
  pinMode(digitDP,OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  setTime(9,1,0,13,2,2022);

  pinMode(SW0, INPUT_PULLUP);   
  pinMode(SW1, INPUT_PULLUP);  
  //pinMode(A2, OUTPUT);  
  //pinMode(A3, OUTPUT);  
  
  digitalWrite(SW0, HIGH); 
  digitalWrite(SW1, HIGH);
  //digitalWrite(A2, LOW);
  //digitalWrite(A3, LOW);
}

void loop() {
  reset();
  //displayNumber03(1);
  //displayNumber04(1);
  //displayMovGio(300);
  //reset();
  //displayMovFlo(150);
  //displayDots();
  
  if (!(digitalRead(SW0))) set_time_hour();
  if (!(digitalRead(SW1))) set_time_min();
  
  clockDisplay(3000);
  reset();
  secondsDisplay(800);
  reset();
  game1();
  reset();
  game2();
  reset();
  displayDots(); 
}

void set_time_min(){
  while (!digitalRead(SW1)) 
    {
      byte hours = hour();
      byte minutes = minute();
     minutes++;
    //Serial.println(minutes);
    if (minutes > 59) minutes = 0;
     for(int i = 20 ; i >0  ; i--) {
      int timp= hours*100+minutes;
      if (timp > 1000) displayNumber01(timp);
     else displayNumber02(timp);
     }
    setTime(hours,minutes,0,0,0,0);
    delay(150);
    }
  }

  
void set_time_hour()   {
  //Serial.println("SETTING TIME...");
  byte minutes1 = 0;
  byte hours1 = 0;
  byte minutes = minute();
  byte hours = hour();

  while (!digitalRead(SW0))
  {
    //Serial.println("SW0 RED = ");
    minutes1=minutes;
    hours1=hours;
    hours++;
    //Serial.println(hours);
    if (hours > 12) hours = 0;  
    if (hours <= 9){
      displayNumber01(hours);
      //displayLetter02('h');
      //displayLetter03('h');
      delay(150);
    }
    else if(hours >= 10){
      num1 = hours % 10;  
      displayNumber01(num1);
      num2 = hours / 10;
      displayNumber02(num2);
      //displayLetter03('h');
      //displayNumber04(1);
      delay(150);
      }
     setTime(hours,minutes,0,0,0,0);
   delay(150);
  }
}

void clockDisplay(int durata){
  int zz = 0;
  do {
    //digitalWrite(segDP, HIGH);
    int hr = hour();
    int timp = ( (hr>12)?(hr%12):hr)*100+minute();
    //Serial.println(timp);
    
    if (timp < 100){
      num1 = timp % 10;  
      displayNumber01(num1);
    
      num2 = timp / 10;
      displayNumber02(num2);
    }
    else if(timp < 1000){
      num3 = timp / 100;
      displayNumber03(num3);

      timp = timp % 100;
      num1 = timp % 10;  
      displayNumber01(num1);
    
      num2 = timp / 10;
      displayNumber02(num2);
    }
    else{
      num4 = timp /1000;
      displayNumber04(1);
      
      timp = timp - 1000;
      num3 = timp / 100;
      displayNumber03(num3);

      timp = timp % 100;
      num1 = timp % 10;  
      displayNumber01(num1);
  
      num2 = timp / 10;
      displayNumber02(num2);
    }
    displayDots();
    zz += 1;
    
    if (!(digitalRead(SW0))) set_time_hour();
    if (!(digitalRead(SW1))) set_time_min();
    
  } while (zz < durata);
  reset();
}

void secondsDisplay(int durata){
  int zz = 0;
  do {

    //digitalWrite(segDP, HIGH);
    int sec = second();
    //int timp = ( (hr>12)?(hr%12):hr)*100+minute();
    //Serial.println(sec);
    
    if (sec <= 9){
      displayNumber01(sec);
      displayLetter02('h');
      displayLetter03('h');
    }
    else if(sec >= 10){
        num1 = sec % 10;  
      displayNumber01(num1);
    
      num2 = sec / 10;
      displayNumber02(num2);
      displayLetter03('h');
      //displayNumber04(1);
    }
      
    displayDots();
  
    zz += 1;
    
    if (!(digitalRead(SW0))) set_time_hour();
    if (!(digitalRead(SW1))) set_time_min();
    
  } while (zz < durata);
  reset();
}

void pSerial(){
  Serial.println((String)"HOURs:" + hour());
  Serial.println((String)"MINs:" + minute());
  Serial.println((String)"SECs:" + second());
  Serial.println((String)"DATE: " + day()+ month() + year());
  }

void displayNumber01(int toDisplay) {
  #define DIGIT_ON  HIGH
  #define DIGIT_OFF  LOW
  digitalWrite(digit1, DIGIT_ON);
  lightNumber(toDisplay);
  delayMicroseconds(delayTime);
  digitalWrite(digit1, DIGIT_OFF);
}


void displayNumber02(int toDisplay) {
  #define DIGIT_ON  HIGH
  #define DIGIT_OFF  LOW
  digitalWrite(digit2, DIGIT_ON);
  lightNumber(toDisplay);
  delayMicroseconds(delayTime);
  digitalWrite(digit2, DIGIT_OFF);
}


void displayNumber03(int toDisplay) {
  #define DIGIT_ON  HIGH
  #define DIGIT_OFF  LOW
  digitalWrite(digit3, DIGIT_ON);
  lightNumber(toDisplay);
  delayMicroseconds(delayTime);
  digitalWrite(digit3, DIGIT_OFF);
}


void displayNumber04(int toDisplay) {
  #define DIGIT_ON  HIGH
  #define DIGIT_OFF  LOW
  digitalWrite(digit4, DIGIT_ON);
  lightNumber(toDisplay);
  delayMicroseconds(delayTime);
  digitalWrite(digit4, DIGIT_OFF);
}

void displayLetter01(char toDisplay) {
  #define DIGIT_ON  HIGH
  #define DIGIT_OFF  LOW
  digitalWrite(digit1, DIGIT_ON);
  lightLetter(toDisplay);
  delayMicroseconds(delayTime);
  digitalWrite(digit1, DIGIT_OFF);
}

void displayLetter02(char toDisplay) {
  #define DIGIT_ON  HIGH
  #define DIGIT_OFF  LOW
  digitalWrite(digit2, DIGIT_ON);
  lightLetter(toDisplay);
  delayMicroseconds(delayTime);
  digitalWrite(digit2, DIGIT_OFF);
}

void displayLetter03(char toDisplay) {
  #define DIGIT_ON  HIGH
  #define DIGIT_OFF  LOW
  digitalWrite(digit3, DIGIT_ON);
  lightLetter(toDisplay);
  delayMicroseconds(delayTime);
  digitalWrite(digit3, DIGIT_OFF);
}


void lightLetter(char letterToDisplay) {
  #define SEGMENT_ON  LOW
  #define SEGMENT_OFF HIGH
  switch (letterToDisplay){
    case 'g':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 'i':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 'o':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 'f':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
     case 'l':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      break;
     case 'h':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
    }
  }

void displayGio(int delayValue){
  int z = 0;
  do {
    displayLetter03('g');
    displayLetter02('i');
    displayLetter01('o');
    z += 1;
  } while (z < delayValue);
}
void displayMovGio(int delayValue){
  int z = 0;
  do {
    displayLetter01('g');
    z += 1;
  } while (z < delayValue);
    z = 0;
  do {
    displayLetter02('g');
    displayLetter01('i');
    z += 1;
  } while (z < delayValue);
      z = 0;
  do {
    displayLetter03('g');
    displayLetter02('i');
    displayLetter01('o');
    z += 1;
  } while (z < delayValue);
}

void displayMovFlo(int delayValue){
  int z = 0;
  do {
    displayLetter01('f');
    z += 1;
  } while (z < delayValue);
    z = 0;
  do {
    displayLetter02('f');
    displayLetter01('l');
    z += 1;
  } while (z < delayValue);
      z = 0;
  do {
    displayLetter03('f');
    displayLetter02('l');
    displayLetter01('o');
    z += 1;
  } while (z < delayValue);
}
void displayFlo(int delayValue){
  int z = 0;
  do {
    displayLetter03('f');
    displayLetter02('l');
    displayLetter01('o');
    z += 1;
  } while (z < delayValue);
}

// TRADUCI NUMERO IN SEGMENTI
void lightNumber(int numberToDisplay) {

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

  switch (numberToDisplay){

  case 0:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  
  case 10:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;
  }
}

void game1(){
  circlePerimeter(100);
  circlePerimeterAnti(200);
  circlePerimeter(100);
  circlePerimeter(90);
  circlePerimeter(75);
  circlePerimeter(50);
  circlePerimeter(25);
  circlePerimeter(15);
  circlePerimeter(5);
  
int z = 0;
do {
  circlePerimeter(5);
    z += 1;
  } while (z < 150);

  clockDisplay(2500);

  
  reset();
  displayMovGio(300);
  reset();
  displayMovFlo(150);
  reset();
  
  int x = 0;
do {
  digitalWrite(digit1, HIGH);
  circle();
  reset();
  digitalWrite(digit2, HIGH);
  circleAnti();
  reset();
  digitalWrite(digit3, HIGH);
  circleAnti();
  reset();
  x += 1;
} while (x < 3);
  clockDisplay(1500);
  
reset();
circleAll();
circleAll();
circleAll();
circleAll();
circleAll();
reset();
lineLR(200);
lineRL(200);
circleAllAnti();
circleAllAnti();
circleAllAnti();
}


 void reset(){
  #define SEGMENT_ON  LOW
  #define SEGMENT_OFF HIGH
    digitalWrite(segDP,SEGMENT_OFF);
    digitalWrite(digit1, LOW);
    digitalWrite(digit2, LOW);
    digitalWrite(digit3, LOW);
    digitalWrite(digit4, LOW);
    digitalWrite(digitDP,LOW);
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
 }

 void ball(int delayValue){
  #define SEGMENT_ON  LOW
  #define SEGMENT_OFF HIGH
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segD, SEGMENT_ON);
  digitalWrite(segE, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  digitalWrite(segC, SEGMENT_ON);
  delay(delayValue);
  reset();
  digitalWrite(digit2, HIGH);
  digitalWrite(segD, SEGMENT_ON);
  digitalWrite(segE, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  digitalWrite(segC, SEGMENT_ON);
  delay(delayValue);
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segD, SEGMENT_ON);
  digitalWrite(segE, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  digitalWrite(segC, SEGMENT_ON);
  delay(delayValue);
  reset();
  digitalWrite(digit2, HIGH);
  digitalWrite(segD, SEGMENT_ON);
  digitalWrite(segE, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  digitalWrite(segC, SEGMENT_ON);
  delay(delayValue);
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segD, SEGMENT_ON);
  digitalWrite(segE, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  digitalWrite(segC, SEGMENT_ON);
  delay(delayValue);
  }

void ballCircular(int delayValue){
  #define SEGMENT_ON  LOW
  #define SEGMENT_OFF HIGH
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segD, SEGMENT_ON);
  digitalWrite(segE, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  digitalWrite(segC, SEGMENT_ON);
  delay(delayValue);
  reset();
  digitalWrite(digit2, HIGH);
  digitalWrite(segD, SEGMENT_ON);
  digitalWrite(segE, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  digitalWrite(segC, SEGMENT_ON);
  delay(delayValue);
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segD, SEGMENT_ON);
  digitalWrite(segE, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  digitalWrite(segC, SEGMENT_ON);
  delay(delayValue);
      reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segA, SEGMENT_ON);
  digitalWrite(segB, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  digitalWrite(segF, SEGMENT_ON);
  delay(delayValue);
      reset();
  digitalWrite(digit2, HIGH);
  digitalWrite(segA, SEGMENT_ON);
  digitalWrite(segB, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  digitalWrite(segF, SEGMENT_ON);
  delay(delayValue);
    reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segA, SEGMENT_ON);
  digitalWrite(segB, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  digitalWrite(segF, SEGMENT_ON);
  delay(delayValue);
  }
  
void circleAll(){
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, HIGH);
  circle();
  reset();
}

void circleAllAnti(){
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, HIGH);
  circleAnti();
  reset();
}

void circle(){
  digitalWrite(segA, LOW);
  delay(100);
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  delay(100);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  delay(100);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  delay(100);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  delay(100);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  delay(100);
  digitalWrite(segF, HIGH);
  reset();
  }
  
  void circleAnti(){
  digitalWrite(segA, LOW);
  delay(100);
  digitalWrite(segA, HIGH);
  digitalWrite(segF, LOW);
  delay(100);
  digitalWrite(segF, HIGH);
  digitalWrite(segE, LOW);
  delay(100);
  digitalWrite(segE, HIGH);
  digitalWrite(segD, LOW);
  delay(100);
  digitalWrite(segD, HIGH);
  digitalWrite(segC, LOW);
  delay(100);
  digitalWrite(segC, HIGH);
  digitalWrite(segB, LOW);
  delay(100);
  digitalWrite(segB, HIGH);
  reset();
  }
  
void lineRL(int delayValue){
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segB, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segG, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit2, HIGH);
  digitalWrite(segG, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digitDP, HIGH);
  digitalWrite(segDP, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segG, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit4, HIGH);
  digitalWrite(segC, LOW);
  delay(delayValue);
}
  
void lineLR(int delayValue){
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segG, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digitDP, HIGH);
  digitalWrite(segDP, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit2, HIGH);
  digitalWrite(segG, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segG, LOW);
  delay(delayValue);
  reset();
}


void displayAll(int delayValue){
  #define SEGMENT_ON  LOW
  #define SEGMENT_OFF HIGH
  digitalWrite(segA, SEGMENT_ON);
  digitalWrite(segB, SEGMENT_ON);
  digitalWrite(segC, SEGMENT_ON);
  digitalWrite(segD, SEGMENT_ON);
  digitalWrite(segE, SEGMENT_ON);
  digitalWrite(segF, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_ON);
  delay(delayValue);
}
void displayDots() {
  #define DIGIT_ON  HIGH
  #define DIGIT_OFF  LOW

  digitalWrite(segDP, LOW);
  digitalWrite(digitDP, DIGIT_ON);
  delayMicroseconds(500);
  //digitalWrite(segDP, HIGH);
  //digitalWrite(digitDP, DIGIT_OFF);
}

void game2(){
  reset();
  secondsDisplay(1800);
  lineLR(150);
  lineRL(150);
  reset();
  clockDisplay(2500);
  secondsDisplay(3800);
  ball(300);
  ballCircular(300);
  ballCircular(250);
  ballCircular(100);
  ballCircular(50);
  ballCircular(50);
  secondsDisplay(1000);
  reset();
}

void circlePerimeter(int delayValue){
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segA, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit2, HIGH);
  digitalWrite(segA, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segA, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segB, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segC, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segD, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit2, HIGH);
  digitalWrite(segD, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segD, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segE, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segF, LOW);
  delay(delayValue);
}



void circlePerimeterAnti(int delayValue){
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segA, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segF, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segE, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit3, HIGH);
  digitalWrite(segD, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit2, HIGH);
  digitalWrite(segD, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segD, LOW);
  delay(delayValue);
    reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segC, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segB, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit1, HIGH);
  digitalWrite(segA, LOW);
  delay(delayValue);
  reset();
  digitalWrite(digit2, HIGH);
  digitalWrite(segA, LOW);
  delay(delayValue);
}
