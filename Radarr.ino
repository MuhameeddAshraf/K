#include <Servo.h>

Servo servo_1; // servo controller (multiple can exist)

int trig = 4; // trig pin for HC-SR04
int echo = 5; // echo pin for HC-SR04
int servo_pin = 3; // PWM pin for servo control
int led_1 = 6 ; // 
int led_2 = 8 ;
int Buzzer = 7 ;

int pos = 0;    // servo starting position
float duration,distance;

void setup()  {
  Serial.begin(115200);
  Serial.println("Radar Start");
  servo_1.attach(servo_pin); // start servo control
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
}


void loop() {
for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20); // delay to allow the servo to reach the desired position
    dist_calc(pos);
  }
 
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
    dist_calc(pos);
  }

}
float dist_calc(int pos){
  // trigger 40kHz pulse for ranging
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  // convert from duration for pulse to reach detector (microseconds) to range (in cm)
  duration = pulseIn(echo,HIGH); // duration for pulse to reach detector (in microseconds)
  distance = 100.0*(343.0*(duration/2.0))/1000000.0; // 100.0*(speed of sound*duration/2)/microsec conversion
   
    if( distance < 85 && distance >= 40 ) {
              digitalWrite(6,HIGH);   
             }
             
         else if( distance < 40 ) {
              digitalWrite(8,HIGH);    //Red led on
              digitalWrite(6,HIGH);    //blue led on
              digitalWrite(7,HIGH);    //buzzer on
             }
             
         else {
              digitalWrite(8,LOW);    //Red led on
              digitalWrite(6,LOW);   
              digitalWrite(7,LOW);    // buzzer on
          }
  
  Serial.print("pos is : "); 
  Serial.print(pos); // position of servo motor
  Serial.print(" , "); // comma separate variables
  Serial.print("distance is : "); // position of servo motor
  Serial.println(distance); // print distance in cm
}
