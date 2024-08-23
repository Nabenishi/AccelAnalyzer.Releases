# AccelAnalyzer.Releases
Release repository for AccelAnalyzer: a toolkit for analyzing accelerometer data and calibrating Bass Shakers.

## What it does:
* Reads Raw Data from sensor through USB serial and converts it to G
* Calculates Magnitude, applies configured offset, filters and downsamples signal.
* Runs FFT signal processing to get frequency response
* Applies Decibel Conversion
* Exports REW compatible measurement data for EQ generation

## How to use
1. You will need an accelerometer/microcontroller. The supported boards below are integrated Plug&Play solutions for cheap, no soldering or coding required.
2. Copy the .uf2 firmware onto the board (Plug in while holding the button)
3. Download the AccelAnalyzer.zip
4. Find out what COM port your sensor is connected to and put it into the settings.json
5. Run the .exe and open the url for accessing the SwaggerUI
   - Note: You may need to install [.NET](https://dotnet.microsoft.com/en-us/download) and [ASP.NET Core 8.0 Runtime](https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-aspnetcore-8.0.8-windows-hosting-bundle-installer) if You do not have it already.
7. Have your sensor hard mounted/fixed on your chair/rig
8. Start your Pink noise on your shaker (REW Generator)
9. Select the Measurement/AnalyzeNoise option in the UI, (Click Try) give your measurement a name, (Click Execute) and wait for results.
   - Note: You may need to install [Windows Terminal](https://apps.microsoft.com/detail/9n0dx20hk701?hl=en-gb&gl=US) for the AsciiChart to work, and also set Consolas as your font to have the curvy curners.
10. Check the Results folder, there will be a plot of frequency response and a .txt frequency response
11. In REW: File -> Import -> Import frequency response -> Open the .txt
12. Then you can create your EQ in REW and load it into APO, or DSP
13. Repeat measurement and check results, apply corrections

## Configuration
RawToGScaleFactor
 Board/Range | ±2 g |±4 g|±8 g|±16 g|
-|-|-|-|-|
ADXL345 | 0.00390625| 0.00390625| 0.00390625| 0.00390625|
LIS2DW12| 0.000244|0.000488|0.000976|  0.001952|
  
## Supported Sensor Boards
Any USB Serial compatible device should work, sketches will be included for the following boards used for testing:

Board | Microprocessor | Sensor |
-----------------|----------------|---|
BIGTREETECH ADXL345 V2.0 [(GIT)](https://github.com/bigtreetech/ADXL345) | RP2040| Analog Devices ADXL345 [(PDF)](https://www.analog.com/media/en/technical-documentation/data-sheets/adxl345.pdf)       
BIGTREETECH S2DW V1.0/1.0.1 [(GIT)](https://github.com/bigtreetech/LIS2DW)| RP2040| STMicroelectronics LIS2DW12 [(PDF)](https://eu.mouser.com/datasheet/2/389/lis2dw12-1849760.pdf) [(Site)](https://www.st.com/en/mems-and-sensors/lis2dw12.html) | 

### Message Structure
| **Field**        | **Size** | **Description**                               |
|------------------|----------|-----------------------------------------------|
| **Start Marker** | 1 byte   | Fixed value `0xFF` indicating the start of the message. |
| **X-Axis Data**  | 2 bytes  | 16-bit signed integer for the X-axis sensor value. |
| **Y-Axis Data**  | 2 bytes  | 16-bit signed integer for the Y-axis sensor value. |
| **Z-Axis Data**  | 2 bytes  | 16-bit signed integer for the Z-axis sensor value. |


## Privacy Policy
The Application is a straightforward console app that runs locally on your device.
The Application does not connect to the internet, does not send or receive data to or from any external servers, and does not interact with any third-party services.
All processing occurs in isolation on your device, ensuring that your data remains private and secure.

## Libraries used:
* https://github.com/swharden/FftSharp
* https://github.com/ScottPlot/ScottPlot
* https://github.com/adafruit/Adafruit_ADXL345
