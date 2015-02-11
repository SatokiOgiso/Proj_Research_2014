#include <Prescaler.h>
#include <MsTimer2.h>


//LED点滅処理用
volatile int ledval = 0;
volatile int nonCount = 0;
volatile int recvFlag = 0;

int nonCountThresh = 1; //
int dimmingRate = 10;
int flashCount = 0;
int flashCountThresh = 25;
int flashFlag = 0;
int led = 9;

// 赤外線受信用
int P_Time = 0;
unsigned long Time;
unsigned long StartTime;

/*******************************************************************************
 *  電源起動時とリセットの時だけのみ処理される関数(初期化と設定処理)            *
 *******************************************************************************/
void setup()
{
  Serial.begin(9600) ;	// ArduinoIDEと通信する為の初期化処理
  pinMode(8,INPUT);
  MsTimer2::set(10, updateLED); // 10ms period
  MsTimer2::start();
  Serial.println("START.");
  StartTime = micros();
}


// LED操作部
void updateLED() // This is the callback function of timer 2 interrupt
{
 if(recvFlag == 1){
   ledval += dimmingRate;
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


/*******************************************************************************
 *  繰り返し実行される処理の関数(メインの処理)                                  *
 *******************************************************************************/
void loop(){
  if(digitalRead(8) == LOW){
    Time = micros();
    while(digitalRead(8) == LOW);
    Time = micros() - Time;
    if(Time > 3000 && Time <= 5000 ){
      recvFlag = 1;
      P_Time = (micros() - StartTime)/1000000;
      Serial.print("B\t");
      Serial.println(P_Time);
      delay(50);
    }
  }
  else if(digitalRead(8) == HIGH){
    Time = micros() - Time;
    if(Time > 1000000 ){
      recvFlag = 0;
    }
  }
}

