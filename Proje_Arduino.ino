#include<SoftwareSerial.h>

SoftwareSerial BTSerial(8,9);

#define R 13
#define G 12
#define B 11
#define m1 5
#define m2 6
#define BuzzerPin 2
#define LedPin 3
#define NemSensoruPin A0

void setup(){

  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(BuzzerPin,OUTPUT);
  pinMode(LedPin,OUTPUT);
  pinMode(NemSensoruPin,OUTPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);
  
}

const int kuru = 400;
int nemDegeri = 0;
int su = 0;
int gelenVeri = 0;

void loop(){

  if(BTSerial.available()){

    gelenVeri = BTSerial.read();

    if(gelenVeri != 253 && gelenVeri != 254 && gelenVeri != 0){
      su = gelenVeri;
      BTSerial.print(su);
      delay(1000);
    }

    if(gelenVeri == 253) {
      while((gelenVeri == 253 || gelenVeri == 0) && gelenVeri != 254 && su != 0){

        Motor_Calisiyor();
        delay(1000);
        Motor_Durdu();

        su -= 1;
        BTSerial.print(su);

        delay(1000);

        if(BTSerial.available()){
          gelenVeri = BTSerial.read();
        }

        if(gelenVeri != 0 && gelenVeri != 253 && gelenVeri != 254){
          su = gelenVeri;
          gelenVeri = 0;
          BTSerial.print(su);
        }
      }

      gelenVeri = 0;
    }

    if(gelenVeri == 254){
      while((gelenVeri == 254 || gelenVeri == 0) && gelenVeri != 253){

        Motor_Durdu();

        delay(1000);

        if(BTSerial.available()){
          gelenVeri = BTSerial.read();
        }

        if(gelenVeri != 0 && gelenVeri != 253 && gelenVeri != 254){
          su = gelenVeri;
          gelenVeri = 0;
          BTSerial.print(su);
        }
      }

      gelenVeri = 0;
    }
  }

  if(su >= 1){

    RGB_Yesil_Yansin();
    Led_Yaniyor();

    nemDegeri = analogRead(NemSensoruPin);

    if(nemDegeri >= kuru) {

      Motor_Calisiyor();
      delay(1000);
      Motor_Durdu();

      su -= 1;

      BTSerial.print(su);

      delay(1000);

      if(BTSerial.available()){
        
        gelenVeri = BTSerial.read();
        
        if(gelenVeri != 253 && gelenVeri != 254 && gelenVeri != 0){
          su = gelenVeri;
          delay(1000);
          BTSerial.print(su);
        }
      }

      delay(10*1000);
      
    }
  }

  else{

    Led_Sondu();

    RGB_Kirmizi_Yansin();
    Motor_Durdu();
    Buzzer_Calisiyor();
    delay(50);
    Buzzer_Durdu();

  }

  if(BTSerial.available())
     BTSerial.print(su);

  delay(1000);
}

void RGB_Sondu(){
  analogWrite(R,0);
  analogWrite(G,0);
  analogWrite(B,0);
}

void RGB_Kirmizi_Yansin(){
  analogWrite(R,255);
  analogWrite(G,0);
  analogWrite(B,0);
}

void RGB_Yesil_Yansin(){
  analogWrite(R,0);
  analogWrite(G,255);
  analogWrite(B,0);
}

void Motor_Calisiyor(){
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
}

void Motor_Durdu(){
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
}

void Buzzer_Calisiyor(){
  digitalWrite(BuzzerPin,HIGH);
}

void Buzzer_Durdu(){
  digitalWrite(BuzzerPin,LOW);
}

void Led_Yaniyor(){
  digitalWrite(LedPin,HIGH);
}

void Led_Sonlu(){
  digitalWrite(LedPin,LOW);
}
