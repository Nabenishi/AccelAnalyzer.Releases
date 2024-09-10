

# AccelAnalyzer
**AccelAnalyzer** is a toolkit for analyzing accelerometer data and calibrating Bass Shakers.

## What the app does:
- **Raw Data Acquisition**: Reads raw accelerometer data over USB serial and converts it to G-forces.
- **Signal Processing**: Applies filtering, offset correction, and optional calibration on the captured data.
- **Frequency Response Analysis**: Runs FFT (Fast Fourier Transform) for frequency domain analysis.
- **Decibel Conversion**: Converts frequency magnitude to dB scale.
- **Generates Graphs**: 
  - G/Time RAW
  - G/Time Selected Axes with DC Blocker & Filtering
  - Magnitude (G) vs Frequency
  - Magnitude (dB) vs Frequency
  - Power Spectral Density
- **REW Compatibility**: Exports measurement data compatible with REW ([Room EQ Wizard](https://www.roomeqwizard.com/)) for EQ generation and calibration.

## Recommended Hardware:
I highly recommend the **BIGTREETECH S2DW V1.0.1** for use with AccelAnalyzer.
 -   **Pre-assembled**: No soldering required, easy  **USB Plug & Play** solution.
 -   **Sensor**: Features the STMicroelectronics [LIS2DW12](https://www.st.com/en/mems-and-sensors/lis2dw12.html), with  high accuracy and low noise.
 - **Mounting**: Has a nice M6 hole in the middle.
 - **Cheap**: Usually around 5-10 USD/EUR
 
### Official Stores:    [BIQU](https://biqu.equipment/products/adxl-345-accelerometer-board-for-36-stepper-motors?variant=40446852759650), [Amazon](https://www.amazon.com/BIGTREETECH-S2DW-Acceleration-Raspberry-Pi-Accelerometer/dp/B0CHFMBFCJ?ref_=ast_sto_dp), [Aliexpress](https://www.aliexpress.com/item/1005004243190853.html?spm=a2g0o.store_pc_home.promoteWysiwyg_4000000448804.1005004243190853)




## How to Use:
1. **Get the Sensor**: Buy the recommended board or build your own.
2. **Install Firmware**: Copy the `.uf2` firmware to your board (Plug it in while holding the button to enter bootloader mode).
	- Note: If you are not using the recommended sensor, you have to code your own firmware.
3. **Mount Sensor**: Securely hard mount your sensor to a fixed point, such as your chair, seat or rig and make sure it doesn't wobble.
4. **Get the App**: Obtain the latest **AccelAnalyzer.zip** from the [releases](https://github.com/Nabenishi/AccelAnalyzer.Releases/releases).
5. **Setup**: Identify the COM port your sensor is connected to (Device Manager) and update the `settings.json` file accordingly.
6. **Run the Application**: 
   - Execute the `.exe` and open the provided URL to access the SwaggerUI.
   - Note: You may need to install [**.NET**](https://dotnet.microsoft.com/en-us/download) and [**ASP.NET Core 8.0 Runtime**](https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-aspnetcore-8.0.8-windows-hosting-bundle-installer) if not already installed.
7. **Start Test Signal**: Use **REW**'s Generator to play **Pink Noise** through your shaker.
8. **Measure**:
   - Navigate to the UI and select **Measurement/AnalyzeToneNoise**.
   - Click **Try it out**, Enter a name for the measurement, click **Execute**, and wait for results.
   - Note: For the ASCII chart to render correctly, you may need to install [**Windows Terminal**](https://apps.microsoft.com/detail/9n0dx20hk701?hl=en-gb&gl=US) and set **Consolas** as your font to get smooth characters.
9. **Review Results**:
   - Check the `Results` folder for plots and `.txt` files of the frequency response.
10. **REW Import**: Open REW, go to **File -> Import -> Frequency Response**, and load the generated `.txt` file.
11. **Create Your EQ**: Use REW to generate the EQ curve and load it into **[Equalizer APO](https://sourceforge.net/projects/equalizerapo/)** or your DSP.
12. **Verify and Fine-Tune**: Repeat measurements, analyze results, and apply necessary adjustments for optimized performance.

## Configuration
You can configure different scaling factors for converting raw data to G-force values:
| **Board/Range** | ±2 g | ±4 g(Default) | ±8 g | ±16 g |
|-----------------|------|------|------|-------|
| **LIS2DW12**    | 0.000244 | 0.000488 | 0.000976 | 0.001952 |
| **ADXL345**     | 0.00390625 | 0.00390625 | 0.00390625 | 0.00390625 |


## Custom Sensor Support
AccelAnalyzer supports any USB Serial compatible device that sends data in the following format. (See [Firmwares](https://github.com/Nabenishi/AccelAnalyzer.Releases/tree/main/Firmwares) for sample codes)

| **Field**        | **Size** | **Description**                               |
|------------------|----------|-----------------------------------------------|
| **Start Marker** | 1 byte   | Fixed value `0xFF` indicating the start of the message. |
| **X-Axis Data**  | 2 bytes  | 16-bit signed integer for X-axis sensor value. |
| **Y-Axis Data**  | 2 bytes  | 16-bit signed integer for Y-axis sensor value. |
| **Z-Axis Data**  | 2 bytes  | 16-bit signed integer for Z-axis sensor value. |

## Privacy Policy
AccelAnalyzer runs locally on your device and does not connect to the internet. It does not send or receive data from any external servers. All data processing happens in isolation on your device, ensuring complete data privacy and security.

## Libraries Used:
- [**FftSharp**](https://github.com/swharden/FftSharp) - For FFT analysis.
- [**ScottPlot**](https://github.com/ScottPlot/ScottPlot) - For plotting graphs.
- [**Adafruit_ADXL345**](https://github.com/adafruit/Adafruit_ADXL345) - ADXL345 accelerometer library.
- [**asciichart-sharp**](https://github.com/NathanBaulch/asciichart-sharp) - ASCII chart rendering library.
