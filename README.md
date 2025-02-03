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
  - Heatmap (Spectrogram)
- **REW Compatibility**: Exports measurement data compatible with REW ([Room EQ Wizard](https://www.roomeqwizard.com/)) for EQ generation and calibration.
- **Sonic Visualiser Compatibility**: Exports measurement data in .CSV
- **Datalogger**: Records G-s with precise timestamp into CSV
- **Audio Stream**: Provides accelerometer data as audio output for tools like REW 
  
### Output example of a REW Measurement Sweep on a BST-300EX (EQ-ed):
| SampleRate | Axes in G | Offset removed |
|--|--|--|
| ![Sweep_R15_SR](https://github.com/user-attachments/assets/2f6bb474-847e-49e2-beda-626767aad9b0) | ![Sweep_R15_XYZ](https://github.com/user-attachments/assets/d476ba5a-775e-48bd-a142-6ad42f1d2a98) | ![Sweep_R15_SEL](https://github.com/user-attachments/assets/d40a94f0-7e9d-4e8b-af23-8ca029f4d04d) |

|FFT|PSD|dB|Heatmap|
|--|--|--|--|
| ![Sweep_R15_FFT](https://github.com/user-attachments/assets/a655bdf1-df0c-4d96-ac14-f6b6aa32a6f9) | ![Sweep_R15_PSD](https://github.com/user-attachments/assets/5af11227-8583-4154-91f1-360ac38b935a) | ![Sweep_R15_dB](https://github.com/user-attachments/assets/da864b42-c772-46bd-8521-bf52d5fe9f57) | ![Sweep_R15_HM](https://github.com/user-attachments/assets/8bd0c687-c93b-4b20-82d8-d9a091da5af9) |

### Realtime audio output from acceleration data:
|TB Equalizer|Sonic Visualizer|REW RTA|
|--|--|--|
| ![TB Equalizer](https://github.com/user-attachments/assets/6ecc0f7b-7d54-4fec-9e87-1f67699082db) | ![Sonic Visualizer](https://github.com/user-attachments/assets/d1061ba3-1f85-4aca-98dd-055bb0f73e0e) | ![REW RTA](https://github.com/user-attachments/assets/7c2fe67a-fafc-4959-9bf9-51948eb09ca6) |



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
   - If you are having connection issues:
     - If you are using SimHub, disable [**serial port scan**](https://github.com/SHWotever/SimHub/wiki/Troubleshoot-other-hardware-Serial-ports-conflicts). (Or any other app that is polling serial USB devices)
     - Check if the port settings are correct (Bits per second: 115200, Data bits: 8, Parity: None, Stop bits: 1)
     - Connect directly to motherboard
     - Use a shorter cable 
7. **Run the Application**: 
   - Execute the `.exe` and open the provided URL to access the SwaggerUI.
   - Note: You may need to install [**.NET**](https://dotnet.microsoft.com/en-us/download) and [**ASP.NET Core 8.0 Runtime**](https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-aspnetcore-8.0.8-windows-hosting-bundle-installer) if not already installed.
8. **Start Test Signal**: Use **REW**'s Generator to play **Pink Noise** through your shaker.
9. **Measure**:
   - Navigate to the UI and select **Measurement/AnalyzeToneNoise**.
   - Click **Try it out**, Enter a name for the measurement, click **Execute**, and wait for results.
   - Note: For the ASCII chart to render correctly, you may need to install [**Windows Terminal**](https://apps.microsoft.com/detail/9n0dx20hk701?hl=en-gb&gl=US) and set **Consolas** as your font to get smooth characters.
10. **Review Results**:
   - Check the `Results` folder for plots and `.txt` files of the frequency response.
11. **REW Import**: Open REW, go to **File -> Import -> Frequency Response**, and load the generated `.txt` file.
12. **Create Your EQ**: Use REW to generate the EQ curve and load it into **[Equalizer APO](https://sourceforge.net/projects/equalizerapo/)** or your DSP.
13. **Verify and Fine-Tune**: Repeat measurements, analyze results, and apply necessary adjustments for optimized performance.

## Configuration
Check the [Configuration Guide](CONFIG_GUIDE.md)

## Privacy Policy
AccelAnalyzer runs locally on your device and does not connect to the internet. It does not send or receive data from any external servers. All data processing happens in isolation on your device, ensuring complete data privacy and security.

## Libraries Used:
- [**FftSharp**](https://github.com/swharden/FftSharp) - For FFT analysis.
- [**ScottPlot**](https://github.com/ScottPlot/ScottPlot) - For plotting graphs.
- [**Adafruit_ADXL345**](https://github.com/adafruit/Adafruit_ADXL345) - ADXL345 accelerometer library.
- [**asciichart-sharp**](https://github.com/NathanBaulch/asciichart-sharp) - ASCII chart rendering library.
- [**NAudio**](https://github.com/naudio/NAudio) - Audio and MIDI library for .NET
