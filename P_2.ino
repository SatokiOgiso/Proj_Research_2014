#include <Prescaler.h>

const char deviceNumber = 4;
long randNumber;
char Init_command=0;
char Flag =  0;
char Count = 0;
char sendFlag = 0;
int P_Time = 0;
int LedCount = 0;
unsigned long Time;
unsigned long StartTime;
unsigned long LedTime = 0;
unsigned char KeyNo = 2;
unsigned char RecNo = 0;
unsigned char MyDeviceNo = 2;   // 自局の識別デバイス番号
unsigned long timestamp = 0;
unsigned long count = 0;
/*******************************************************************************
 *  電源起動時とリセットの時だけのみ処理される関数(初期化と設定処理)            *
 *******************************************************************************/
void setup()
{
  Serial.begin(9600) ;	// ArduinoIDEと通信する為の初期化処理
  pinMode(13,OUTPUT);
  pinMode(8,INPUT);
  digitalWrite(13,LOW);
}
/*******************************************************************************
 *  繰り返し実行される処理の関数(メインの処理)                                  *
 *******************************************************************************/
void loop(){
  if(Flag == 0 && Serial.read() == 'A' ){
    Serial.println("START.");
    StartTime = micros();
    Flag = 1;
  }
  else if(Flag == 1){
    if(digitalRead(8) == LOW){
      Time = micros();
      while(digitalRead(8) == LOW);
      Time = micros() - Time;
      if(Time > 3000 && Time <= 5000 && LedCount < 50){
        if( micros() - LedTime < 100000 ){
          LedCount++;
        }
        Count = 1;
      }
      if(Count ==1){
        digitalWrite(13,HIGH);
        P_Time = (micros() - StartTime)/1000000;
        Serial.print("B\t");
        Serial.println(P_Time);
        LedTime = micros();
        delay(50);
      }
      Count = 0;
    }
    else if(digitalRead(8) == HIGH){
      Time = micros() - Time;
      if(Time > 1000000 ){
        digitalWrite(13,LOW);
        LedCount = 0;
      }
    }
  }
}






