#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = "NCHxI7jjrD-cVpPB1q2008qir_9vDJM9"; //YourToken
// Your WiFi credentials.
char ssid[] = "Redmi"; //YourNetworkName
char pass[] = "123456789"; //YourPassword
BlynkTimer timer;
const byte L298N_A_pin = 1; // GPI05
const byte L298N_A_In1_pin = 33; //GPI04
const byte L298N_A_In2_pin = 32; //GPI0
const byte L298N_B_pin = 6; //GPI12
const byte L298N_B_In3_pin = 35; // GPI02
const byte L298N_B_In4_pin = 34; // GPIO14
const byte forba_pin = 12; //GPI016  //forba
const byte rile_pin = 13; //GPI016  //rile


/*
 * blynk ekranı
 * V0 joystick,  
 * v1,v2, v3, v4,v5,v6,v7,v8 Led  
 * v10  button push
 * v11 button switch
 */
void motorSpeed(byte prmA, byte prmA1, byte prmA2,byte prmB, byte prmB1, byte prmB2)
{
  digitalWrite(L298N_A_pin,prmA);
  digitalWrite(L298N_B_pin,prmB);
  digitalWrite(L298N_A_In1_pin,prmA1);
  digitalWrite(L298N_A_In2_pin,prmA2);
  digitalWrite(L298N_B_In3_pin,prmB1);
  digitalWrite(L298N_B_In4_pin,prmB2);
 
}
BLYNK_WRITE(V1) {
/* forward back*/  
  int x1 = param[0].asInt();
  int y1 = param[1].asInt();
  if ((x1==0) && (y1==0)) // stop
 {
   motorSpeed(HIGH,LOW,LOW,HIGH,LOW,LOW); 
 }
  if ((x1==0) && (y1>0)) // forward
 {
  if (y1==1){ motorSpeed(HIGH,HIGH,LOW,HIGH,HIGH,LOW); }
  else { motorSpeed(HIGH,HIGH,LOW,HIGH,HIGH,LOW); }

 }
 
  
 if ((y1<0) && (x1<0))// back left
    motorSpeed(HIGH,LOW,LOW,HIGH,LOW,HIGH); 
 else if ((y1<0) && (x1>0))// back right 
    motorSpeed(HIGH,LOW,HIGH,HIGH,LOW,LOW); 
 else if ((y1<0) && (x1==0))// back
   motorSpeed(HIGH,LOW,HIGH,HIGH,LOW,HIGH); 
}
BLYNK_WRITE(V2) {
/* right left*/  
   int x2 = param[0].asInt();
  int y2 = param[1].asInt();
if ((x2==0) && (y2==0)) // stop
 {
   motorSpeed(HIGH,LOW,LOW,HIGH,LOW,LOW); 
 }
  
  if ((y2==0) && (x2>0))// + right
 { 
  motorSpeed(HIGH,HIGH,LOW,HIGH,LOW,HIGH); 
  }
 else if ((y2>0) && (x2>0))// -right
 {  
  motorSpeed(HIGH,HIGH,LOW,HIGH,LOW,LOW); 
  }
 else if ((y2==0) && (x2<0))// +left
 { 
  motorSpeed(HIGH,LOW,HIGH,HIGH,HIGH,LOW); 
  }
 else if ((y2>0) && (x2<0))// -left
 {   
  motorSpeed(HIGH,LOW,LOW,HIGH,HIGH,LOW); }
}

// x =  -2 -1 0 1 2 
// Y =  -2 -1 0 1 2 
 

void setup() {
  Serial.begin(115200);
  pinMode(L298N_A_In1_pin,OUTPUT);
  pinMode(L298N_A_In2_pin,OUTPUT);
  pinMode(L298N_B_In3_pin,OUTPUT);
  pinMode(L298N_B_In4_pin,OUTPUT);

 digitalWrite(L298N_A_In1_pin,LOW);
 digitalWrite(L298N_A_In2_pin,LOW);
 digitalWrite(L298N_B_In3_pin,LOW);
 digitalWrite(L298N_B_In4_pin,LOW);

  Blynk.begin(auth, ssid, pass);
}



void loop() {
  Blynk.run();
  timer.run();
}
