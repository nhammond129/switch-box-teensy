/* Width of pulse to trigger the shift register to read and latch. */
#define PULSE_WIDTH_USEC  5

const int dataPin = 5;
const int clkPin = 6;
const int latchPin = 7;
const int ledPin = 13;

uint32_t last_data = 0;
uint32_t data = 0;

#define bitmask = 0b00000000111111111111111111111111;
#define flips   = 0b00000000000000000000001111111111;

// shift in from 4x daisy-chained HC165s
uint32_t inShift32(uint8_t dataPin, uint8_t clockPin) {
  uint32_t out = 0;
  for (uint16_t i = 0; i<32; i++) {
    out |= (digitalRead(dataPin) << i);

    digitalWrite(clockPin, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(clockPin, LOW);
  }
  return out;
}

void setup() {  
  pinMode(dataPin,  INPUT);
  pinMode(clkPin,   OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(ledPin,   OUTPUT);
}

void loop() {
  {  // Get data from 74HC165s (x4)
    digitalWrite(latchPin, HIGH);
    delayMicroseconds(5);
    data = inShift32(dataPin, clkPin);
    // Write pulse to load pin
    digitalWrite(latchPin, LOW);
  }

  // mask out unused & invert some buttons
  data = data & bitmask;
  data = data ^ flips;
  // set buttons
  for (int i=0; i<32; i++) {
    Joystick.button(i+1, (data >> i) & 1);
  }
}
