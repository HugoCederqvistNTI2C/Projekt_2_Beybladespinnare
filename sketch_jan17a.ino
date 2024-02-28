#include <Servo.h>  // Inkludera Servo biblioteket

const int button = 1;        // knappen är ansluten till pin 1 på Arduino-brädet
const int relay_motor = 2;   // reläet är anslutet till pin 2 på Arduino-brädet

int eButton;
int lastButtonState;
int currentButtonState;
Servo myServo;  // Skapa ett servo-objekt för att styra servomotorn
int servoPosition = 90;  // Initialposition för servomotorn
bool servoState = false; // Variabel för att hålla reda på servomotorns riktning

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(relay_motor, OUTPUT);

  myServo.attach(4);  // Anslut servomotorn till pin 3 på Arduino
  myServo.write(servoPosition);  // Ställ in servomotorns position till den initiala positionen

  currentButtonState = digitalRead(button);
  lastButtonState = currentButtonState;  // Sätt föregående knappstatus till aktuell status vid start
}

void loop() {
  eButton = digitalRead(button);
  lastButtonState = currentButtonState;
  currentButtonState = digitalRead(button);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("Knappen är nedtryckt");

    // Ändra reläets tillstånd
    servo();
    delay(500);

    motor_relay();


    delay(100); // Förbikoppling av studs på knappen
  }
}

void motor_relay() {
  if (digitalRead(relay_motor) == HIGH) {
    digitalWrite(relay_motor, LOW);  // Stäng av reläet om det är på
    Serial.println("Reläet är avstängt");
  }
  else {
    digitalWrite(relay_motor, HIGH);  // Slå på reläet om det är avstängt
    Serial.println("Reläet är på");
  }
}

void servo() {
  if (servoState) {
    servoPosition += 30;
    if (servoPosition > 180) {
      servoPosition = 180;
    }
  } else {
    servoPosition -= 30;
    if (servoPosition < 0) {
      servoPosition = 0;
    }
  }
  myServo.write(servoPosition);
  servoState = !servoState; // Vänd på riktningen för nästa knapptryck
  delay(100); // Förbikoppling av studs på knappen
}
