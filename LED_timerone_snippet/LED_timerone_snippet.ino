#include <MsTimer2.h>

volatile int ledval = 0;

int led = 9;

void setup()
{
  MsTimer2::set(10, updateLED); // 500ms period
  MsTimer2::start();
  Serial.begin(9600);
}

void updateLED()
{
 analogWrite(led, ledval++);
 if(ledval > 255 ) ledval = 255;
 if(ledval < 0) ledval = 0;
}

void loop()
{
  unsigned int ledval_copy;
  noInterrupts();
  ledval_copy = ledval;
  interrupts();
  Serial.println(ledval_copy);
}
