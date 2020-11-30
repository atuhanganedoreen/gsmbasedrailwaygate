#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial Serial1(10, 11);
Servo myservo;
int x, y;
int pos = 0;
char *test="$GPRMC";
void initModule(String cmd, char *res, int t)
{
while(1)
{
Serial.println(cmd);
Serial1.println(cmd);
delay(100);
while(Serial1.available()>0)
{
if(Serial1.find(res))
{
Serial.println(res);
delay(t);
return;
}
else
{
Serial.println("Error");
}
}
delay(t);
}
}
void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("System Started.....");
  delay(1000);
  Serial.println("Initializing....");
  initModule("AT","OK",1000);
  initModule("ATE1","OK",1000);
  initModule("AT+CPIN?","READY",1000);
  initModule("AT+CMGF=1","OK",1000);
  initModule("AT+CNMI=2,2,0,0,0","OK",1000);
  Serial.println("Initialized Successfully");  
  myservo.attach(9);
}

void loop() {
  readSensor();

  if (y == LOW)
  {
    servoUp();
  }
 else if (x == LOW)
  {
    servoDown();
    delay(1000);
   Send();
  }
}

void readSensor()
{
  x = digitalRead(A5);
  y = digitalRead(A4);
}

void servoUp()
{
  for (pos = 0; pos <= 90; pos += 1)
  {
    myservo.write(pos);
    delay(30);
  }
}
void servoDown()
{
  for (pos = 90; pos >= 0; pos -= 1)
  {  
     myservo.write(pos);
     delay(30);
     
  }
}
void Send()
{ 
   Serial1.println("AT");
   delay(500);
   serialPrint();
   Serial1.println("AT+CMGF=1");
   delay(500);
   serialPrint();
   Serial1.print("AT+CMGS=");
   Serial1.print('"');
   Serial1.print("+256706026219");    //mobile no. for SMS alert
   Serial1.println('"');
   delay(500);
   serialPrint();
   Serial1.println("Hi Mrs Doreen, A train is approaching from a distance");
   delay(500);
   serialPrint();
   Serial1.println("Make sure the gate is closed and please stop traffic from crossing");
   delay(500);
   Serial1.write(26);
   delay(500);
   serialPrint();
}

void serialPrint()
{
  while(Serial1.available()>0)
  {
    Serial.print(Serial1.read());
  }
}
