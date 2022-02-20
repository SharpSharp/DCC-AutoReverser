/* A sketch to automatically control the power feed to a reversing loop on a DCC model railway.
 * Two acs712 current sensors are used to detect a short ciruit in either rail.
 * acs712 current sensors are connected to anolog pins.
 *  
 * Two relays are used to switch the power feed on detection of a short.
 * Relays are connected to digital pins
 * 
 * The number of analogue pins limit the number of reversing sections that can be controlled
 * An Uno's 6 analog pins can control 3 reversing sections
 * A Nano's 8 analog pins can control 4 reversing sections
 * 
 * DCC is an AC signal, current can be +ve or -ve. 
 * For fast detection both are tested.
 * Triggers are set for above (+ve) and below (-ve) the midpoint.
 */
 
const float vcc = 5.0;              // voltage on your Arduino
const int adc = 1024;               // Arduino Analog to Digital Conversion resolution (10 bit)
const float sensitivity = 0.185;    // sensetivity of ACS712 in V (185mV/A)
const float triggerCurrent = 1.0;   // trigger current to activate the reverser
#define sensorMidPoint 511          // sensor value when reading 0 amps

float triggerVoltage = triggerCurrent * sensitivity;        // voltage required to trigger
float triggerValue = triggerVoltage / vcc * adc;            // value change required for trigger

float highTriggerValue = sensorMidPoint + triggerValue;     // set trigger for +ve current
float lowTriggerValue =  sensorMidPoint - triggerValue;     // set trigger for -ve current

struct AutoReverse
{
  byte sensor1;       // analog input pin from acs712 first rail
  byte sensor2;       // analog input pin from acs712 second rail
  byte railA;         // pin connected to output relay for first rail
  byte railB;         // pin connected to output relay for second rail
  bool triggerReverse;
  
  void setup()
  {
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(railA,   OUTPUT);
    pinMode(railB,   OUTPUT);
    digitalWrite(railA, LOW);      //setup relay output to their Normally Closed position
    digitalWrite(railB, LOW);      //setup relay output to their Normally Closed position   
  }
  void reverseOutput()
  {
    digitalWrite(railA, !digitalRead(railA));       // toggle railA output 
    digitalWrite(railB, !digitalRead(railB));       // toggle railB output
    delay(5); // wait to avoid false triggers 
  }
  
  void  readSensor(byte sensor)
  {
  // read analog signal from current sensor and test against trigger values
  if (analogRead(sensor) > highTriggerValue) triggerReverse = true;
  if (analogRead(sensor) < lowTriggerValue)  triggerReverse = true;
  }
  
  void testForShort()
  {
    triggerReverse = false;               // set trigger to false prior to reading sensors
    readSensor(sensor1);
    readSensor(sensor2);
    if (triggerReverse) reverseOutput();
  }
};

AutoReverse reversingTrack = {A0, A1, 4, 5};
//AutoReverse wye = {A2, A3, 6, 7};               // uncoment for second reverser
//AutoReverse reversingLoop = {A4, A5, 8, 9};     // uncoment for third reverser



void setup() {
//  Serial.begin(9600); 
  delay(500);               // wait half a second to allow the sensers to stablize
  reversingTrack.setup();
//  wye.setup();            // uncoment for second reverser
//  reversingLoop.setup();  // uncoment for third reverser
}

void loop() {
  reversingTrack.testForShort();
//  wye.testForShort();
//  reversingLoop.testForShort();             // uncoment for second reverser
//  delay(500); // slow output for testing    // uncoment for third reverser
 }
