// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN1  10  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define TRIGGER_PIN2  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2    8  // Arduino pin tied to echo pin on the ultrasonic sensor.
const int leftForward = 2;
const int leftBackward = 3;
const int rightForward = 4;
const int rightBackward = 5;
const int minDistance = 20;


NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void stop() {
  Serial.println("stopped");
  digitalWrite(leftForward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightBackward, LOW);
}

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
}

void loop() {
  delay(100);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int front = sonar1.ping(); // Send ping, get ping time in microseconds (uS). 
  unsigned int back = sonar2.ping(); // Send ping, get ping time in microseconds (uS). 
  unsigned int front_mov = front / US_ROUNDTRIP_CM;
  unsigned int back_mov = back / US_ROUNDTRIP_CM;
  Serial.print("Ping: ");
  Serial.print(front / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.print("cm ");
  Serial.print(back / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm ");
  
  // if ((front == 0 && back == 0) && front <= minDistance && back <= minDistance) {
  //   stop();
  // }
  if (front_mov != 0 && front_mov <= minDistance) {
  	Serial.println("Going Backward");
	digitalWrite(leftForward, LOW);
	digitalWrite(rightForward, LOW);
	digitalWrite(leftBackward, HIGH);
	digitalWrite(rightBackward, HIGH);
  }
  else if (back_mov != 0 && back_mov <= minDistance) {
  	Serial.println("Going Forward");
	digitalWrite(leftBackward, LOW);
	digitalWrite(rightBackward, LOW);
	digitalWrite(leftForward, HIGH);
	digitalWrite(rightForward, HIGH);
  }
  else {
    stop();
  }
}