/* Width of pulse to trigger the shift register to read and latch.
*/
#define PULSE_WIDTH_USEC  5

const int dataPin = 5;
const int clkPin = 6;
const int latchPin = 7;

const int ledPin = 13;

const uint32_t bitmask = 0b00000000111111111111111111111111;
const uint32_t flips   = 0b00000000000000000000001111111111;

uint32_t inShift(uint8_t dataPin, uint8_t clockPin) {
  uint32_t out = 0;
  for (uint16_t i = 0; i<32; i++) {
    out |= (digitalRead(dataPin) << i);

    digitalWrite(clockPin, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(clockPin, LOW);
  }
  return out;
}

void oldFunc(int var) {
  for (int i = 0; i < 32; i++)  {
    Serial.print(((var >> i) & 1) == 1 ? "1" : "0");
  }
  Serial.println();
}

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  
  pinMode(dataPin,  INPUT);
  pinMode(clkPin,   OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(ledPin,   OUTPUT);
}

// the loop routine runs over and over again forever:
uint32_t data;
void loop() {


  // Get data from 74HC165
  digitalWrite(latchPin, HIGH);
  delayMicroseconds(5);
  data = inShift(dataPin, clkPin);
  // Write pulse to load pin
  digitalWrite(latchPin, LOW);

  // mask
  data = data & bitmask;
  // flip
  data = data ^ flips;

  for (int i=0; i<32; i++) {
    Joystick.button(i+1, (data >> i) & 1);
  }

  // Print to serial monitor
  Serial.print("Pin States:\t");
  oldFunc(data);
  delay(100);
}
