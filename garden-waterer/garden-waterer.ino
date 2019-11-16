#include <virtuabotixRTC.h>

virtuabotixRTC myRTC(6,7,8);

int outPin = 13;
int currentMin;
bool firstRun = true;

void setup() {
  Serial.begin(9600);

  // Will output to pin 13 if minute has changed
  pinMode(outPin, OUTPUT);

  // seconds, mins, hours, day of week, day of month, month, year
//  myRTC.setDS1302Time(20, 8, 10, 6, 16, 11, 2019);
}

void loop() {
  // Before updating, store the current minute to check if minute has changed
  currentMin = myRTC.minutes;

  // Update clock module to real time
  myRTC.updateTime();

  // Print current date and time to serial monitor
  Serial.print("Current Date / Time: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);

  if (myRTC.minutes != currentMin){
    Serial.print("Current minute from ");
    Serial.print(currentMin);
    
    Serial.print(" to ");
    currentMin = myRTC.minutes;
    Serial.println(currentMin);

    digitalWrite(outPin, HIGH);

    if (firstRun == false){
      delay(10000);
    }

    firstRun = false;
  }else{
    digitalWrite(outPin, LOW);
  }
  
  // Delay for 1 second so the program doesn't print non-stop
  delay(1000);
}
