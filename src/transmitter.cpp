#include <Arduino.h>
#include <RH_ASK.h>

#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

String output = "";

void writeFrame(){
  output = "";
  output.concat("<");
  output.concat(String(analogRead(A0)));
  output.concat(",");
  output.concat(String(analogRead(A1)));
  output.concat(">");
}

void setup()
{
  Serial.begin(9600); // Debugging only
  if (!driver.init())
  {
    Serial.println("init failed");
    delay(1000);
  }

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  Serial.println('Is a me, a transmitter');
}

void loop()
{
  char msg[10];
  writeFrame();
  output.toCharArray(msg,10);
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  //Serial.println(msg);
}