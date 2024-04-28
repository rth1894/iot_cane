// initializing pins
const int trigPin = 13;
const int buzzerPin = 8;
const int echoPin = 12;
const int waterSensorPin = 7;
const int mosfetGatePin = 3;
const int motorOnTime = 2000;

// initalize variables
int distanceCm, distanceInch, waterState;
long time;

void setup() {
  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(waterSensorPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(mosfetGatePin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  time = pulseIn(echoPin, HIGH);

  // calculate distance
  distanceCm = time * 0.034 / 2;

  // Water detection sensor code
  waterState = digitalRead(waterSensorPin);
  if (waterState == HIGH && digitalRead(buttonPin) == HIGH) {
    digitalWrite(mosfetGatePin, HIGH);
    delay(motorOnTime);
    digitalWrite(mosfetGatePin, LOW);
  }

  // Ultrasonic sensor code
  if (distanceCm < 25) { 
    digitalWrite(buzzerPin, HIGH);  // Buzzer ON
  } else {
    digitalWrite(5, LOW);   // Buzzer OFF
  }
}
