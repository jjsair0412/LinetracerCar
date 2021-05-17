#include <SoftwareSerial.h> 
SoftwareSerial bluetooth(8, 9);

long time = millis();


const int AIA = 5;  //우 뒤
const int AIB = 6;  //우 앞
const int BIA = 10; //좌 뒤
const int BIB = 11; //좌 앞

const int SensorLeft = 2;
const int SensorRight = 3;

int trig = 13;
int echo = 12;


void setup() {
  bluetooth.begin(9600);  // 블루투스 통신 속도 설정
  
  pinMode(AIA,OUTPUT);
  pinMode(AIB,OUTPUT);
  pinMode(BIA,OUTPUT);
  pinMode(BIB,OUTPUT);

  pinMode(SensorLeft,INPUT);
  pinMode(SensorRight,INPUT);

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

}

void loop() {
  if(bluetooth.available()) {
   char data = (char)bluetooth.read();   // 블루투스 들어오는값 저장 data
    if(data == '1') {
      CarAuto(); //흰색선 밟으면 그냥 왼쪽으로 가는 CarAuto();
    }else if(data == '2') {
      CarStop();
  }else if(data=='3'){
    CarAuto2(); //흰색선 밟아도 무시하고 직진하는 CarAuto2();
  }else if(data=='4'){
    while(true){
    CarSelf(); // 첫번째 흰색선은 무시한후 주차칸으로들어가는 코드
   }
  }
 }
}

void CarSelf(){ //첫번째 흰색선은 무시한후 주차칸으로들어가는 코드
  boolean flag = 1;
  while(!bluetooth.available()) {
  digitalWrite(trig, LOW); 
   delayMicroseconds(2);     
   digitalWrite(trig, HIGH); 
   delayMicroseconds(10);    
   digitalWrite(trig, LOW);
   unsigned long duration = pulseIn(echo,HIGH);
   float distance = ((float)(340*duration)/10000)/2; 
 
   int SL, SR;
   SL = digitalRead(SensorLeft);
   SR = digitalRead(SensorRight);
    
    
    
    if(distance <= 5) {
    CarStop();
    
   }else {
    if(SL == HIGH && SR == HIGH) {
      CarGo();
    }else if(SL == LOW && SR == HIGH) {
      CarRight();
    }else if(SL == HIGH && SR == LOW) {
      CarLeft();
    }else if(SL == LOW && SR == LOW){
      
     if(flag == 1){
     CarGo();
     flag =0;
    }else if(flag == 0){
     CarAuto();
    }
   }
  }
 }
}


void CarAuto(){ //흰색선 밟으면 그냥 왼쪽으로 가는 CarAuto();
  while(!bluetooth.available()) {

   digitalWrite(trig, LOW); 
   delayMicroseconds(2);     
   digitalWrite(trig, HIGH); 
   delayMicroseconds(10);    
   digitalWrite(trig, LOW);
   unsigned long duration = pulseIn(echo,HIGH);
   float distance = ((float)(340*duration)/10000)/2; 
    
   int SL, SR;
   SL = digitalRead(SensorLeft);
   SR = digitalRead(SensorRight);

   if(distance <= 5) {
    CarStop();
   }else {
    if(SL == HIGH && SR == HIGH) {
      CarGo();
    }else if(SL == LOW && SR == HIGH) {
      CarRight();
    }else if(SL == HIGH && SR == LOW) {
      CarLeft();
    }else {
      CarLeft();
    }
   }
  }
}

void CarAuto2(){ //흰색선 밟아도 무시하고 직진하는 CarAuto2();
  while(!bluetooth.available()) {

   digitalWrite(trig, LOW); 
   delayMicroseconds(2);     
   digitalWrite(trig, HIGH); 
   delayMicroseconds(10);    
   digitalWrite(trig, LOW);
   unsigned long duration = pulseIn(echo,HIGH);
   float distance = ((float)(340*duration)/10000)/2; 
    
   int SL, SR;
   SL = digitalRead(SensorLeft);
   SR = digitalRead(SensorRight);

  
   if(distance <= 5) {
    CarStop();
   }else {
    if(SL == HIGH && SR == HIGH) {
      CarGo();
    }else if(SL == LOW && SR == HIGH) {
      CarRight();
    }else if(SL == HIGH && SR == LOW) {
      CarLeft();
    }else {
      CarGo();
    }
   }
  }
}



void CarGo(){
  //모터의 물리적 힘차이로 인해 모터마다 주는 힘이 다름
  while(!bluetooth.available()) {
    analogWrite(AIA,0);       // 우 뒤
    analogWrite(AIB,150);     // 우 앞
    analogWrite(BIA,0);       // 좌 뒤
    analogWrite(BIB,135);     // 좌 앞
    break;
  }
}

void CarBack(){
  while(!bluetooth.available()) {
    analogWrite(AIA,150);
    analogWrite(AIB,0);
    analogWrite(BIA,135);
    analogWrite(BIB,0);
    break;
  }
}

void CarRight(){
  while(!bluetooth.available()) {
    analogWrite(AIA,0);
    analogWrite(AIB,0);
    analogWrite(BIA,0);
    analogWrite(BIB,135);
    break;
  }
}

void CarLeft(){
  while(!bluetooth.available()) {
    analogWrite(AIA,0);
    analogWrite(AIB,150);
    analogWrite(BIA,0);
    analogWrite(BIB,0);
    break;
  }
}

void CarStop(){
  while(!bluetooth.available()) {
    analogWrite(AIA,0);
    analogWrite(AIB,0);
    analogWrite(BIA,0);
    analogWrite(BIB,0);
    break;
  }
}
