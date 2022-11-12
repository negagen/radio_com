#include <Arduino.h>
#include <Servo.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;
Servo sv1;

void motores(int pin_a, int pin_b, int velocidad){
    if(velocidad>0){
        analogWrite(pin_a, velocidad);
        digitalWrite(pin_b, 0);
    }

    if(velocidad<0){
        analogWrite(pin_b, (-1)*velocidad);
        digitalWrite(pin_a, 0);
    }

    if(velocidad==0){
        digitalWrite(pin_a, 0);
        digitalWrite(pin_b, 0);
    }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  sv1.attach(3);
  sv1.write(0);

  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  if (!driver.init())
  {
    Serial.println("Couldn't connect!");
    delay(1000);
  }
  Serial.println("Is a me, a receiver!");
}

void loop()
{
  // put your main code here, to run repeatedly:
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  

  

  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    buf[buflen] = '\0';
    String parseString = String((char *)buf);
    int begin = parseString.indexOf('<');
    int limit = parseString.indexOf(',');
    int num1 = parseString.substring(begin+1, limit).toInt();
    begin = limit;
    limit = parseString.indexOf('>', limit+1);
    int num2 = parseString.substring(begin+1, limit).toInt();

    int per1 = (num1/1024.0) * 50;
    sv1.write(per1);
    Serial.println(per1);
    int per2 = (num2/1024.0 * 500) - 250;
    motores(5,6,per2);
    Serial.println(per2);

  }
}