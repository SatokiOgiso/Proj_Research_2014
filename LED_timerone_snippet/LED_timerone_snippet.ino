#include <MsTimer2.h>

volatile int ledval = 0;
volatile int nonCount = 0;
volatile int recvFlag = 0;

int nonCountThresh = 1; //
int flashCount = 0;
int flashCountThresh = 25;
int flashFlag = 0;
int led = 9;

void setup()
{
  pinMode(13, OUTPUT);
  MsTimer2::set(10, updateLED); // 10ms period
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
 if(ledval == 0){
   flashCount ++;
   if(flashCount > flashCountThresh){
     flashCount = 0;
     if(flashFlag == 1){
       analogWrite(led, 255); 
       flashFlag = 0;
     }else{
       analogWrite(led, 0); 
       flashFlag = 1;
     }
   }
 }else{
   analogWrite(led, ledval);
 }
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
