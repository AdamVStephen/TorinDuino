/**
* Sonar.ino : credit to a YouTube presentation TBA
*
* Simple distance detection using an SRF004 Ultrasonic sensor and basic speaker.
*
* Component ref : www.rev-ed.co.uk/cods/srf004.pdf
* Pinout : 5 pins numbered 1..5 from left to right looking at ultrasound side of board with pins at bottom edge
* 1 = GND ; 2 = GND ; 3 = Trigger Pulse Input ; 4 = Echo Pulse Output ; 5 = 5V Supply
* Circuit :
*
* Arduino 5V : SRF004.5
* Arduino GND : SRF004.1
* Arduino Pin 9 : SRF004.3
* Arduino Pin 8 : SRF004.4
* SRF004.2 N/C
* Arduino GND : Speaker GND
* Arduino Pin 10 : Speaker +VCC
*
*/


#define trigPin 9
#define echoPin 8
#define beepPin 10
//#define scalingfactor 0.1
#define scalingfactor 10

float inches=0.0;
unsigned long duration=0;
unsigned long maxtime=1000;
unsigned long i=1;
unsigned long time2=0;
unsigned long time1=0;

void setup(){
  Serial.begin(115200);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(beepPin,OUTPUT);
}

void logdistance(){
  time1=millis();
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  //inches=duration/148;
  inches = duration *0.034/2;
  time2=millis();
  maxtime=scalingfactor*inches;
  
}

void delayandcheckdistance(){
  i=1;
  while(1){
    if(i%60==0){
      logdistance();
    }
    delay(1);
    ++i;
    if(i>=maxtime){
     break;
    }
  }
}

void beep(){
  digitalWrite(beepPin,HIGH);
  delay(90);
  logdistance();
  //delay(maxtime);
  if(time2-time1<30){
    delay(60-(time2-time1));
  }
  digitalWrite(beepPin,LOW);
}

int lp = 1;
  
void loop(){
  beep();
  delayandcheckdistance();
  lp++;
  if (lp%10 == 0) { 
     Serial.println(lp);
  Serial.println("Distance in inches is");
   Serial.println(inches);
  }
}

