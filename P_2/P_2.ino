#include <Prescaler.h>

int P_Time = 0;
unsigned long Time;
unsigned long StartTime;
/*******************************************************************************
 *  電源起動時とリセットの時だけのみ処理される関数(初期化と設定処理)            *
 *******************************************************************************/
void setup()
{
  Serial.begin(9600) ;	// ArduinoIDEと通信する為の初期化処理
  pinMode(13,OUTPUT);
  pinMode(8,INPUT);
  digitalWrite(13,LOW);
  while(Serial.read() != 'A');
  Serial.println("START.");
  StartTime = micros();
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
      digitalWrite(13,HIGH);
      P_Time = (micros() - StartTime)/1000000;
      Serial.print("B\t");
      Serial.println(P_Time);
      delay(50);
    }
  }
  else if(digitalRead(8) == HIGH){
    Time = micros() - Time;
    if(Time > 1000000 ){
      digitalWrite(13,LOW);
    }
  }
}

