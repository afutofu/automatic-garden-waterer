#include <virtuabotixRTC.h>

virtuabotixRTC myRTC(2,3,4);

// Vars for clock
int currentDay;
int dayDiff = 0;
bool firstRun = true;

// Vars for moisture sensor
int moistIn = A0;
float moisture;
float moistureThreshold = 500;

// Vars for relay
int relayPin = 12;

void setup() {
  Serial.begin(9600);

  // Will check input from moisture sensor
  pinMode(moistIn, INPUT);

  // Will close relay if moisture is low
  pinMode(relayPin, OUTPUT);

  // seconds, mins, hours, day of week, day of month, month, year
//  myRTC.setDS1302Time(50, 11, 11, 7, 17, 11, 2019);

  for( int i = 0; i < 5; i++){
    Serial.print(i);
    delay(250);
    Serial.print(".");
    delay(250);
    Serial.print(".");
    delay(250);
    Serial.print(".");
    delay(250);
  }

  Serial.println();
  
}

void loop() {
  // Before updating, store the current minute to check if minute has changed
  currentDay = myRTC.dayofmonth;

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

  if (myRTC.dayofmonth != currentDay){
    Serial.print("\nCurrent day from ");
    Serial.print(currentDay);
    
    Serial.print(" to ");
    currentDay = myRTC.dayofmonth;
    Serial.println(currentDay);

    moisture = analogRead(moistIn);

    Serial.print("Current moisture is: ");
    Serial.println(moisture);
    Serial.println();

    if(firstRun && moisture >= moistureThreshold) {
      digitalWrite(relayPin, HIGH);
      delay(5000);
      dayDiff = 0;
    }

    if (firstRun == false){
      dayDiff += 1;
    }


    if (moisture >= moistureThreshold && firstRun == false && dayDiff > 1){
      digitalWrite(relayPin, HIGH);
      delay(5000);
      dayDiff = 0;
    }

    digitalWrite(relayPin, LOW);
    firstRun = false;
  }
  
  // Delay for 1 second so the program doesn't print non-stop
  delay(1000);
}
