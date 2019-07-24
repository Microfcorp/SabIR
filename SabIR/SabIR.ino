#include <IRremote.h>

#define StartVolume 4
#define MaxVolume 16
#define Run() irsend.sendNEC(0x42BD50AF, 32); Standby =! Standby
#define Input() irsend.sendNEC(0x42BD08F7, 32); Input =! Input
#define Mode() irsend.sendNEC(0x42BD48B7, 32); Mode =! Mode
#define VolumeUp() irsend.sendNEC(0x42BDE01F, 32); Volume++; if(Volume < 0) Volume = 0; if(Volume > MaxVolume) Volume = MaxVolume
#define VolumeDown() irsend.sendNEC(0x42BD6897, 32); Volume--; if(Volume < 0) Volume = 0; if(Volume > MaxVolume) Volume = MaxVolume
#define Default() irsend.sendNEC(0x42BD00FF, 32); Volume = StartVolume

IRsend irsend;

bool Standby = false;
bool Input = false;
bool Mode = true; //true=5.1 false 2.1

int Volume = StartVolume;

void setup()
{
  pinMode(22, 2);
  pinMode(24, 2);
  pinMode(26, 2);
  pinMode(28, 2);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(22) == 0 & digitalRead(24) == 0){
    Run();
    delay(100);
    Standby = false;
  }
  else if(digitalRead(22) == 0)
    SendIR_PC(100);  
  else if(digitalRead(24) == 0)
    SendIR_51(100);
  

  if(digitalRead(28) == 0 & digitalRead(26) == 0){
    Default();
    delay(100);  
  }
  else if(digitalRead(28) == 0){
    VolumeUp();
    delay(100);  
  }
  else if(digitalRead(26) == 0){
    VolumeDown();
    delay(100);
  }

  if (Serial.available()) {
    String data = Serial.readString();
    if(data == "GetVolume"){
      Serial.println(Volume);
    }
    else if(data == "VolumeUp"){
      VolumeUp();
      delay(100);
      Serial.println(Volume);
    }
    else if(data == "VolumeDown"){
      VolumeDown();
      delay(100);
      Serial.println(Volume);
    }
    else if(data == "Mode"){
      Mode();
      delay(100);
      Serial.println(Volume);
    }
    else if(data == "Input"){
      Input();
      delay(100);
      Serial.println(Volume);
    }
    else if(data == "Run"){
      Run();
      delay(100);
      Serial.println(Volume);
    }
    else if(data == "Default"){
      Default();
      delay(100);
      Serial.println(Volume);
    }
  }
}

int SendIR_PC(int sleep){
  if(!Standby){
    Run();
    delay(sleep);
  }
  if(!Input){
    Input();
    delay(sleep);
  }
  Mode = false;
  if(!Mode){
    Mode();  
    delay(sleep);
  }
  //ChangeVolume(2);
}

int SendIR_51(int sleep){
  if(!Standby){
    Run();
    delay(sleep);
  }
  if(Input){
    Input();
    delay(sleep);
  }
  if(!Mode){
    Mode();  
    delay(sleep);
  }
  //ChangeVolume(2);
}

/*int ChangeVolume(byte a){
  if(Volume < a){     
    //VolumeUp();
    for(int i = 0; i <= (a - Volume)+1; i++){
      VolumeUp();
      delay(100);
      Serial.println("UP");
    }
    //VolumeUp(); 
  }
  else if(Volume > a){    
    //VolumeDown();
    for(int i = 0; i <= (Volume - a)+1; i++){
      VolumeDown();
      delay(100);
      Serial.println("Down");
    }
    //VolumeDown();
  } 
  //Volume = a;
}*/

