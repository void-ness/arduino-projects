const int trigpin = 7;
const int echopin = A2;
int a = 0;
char inp;

#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1);   // rx tx pins initialised

#include <AFMotor.h>
AF_DCMotor motor2(2);       // initialising motors
AF_DCMotor motor3(3);

void setup(){
  mySerial.begin(9600);       // initialised speed
  motor2.setSpeed(250);
  motor3.setSpeed(250);
  delay(5000);                // patience is important. to slow up the boot for idk why i did that.lol
  mySerial.println("programm on ");   
}

void loop(){
  digitalWrite(trigpin , LOW);       
  delayMicroseconds(5);                     // ultrasonic reading read and stored for the first time   
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  long duration=pulseIn(echopin,HIGH);
  long cm= (duration*0.034)/2;
  int a = cm;
  
  // in the below code i have implemented the safe feature which after detecting
  // an obstacle under a range of 18cm from car stops the car and reverses it to a safe distance of 18 cm from the obstacle
  
  if (a < 18 and a > 1){
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    mySerial.println("unsafe - moving backward");       // implementation of the safety feature
    while (a < 18){
      digitalWrite(trigpin , LOW);
      delayMicroseconds(5);
      digitalWrite(trigpin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigpin, LOW);  
      long duration=pulseIn(echopin,HIGH);
      long cm= (duration*0.034)/2;
      if (int(cm) > 18){
        a = 20;
        motor2.run(RELEASE);
        motor3.run(RELEASE);                  // car moved over to a safe distance
        mySerial.println("successfully moved to safe distance");
      }
    }
    delay(10);      
  }
      
  if (mySerial.available()>0){              
    inp = mySerial.read();          // reads user input
    mySerial.println( "entered value " + String(inp));
    if ( inp == 'F'){
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      mySerial.println("moving forward");         // moving the car forward mechanism
    }
    else if ( inp == 'B'){
      motor2.run(BACKWARD);
      motor3.run(BACKWARD);
      mySerial.println("moving backward");
    }
    else if ( inp == 'L'){
      motor2.run(FORWARD);
      motor3.run(BACKWARD);
      mySerial.println("moving left");
    }
    else if ( inp == 'R'){
      motor2.run(BACKWARD);
      motor3.run(FORWARD);
      mySerial.println("moving right");
    }  
  }  
  delay(100);           // a small delay to not fry up the arduino
} 
