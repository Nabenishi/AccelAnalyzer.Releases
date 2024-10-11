#include "lis2dw12_reg.h"

// Define SPI pins
const uint8_t CS_PIN = 9;     // Chip Select pin
const uint8_t MOSI_PIN = 11;  // Master Out, Slave In pin
const uint8_t MISO_PIN = 8;   // Master In, Slave Out pin
const uint8_t SCLK_PIN = 10;  // Serial Clock pin
const uint8_t INT1_PIN = 6;   // Interrupt pin

stmdev_ctx_t dev_ctx;          // Device context for the driver
absolute_time_t previousTime;  // Using absolute_time_t for timestamp tracking

void spiInit() {
  // Setup SPI pins
  pinMode(CS_PIN, OUTPUT);
  pinMode(SCLK_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(INT1_PIN, INPUT);

  // Set initial pin states
  digitalWrite(CS_PIN, HIGH);
  digitalWrite(SCLK_PIN, LOW);
  digitalWrite(MOSI_PIN, HIGH);
  delay(100);
}

void devInit() {
  // Initialize the driver interface
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;

  // Check WHO_AM_I register to ensure we are communicating with the correct sensor
  uint8_t whoamI;
  lis2dw12_device_id_get(&dev_ctx, &whoamI);
  if (whoamI != LIS2DW12_ID) {
    Serial.print("Error: WHO_AM_I register mismatch! Expected 0x44, got 0x");
    Serial.println(whoamI, HEX);
    while (1)
      ;  // Stop the program if the sensor is incorrect
  }
  Serial.println("WHO_AM_I register verified!");

  // Reset the sensor
  Serial.println("Resetting the sensor...");
  lis2dw12_reset_set(&dev_ctx, PROPERTY_ENABLE);

  // Wait until reset is complete
  uint8_t reset_done;
  do {
    lis2dw12_reset_get(&dev_ctx, &reset_done);
  } while (reset_done);
}

void setup(void) {
  Serial.begin(115200);
  delay(1000);
  while (!Serial)
    ;
  Serial.println("Serial enabled!");

  spiInit();
  devInit();

  // Configure the sensor
  lis2dw12_power_mode_set(&dev_ctx, LIS2DW12_HIGH_PERFORMANCE_LOW_NOISE);
  lis2dw12_data_rate_set(&dev_ctx, LIS2DW12_XL_ODR_400Hz);
  lis2dw12_full_scale_set(&dev_ctx, LIS2DW12_4g);
  lis2dw12_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

  // Configure interrupts
  lis2dw12_data_ready_mode_set(&dev_ctx, LIS2DW12_DRDY_PULSED);

  // Route data-ready interrupt to INT1 pin
  lis2dw12_ctrl4_int1_pad_ctrl_t int1_route;
  lis2dw12_pin_int1_route_get(&dev_ctx, &int1_route);
  int1_route.int1_drdy = PROPERTY_ENABLE;
  lis2dw12_pin_int1_route_set(&dev_ctx, &int1_route);

  Serial.println("Sensor setup complete.");
  delay(100);

  attachInterrupt(digitalPinToInterrupt(INT1_PIN), dataReadyISR, RISING);
  previousTime = get_absolute_time();
}

// Pre-allocated buffer
uint8_t buffer[9];
const uint8_t startMarker = 0xFF;
volatile bool dataReady = false;
int16_t data_raw_acceleration[3];
uint16_t interval = 0;
absolute_time_t currentTime;
bool DebugMode = false;

void loop(void) {
  if (dataReady) {
    dataReady = false;

    // Calculate the interval in microseconds between the current and previous time
    interval = (uint16_t)(absolute_time_diff_us(previousTime, currentTime));
    previousTime = currentTime;  // Update the previous time

    // Read sensor values using the driver
    lis2dw12_acceleration_raw_get(&dev_ctx, data_raw_acceleration);

    // Adjust data if necessary (shift right by 2 bits to align 14-bit data)
    int16_t x = data_raw_acceleration[0] >> 2;
    int16_t y = data_raw_acceleration[1] >> 2;
    int16_t z = data_raw_acceleration[2] >> 2;

    if (DebugMode) {
      // Output sensor data
      Serial.print("X:");
      Serial.print(x);
      Serial.print(" Y:");
      Serial.print(y);
      Serial.print(" Z:");
      Serial.print(z);
      Serial.print(" INT:");
      Serial.println(interval);
    } else {
      // Pack marker and data into buffer
      buffer[0] = startMarker;
      memcpy(buffer + 1, &x, sizeof(int16_t));
      memcpy(buffer + 3, &y, sizeof(int16_t));
      memcpy(buffer + 5, &z, sizeof(int16_t));
      memcpy(buffer + 7, &interval, sizeof(uint16_t));
      // Send data in one call
      Serial.write(buffer, sizeof(buffer));
    }
  }
}

// Interrupt Service Routine (ISR) for Data Ready interrupt
void dataReadyISR() {
  currentTime = get_absolute_time();
  dataReady = true;
}

// Software SPI transfer function
uint8_t softwareSPITransfer(uint8_t data) {
  uint8_t received = 0;
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(MOSI_PIN, (data & 0x80) ? HIGH : LOW);
    data <<= 1;
    digitalWrite(SCLK_PIN, HIGH);
    received <<= 1;
    if (digitalRead(MISO_PIN)) {
      received |= 0x01;
    }
    digitalWrite(SCLK_PIN, LOW);
  }
  return received;
}

// Platform-specific write function for the driver
int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len) {
  // Use software SPI to write to the sensor
  digitalWrite(CS_PIN, LOW);

  // Send register address with write operation (MSB = 0)
  softwareSPITransfer(reg & 0x7F);

  // Send data bytes
  for (uint16_t i = 0; i < len; i++) {
    softwareSPITransfer(bufp[i]);
  }

  digitalWrite(CS_PIN, HIGH);
  return 0;  // Return 0 for success
}



// Platform-specific read function for the driver
int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len) {
  // Use software SPI to read from the sensor
  digitalWrite(CS_PIN, LOW);

  // Send register address with read operation (MSB = 1)
  softwareSPITransfer(reg | 0x80);

  // Read data bytes
  for (uint16_t i = 0; i < len; i++) {
    bufp[i] = softwareSPITransfer(0x00);
  }

  digitalWrite(CS_PIN, HIGH);
  return 0;  // Return 0 for success
}

void platform_delay(uint32_t ms) {
  delay(ms);
}
