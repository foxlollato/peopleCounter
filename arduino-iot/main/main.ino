#include <SoftwareSerial.h>

const byte rxPin = 2;
const byte txPin = 3;
const byte sIn = 5;
const byte sOut = 6;

const String server="SERVER_IP";
const String port="PORT";
const String ssid="SSID";
const String password="PASSWORD";

SoftwareSerial ESP8266 (rxPin, txPin);

void setup() {
  pinMode(sIn, INPUT);
  pinMode(sOut, INPUT);
  Serial.begin(9600);   
  ESP8266.begin(9600);
  delay(5000);
  ESP8266.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");  
}

void exec(String action){
  String cmd = "GET /"+action+" HTTP/1.1";
  ESP8266.println("AT+CIPSTART=\"TCP\",\""+server+"\","+port);
  delay(10);
  ESP8266.println("AT+CIPSEND=" + String(cmd.length()+4));
  delay(10);
  ESP8266.println(cmd);
  delay(10);
  ESP8266.println("");
  delay(250);
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
