#include <MsTimer2.h>

volatile int ledval = 0;
volatile int nonCount = 0;
volatile int recvFlag = 0;

int nonCountThresh = 5; //
int led = 9;

void setup()
{
  pinMode(13, OUTPUT);
  MsTimer2::set(10, updateLED); // 500ms period
  MsTimer2::start();
  Serial.begin(9600);
}

void updateLED() // This is the callback function of timer 2 interrupt
{
 if(recvFlag == 1){
   ledval += 2;
   nonCount = 0;
 }else{
   nonCount ++;
   if(nonCount > nonCountThresh){
     ledval --;
     nonCount = 0;
   }
 }
 
 ledval = validateLED(ledval);
 analogWrite(led, ledval);
}

int validateLED(int ledval)
{
 if(ledval > 255 ) ledval = 255;
 if(ledval < 0) ledval = 0; 
 return ledval;
}


void loop()
{
  unsigned int ledval_copy;
  noInterrupts();
  ledval_copy = ledval;
  interrupts();
  Serial.println(ledval_copy);
  recvFlag = 1;
  digitalWrite(13, recvFlag);
  delay(5000);
  recvFlag = 0;
  digitalWrite(13, recvFlag);
  delay(5000);
  recvFlag = 1;
  digitalWrite(13, recvFlag);
  delay(2000);
  recvFlag = 0;
  digitalWrite(13, recvFlag);
  delay(10000);
}
