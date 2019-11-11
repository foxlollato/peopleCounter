#include <SoftwareSerial.h>

const byte rxPin = 2;
const byte txPin = 3;
const byte sIn = 5;
const byte sOut = 6;

SoftwareSerial ESP8266 (rxPin, txPin);

void setup() {
  pinMode(sIn, INPUT);
  pinMode(sOut, INPUT);
  Serial.begin(9600);   
  ESP8266.begin(9600);
}

void printResponse() {
  while (ESP8266.available()) {
    Serial.println(ESP8266.readStringUntil('\n')); 
  }
}

void exec(String action){
  String cmd = "GET /"+action+" HTTP/1.1";
  ESP8266.println("AT+CIPSTART=\"TCP\",\"192.168.0.112\",8081");
  delay(150);   
  ESP8266.println("AT+CIPSEND=" + String(cmd.length() + 4));
  delay(150);
  ESP8266.println(cmd);
  delay(150);
  ESP8266.println("");
  delay(1000);
}

void loop() {

    if(digitalRead(sIn) == LOW){
      delay(10);
      while(digitalRead(sIn) == LOW){
        delay(10);
      }
      exec("entrada");
    }
    if(digitalRead(sOut) == LOW){
      delay(10);
      while(digitalRead(sOut) == LOW){
        delay(10);
      }
      exec("saida");
    }

  if (ESP8266.available()) {
    Serial.write(ESP8266.read());
  }
}