#include <Prescaler.h>

int P_Time = 0;
unsigned long Time;
unsigned long StartTime;

unsigned int led_value = 0;

int LED = 13;


/*******************************************************************************
 *  電源起動時とリセットの時だけのみ処理される関数(初期化と設定処理)            *
 *******************************************************************************/
void setup()
{
  Serial.begin(9600) ;	// ArduinoIDEと通信する為の初期化処理
  pinMode(LED,OUTPUT);
  pinMode(8,INPUT);
  digitalWrite(LED,LOW);
//  while(Serial.read() != 'A');
  Serial.println("START.");
  StartTime = micros();
}


unsigned int led_update(unsigned int led_value, unsigned int prescale_value, int stepsize)
{
  unsigned long Now;
  static unsigned long LastUpdateTime = 0;
  
  Now = micros();
  
  if((Now - LastUpdateTime) > prescale_value){
    led_value = led_value + stepsize;
    LastUpdateTime = Now;
  }
  
  return led_value;
}

unsigned int led_validate(unsigned int led_value)
{
  unsigned long Now;
  static unsigned long LastLEDChange = 0;
  
  Now = micros();
  
  
  
  if(led_value > 255)  led_value = 255;
  if(led_value < 0)    led_value = 0;
  
  return led_value;
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
      digitalWrite(LED,HIGH);
      P_Time = (micros() - StartTime)/1000000;
      Serial.print("B\t");
      Serial.println(P_Time);
      delay(50);
    }
  }
  else if(digitalRead(8) == HIGH){
    Time = micros() - Time;
    if(Time > 1000000 ){
      digitalWrite(LED,LOW);
    }
  }
}

