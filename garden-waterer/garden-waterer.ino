#include <virtuabotixRTC.h>

virtuabotixRTC myRTC(2,3,4);

// Vars for clock
int currentDay;
int dayDiff = 0;
bool firstRun = true;

// Vars for moisture sensor
int moistIn = A0;
float moisture;
float moistureThreshold = 430;

// Vars for relay
int relayPin = 12;
int dlayMinutes = 1;
int dlay = dlayMinutes* 30 * 1000;

void setup() {
  Serial.begin(9600);

  // Will check input from moisture sensor
  pinMode(moistIn, INPUT);

  // Will close relay if moisture is low
  pinMode(relayPin, OUTPUT);

  // seconds, mins, hours, day of week, day of month, month, year
//  myRTC.setDS1302Time(1, 29, 8, 6, 23, 11, 2019);

  for( int i = 20; i > 0; i--){
    Serial.print(i);
    delay(250);
    Serial.print(".");
    delay(250);
    Serial.print(".");
    delay(250);
    Serial.print(".");
    delay(250);
  }

  Serial.println(" Program is now starting");
  
}

void loop() {
  // Before updating, store the current day to check if day has changed
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

  // Print current moisture level to serial monitor
  moisture = analogRead(moistIn);
  Serial.print("Current moisture is: ");
  Serial.println(moisture);
  Serial.println();


  // Check if the day has changed
  if (myRTC.dayofmonth != currentDay){
    Serial.print("\nCurrent day from ");
    Serial.print(currentDay);
    
    Serial.print(" to ");
    currentDay = myRTC.dayofmonth;
    Serial.println(currentDay);

    // Will check moisture on first run and turn on relay if moisture is above threshold
    if(firstRun && moisture >= moistureThreshold) {
      digitalWrite(relayPin, HIGH);
      delay(dlay);
      dayDiff = 0;
    }

    if (firstRun == false){
      dayDiff += 1;
    }

    // Will check after 2 days and turn on if moisture is above threshold. If moisture is below threshold, then check again the following days
    if (moisture >= moistureThreshold && firstRun == false && dayDiff > 1){
      digitalWrite(relayPin, HIGH);
      delay(dlay);
      dayDiff = 0;
    }

    digitalWrite(relayPin, LOW);
    firstRun = false;
  }
  
  // Delay for 1 second so the program doesn't print non-stop
  delay(1000);
}
