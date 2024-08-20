#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

//Sensor
const uint8_t sclock = 10;
const uint8_t miso = 8;
const uint8_t mosi = 11;
const uint8_t cs = 9;
const int32_t sensorID = 123;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(sclock, miso, mosi, cs, sensorID);

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("Accelerometer Data Output");

  if (!accel.begin()) {
    Serial.println("Cannot connect to ADXL345!");
    while (1)
      ;
  }

  Wire.setClock(400000);

  accel.setDataRate(ADXL345_DATARATE_800_HZ);
  accel.writeRegister(ADXL345_REG_DATA_FORMAT, 0x09);  // Enable full resolution @ 4G
}

// Pre-allocated buffer
uint8_t buffer[7];
const uint8_t startMarker = 0xFF;

void loop(void) {
  // Check for data ready
  if (accel.readRegister(0x30) & 0b10000000) {
    // Read sensor values
    int16_t x = accel.getX();
    int16_t y = accel.getY();
    int16_t z = accel.getZ();

    // Pack marker and data into buffer
    buffer[0] = startMarker;
    memcpy(buffer + 1, &x, sizeof(int16_t));
    memcpy(buffer + 3, &y, sizeof(int16_t));
    memcpy(buffer + 5, &z, sizeof(int16_t));

    // Send in one call
    Serial.write(buffer, sizeof(buffer));
  }
}
