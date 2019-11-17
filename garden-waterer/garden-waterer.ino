#include <virtuabotixRTC.h>

virtuabotixRTC myRTC(2,3,4);

// Vars for clock
int currentMin;
int minDiff = 0;
bool firstRun = true;

// Vars for moisture sensor
int moistIn = A0;
float moisture;

// Vars for relay
int relayPin = 12;

void setup() {
  Serial.begin(9600);

  // Will check input from moisture sensor
  pinMode(moistIn, INPUT);

  // Will close relay if moisture is low
  pinMode(relayPin, OUTPUT);

  // seconds, mins, hours, day of week, day of month, month, year
  myRTC.setDS1302Time(50, 11, 11, 7, 17, 11, 2019);
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
    Serial.print("\nCurrent minute from ");
    Serial.print(currentMin);
    
    Serial.print(" to ");
    currentMin = myRTC.minutes;
    Serial.println(currentMin);

    moisture = analogRead(moistIn);

    Serial.print("Current moisture is: ");
    Serial.println(moisture);
    Serial.println();

    if (firstRun == false){
      minDiff += 1;
    }


    if (moisture >= 550 && firstRun == false && minDiff > 1){
      digitalWrite(relayPin, HIGH);
      delay(5000);
      minDiff = 0;
    }

    digitalWrite(relayPin, LOW);
    firstRun = false;
  }
  
  // Delay for 1 second so the program doesn't print non-stop
  delay(1000);
}
