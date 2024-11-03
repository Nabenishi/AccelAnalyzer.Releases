#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

//Sensor
const uint8_t sclock = 10;
const uint8_t miso = 8;
const uint8_t mosi = 11;
const uint8_t cs = 9;
const int32_t sensorID = 123;

absolute_time_t referenceTime;  // Using absolute_time_t for timestamp tracking

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

  accel.setDataRate(ADXL345_DATARATE_400_HZ);

  //accel.writeRegister(ADXL345_REG_DATA_FORMAT, 0x08);  // Enable full resolution @ 2G
  accel.writeRegister(ADXL345_REG_DATA_FORMAT, 0x09);  // Enable full resolution @ 4G
  //accel.writeRegister(ADXL345_REG_DATA_FORMAT, 0x10);  // Enable full resolution @ 8G

  referenceTime = to_us_since_boot(get_absolute_time());
}

// Pre-allocated buffer
uint8_t dataBuffer[11];
uint8_t syncBuffer[9];
const uint8_t dataMarker = 0xFF;
const uint8_t syncMarker = 0xFE;
uint32_t syncInterval = 0;  // 16-bit unsigned interval
absolute_time_t dataReadyTime;

void loop(void) {
  if (Serial.available() > 0) {
    uint8_t command = Serial.read();
    if (command == 0x01) {
      // Respond with the absolute time framed with syncMarker
      referenceTime = to_us_since_boot(get_absolute_time());

      // Prepare sync message
      syncBuffer[0] = syncMarker;
      memcpy(syncBuffer + 1, &referenceTime, 8);

      // Send sync message
      Serial.write(syncBuffer, 9);  // Total 9 bytes: 1-byte marker + 8-byte timestamp
    }
  }

  // Check for data ready
  if (accel.readRegister(0x30) & 0b10000000) {

    dataReadyTime = get_absolute_time();
    syncInterval = (uint32_t)(absolute_time_diff_us(referenceTime, dataReadyTime));

    // Read sensor values
    int16_t x = accel.getX();
    int16_t y = accel.getY();
    int16_t z = accel.getZ();

    // Pack marker and data into buffer
    dataBuffer[0] = dataMarker;
    memcpy(dataBuffer + 1, &x, 2);
    memcpy(dataBuffer + 3, &y, 2);
    memcpy(dataBuffer + 5, &z, 2);
    memcpy(dataBuffer + 7, &syncInterval, 4);

    // Send in one call
    Serial.write(dataBuffer, 11);
  }
}
