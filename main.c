// Pin Definitions
#define SENSOR_1_PIN A0
#define SENSOR_2_PIN A1
#define OUTPUT_1_PIN 2
#define OUTPUT_2_PIN 3
#define OUTPUT_3_PIN 4
#define OUTPUT_4_PIN 5
#define OUTPUT_5_PIN 6
#define OUTPUT_6_PIN 7
#define OUTPUT_7_PIN 8
#define OUTPUT_8_PIN 9
#define POWER_ON_PIN 10
#define LED_PIN 13 //for testing 


// Sensor Thresholds
#define THRESHOLD_1_LOW 0
#define THRESHOLD_1_HIGH 102
#define THRESHOLD_2_LOW 103
#define THRESHOLD_2_HIGH 358
#define THRESHOLD_3_LOW 359
#define THRESHOLD_3_HIGH 767
#define THRESHOLD_4_LOW 768
#define THRESHOLD_4_HIGH 1023

// Time Constants (in milliseconds)
#define SENSOR_READ_INTERVAL 100
#define LED_ON_TIME 8000

// Global Variables
int sensor1Value = 0;
int sensor2Value = 0;
bool procedureStarted = false;

void setup() {
  // Initialize pin modes
  pinMode(SENSOR_1_PIN, INPUT);
  pinMode(SENSOR_2_PIN, INPUT);
  pinMode(OUTPUT_1_PIN, OUTPUT);
  pinMode(OUTPUT_2_PIN, OUTPUT);
  pinMode(OUTPUT_3_PIN, OUTPUT);
  pinMode(OUTPUT_4_PIN, OUTPUT);
  pinMode(OUTPUT_5_PIN, OUTPUT);
  pinMode(OUTPUT_6_PIN, OUTPUT);
  pinMode(OUTPUT_7_PIN, OUTPUT);
  pinMode(OUTPUT_8_PIN, OUTPUT);
  pinMode(POWER_ON_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);


  // Turn off all outputs initially
  turnOffAllOutputs();
  digitalWrite(POWER_ON_PIN, 0);    
}

void loop() {
  // Read sensor values
  int leftSensorValue = analogRead(SENSOR_1_PIN);
  int rightSensorValue = analogRead(SENSOR_2_PIN);

  //check if shoes detected on right or left led stays on
  if(rightSensorValue>0||leftSensorValue>0){
      digitalWrite(LED_PIN, HIGH);
  }




  // Check if both shoes are detected
  if (leftSensorValue > 0 && rightSensorValue > 0) {
    // Wait for 2 seconds to confirm shoe placement
    bool ledstate= true;
    for(int i=0;i<20;i++){
      digitalWrite(LED_PIN, ledstate);
      ledstate=!ledstate;
      delay(100);
  }
    // Check if both shoes are still detected after delay
    if (analogRead(SENSOR_1_PIN) > 0 && analogRead(SENSOR_2_PIN) > 0) {
     // Map the signal strength to the corresponding output
  if (leftSensorValue >= THRESHOLD_1_LOW && leftSensorValue <= THRESHOLD_1_HIGH) {
    triggerOutput(OUTPUT_1_PIN);
  } else if (leftSensorValue >= THRESHOLD_2_LOW && leftSensorValue <= THRESHOLD_2_HIGH) {
    triggerOutput(OUTPUT_2_PIN);
  } else if (leftSensorValue >= THRESHOLD_3_LOW && leftSensorValue <= THRESHOLD_3_HIGH) {
    triggerOutput(OUTPUT_3_PIN);
  } else if (leftSensorValue >= THRESHOLD_4_LOW && leftSensorValue <= THRESHOLD_4_HIGH) {
    triggerOutput(OUTPUT_4_PIN);
  }
if (rightSensorValue >= THRESHOLD_1_LOW && rightSensorValue <= THRESHOLD_1_HIGH) {
    triggerOutput(OUTPUT_5_PIN);
  } else if (rightSensorValue >= THRESHOLD_2_LOW && rightSensorValue <= THRESHOLD_2_HIGH) {
    triggerOutput(OUTPUT_6_PIN);
  } else if (rightSensorValue >= THRESHOLD_3_LOW && rightSensorValue <= THRESHOLD_3_HIGH) {
    triggerOutput(OUTPUT_7_PIN);
  } else if (rightSensorValue >= THRESHOLD_4_LOW && rightSensorValue <= THRESHOLD_4_HIGH) {
    triggerOutput(OUTPUT_8_PIN);
  }
      //open led for 8 seconds
      digitalWrite(LED_PIN, HIGH);

      // Wait for LED_ON_TIME
      delay(LED_ON_TIME);
      digitalWrite(LED_PIN, LOW);

     //turn off leds
     turnOffAllOutputs();
    }
  } else {
    // Reset the shoe detection
    delay(100);
  }
}

void turnOffAllOutputs() {
  digitalWrite(OUTPUT_1_PIN, 0);
  digitalWrite(OUTPUT_2_PIN, 0);
  digitalWrite(OUTPUT_3_PIN, 0);
  digitalWrite(OUTPUT_4_PIN, 0);
  digitalWrite(OUTPUT_5_PIN, 0);
  digitalWrite(OUTPUT_6_PIN, 0);
  digitalWrite(OUTPUT_7_PIN, 0);
  digitalWrite(OUTPUT_8_PIN, 0);
}
void triggerOutput(int outputPin) {
  // Trigger the specified output pin
  digitalWrite(outputPin, HIGH);
  }