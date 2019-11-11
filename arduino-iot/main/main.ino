#include <SoftwareSerial.h>

//set ESP8266 wireless controller pins
const byte rxPin = 2;
const byte txPin = 3;

//set in sensor pin
const byte sIn = 5;
//set out sensor pin
const byte sOut = 6;

//server and wireless settings
const String server="SERVER_IP";
const String port="PORT";
const String ssid="SSID";
const String password="PASSWORD";

//instantiate serial object to communicate with esp8266 over pins rxPin txPin
SoftwareSerial ESP8266 (rxPin, txPin);

void setup() {
  //set sensor pins for input mode
  pinMode(sIn, INPUT);
  pinMode(sOut, INPUT);
  //begin serial communication: "Serial" for Arduino console and "ESP8266" for wireless controller
  Serial.begin(9600);   
  ESP8266.begin(9600);
  //Delay to avoid missconfiguration for wireless setup
  delay(5000);
  ESP8266.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");  
}

void exec(String action){
  //Message format to API
  String cmd = "GET /"+action+" HTTP/1.1";
  //start tcp communication from esp8266 to server
  ESP8266.println("AT+CIPSTART=\"TCP\",\""+server+"\","+port);
  delay(10);
  //send message length
  ESP8266.println("AT+CIPSEND=" + String(cmd.length()+4));
  delay(10);
  //send message
  ESP8266.println(cmd);
  delay(10);
  //send blank character to end message
  ESP8266.println("");
  delay(250);
}

void loop() {
    //"listening" IN sensor value. Wanted value = LOW
    if(digitalRead(sIn) == LOW){
      delay(10);
      //if sensor blocked, wait unblock
      while(digitalRead(sIn) == LOW){
        delay(10);
      }//then, call exec function and pass action according sensor
      exec("entrada");
    }

    //same as above, but for OUT sensor
    if(digitalRead(sOut) == LOW){
      delay(10);
      while(digitalRead(sOut) == LOW){
        delay(10);
      }
      exec("saida");
    }
  //uncomment to get some log from esp8266
  // if (ESP8266.available()) {
  //   Serial.write(ESP8266.read());
  // }
}
