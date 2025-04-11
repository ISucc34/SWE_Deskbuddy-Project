#include <Servo.h>
int(D12) = 12;
Servo myservo;

void setup() {
  // put your setup code here, to run once:
myservo.attach(A3);
pinMode(D12,INPUT);
}



void loop() {
  // put your main code here, to run repeatedly:

int(val) = digitalRead(D12);
 if (val == HIGH) {
  myservo.write(0);
 }

}
