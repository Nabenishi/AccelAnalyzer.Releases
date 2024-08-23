#include <SPI.h>

// Define software SPI pins based on the configuration
const uint8_t sclock = 10;  // GPIO10
const uint8_t miso = 8;     // GPIO8
const uint8_t mosi = 11;    // GPIO11
const uint8_t cs = 9;       // GPIO9

void setup(void) {
  Serial.begin(115200);
  delay(1000);
  while (!Serial)
    ;

  Serial.println("Serial enabled!");

  // Setup SPI pins for software SPI
  pinMode(cs, OUTPUT);
  pinMode(sclock, OUTPUT);
  pinMode(mosi, OUTPUT);
  pinMode(miso, INPUT);

  digitalWrite(cs, HIGH);  // Ensure CS is initially high
  delay(100);              // Give time for the sensor to stabilize

  // Check WHO_AM_I register to ensure we are communicating with the correct sensor
  uint8_t who_am_i = softwareReadRegister(0x0F);
  if (who_am_i != 0x44) {
    Serial.print("Error: WHO_AM_I register mismatch! Expected 0x44, got 0x");
    Serial.println(who_am_i, HEX);
    while (1)
      ;  // Stop the program if the sensor is incorrect
  }
  Serial.println("WHO_AM_I register verified!");

  // Initialize the sensor
  Serial.println("Resetting the sensor..");
  softwareWriteRegister(0x21, 0x40);  // Soft reset the sensor
  delay(100);

  softwareWriteRegister(0x20, 0x74);  // ODR 400 Hz, High-Performance mode
  //softwareWriteRegister(0x20, 0x84);  // ODR 800 Hz, High-Performance mode
  //softwareWriteRegister(0x20, 0x94);  // ODR 1600 Hz, High-Performance mode

  softwareWriteRegister(0x25, 0x14);  // 4g low noise

  Serial.println("Sensor setup complete.");
  delay(100);
}


// Pre-allocated buffer
uint8_t buffer[7];
const uint8_t startMarker = 0xFF;

void loop(void) {
  if (softwareReadRegister(0x27) & 0x01) {

    // Check if the DRDY (Data Ready) bit is set, which is bit 7
    // Read sensor values
    int16_t x = (read16BitRegister(0x28) >> 2);
    int16_t y = (read16BitRegister(0x2A) >> 2);
    int16_t z = (read16BitRegister(0x2C) >> 2);

    // Pack marker and data into buffer
    buffer[0] = startMarker;
    memcpy(buffer + 1, &x, sizeof(int16_t));
    memcpy(buffer + 3, &y, sizeof(int16_t));
    memcpy(buffer + 5, &z, sizeof(int16_t));

    // Send in one call
    Serial.write(buffer, sizeof(buffer));
  }
}

uint8_t softwareReadRegister(uint8_t reg) {
  digitalWrite(cs, LOW);
  softwareSPITransfer(reg | 0x80);
  uint8_t value = softwareSPITransfer(0x00);
  digitalWrite(cs, HIGH);
  return value;
}

void softwareWriteRegister(uint8_t reg, uint8_t value) {
  digitalWrite(cs, LOW);
  delayMicroseconds(10);
  softwareSPITransfer(reg & 0x7F);
  softwareSPITransfer(value);
  digitalWrite(cs, HIGH);
  delayMicroseconds(10);
}

uint8_t softwareSPITransfer(uint8_t data) {
  uint8_t received = 0;
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(mosi, (data & 0x80) ? HIGH : LOW);
    data <<= 1;
    digitalWrite(sclock, HIGH);
    received <<= 1;
    if (digitalRead(miso)) {
      received |= 0x01;
    }
    digitalWrite(sclock, LOW);
  }
  return received;
}

int16_t read16BitRegister(uint8_t reg) {
  int16_t value = softwareReadRegister(reg);
  value |= (softwareReadRegister(reg + 1) << 8);
  return value;
}
