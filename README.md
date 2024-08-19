# AccelAnalyzer.Releases
Release repository for AccelAnalyzer: a toolkit for analyzing accelerometer data and calibrating Bass Shakers.

## What it does:
* Reads Raw Data from sensor through USB serial and converts it to G
* Calculates Magnitude, applies configured offset, filters and downsamples signal.
* Runs FFT signal processing to get frequency response
* Applies Decibel Conversion
* Exports REW compatible measurement data for EQ generation
  
## Supported Sensor Boards
Any USB Serial compatible device should work, sketches will be included for the following boards used for testing:

Board           | Sensor       | 
-----------------|----------------|
BIGTREETECH ADXL345 V2.0 [(GIT)](https://github.com/bigtreetech/ADXL345) | Analog Devices ADXL345 [(PDF)](https://www.analog.com/media/en/technical-documentation/data-sheets/adxl345.pdf)       
BIGTREETECH S2DW V1.0 [(GIT)](https://github.com/bigtreetech/LIS2DW)| STMicroelectronics LIS2DW12 [(PDF)](https://eu.mouser.com/datasheet/2/389/lis2dw12-1849760.pdf) [(Site)](https://www.st.com/en/mems-and-sensors/lis2dw12.html)        |
