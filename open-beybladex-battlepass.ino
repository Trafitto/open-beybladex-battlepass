const int irSensorPin = 2;
const int buttonPin = 3;

volatile int blankCount = 0;
unsigned long pressStartTime = 0;
bool isButtonPressed = false;
bool hasPrinted = false;

void setup() {
  pinMode(irSensorPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(irSensorPin), countTransition, FALLING);

}

void loop() {
  if (digitalRead(buttonPin) == HIGH){
    if (!isButtonPressed){
      isButtonPressed = true;
      blankCount = 0;
      pressStartTime = millis();
      hasPrinted = false;
    }
  }else{
    if (isButtonPressed && !hasPrinted){
      isButtonPressed = false;
      hasPrinted = true;
      unsigned long elapsedTime = millis() - pressStartTime;
      float elapsedTimeSeconds = elapsedTime / 1000.0;
      int rpm = (int)(((blankCount / 2) / elapsedTimeSeconds) * 60);
      Serial.print("RPM: ");
      Serial.println(rpm);
    }
  }

}

void countTransition(){
  if (isButtonPressed) {
    blankCount++;
  }
}
