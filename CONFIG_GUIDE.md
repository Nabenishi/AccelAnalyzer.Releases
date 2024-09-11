# AccelAnalyzer Configuration Guide

This document provides an overview of the configuration options available in AccelAnalyzer. The configuration is stored in a `JSON` format and can be adjusted based on your needs for sensor data acquisition, processing, and visualization.

## **Analyzer**

This section defines the core settings for how the analyzer interacts with the sensor and processes the data.

####  **PortName**

Specifies the **COM Port** your sensor is connected to.
 
   -   Change it to `"COM3"`, `"COM4"`, etc.

#### **BaudRate**

Defines the communication speed with the sensor. The standard rate for many devices is **115200 baud**.

-   **Default**: `115200`
    
    **Example**: Change to other values like `9600` or `57600` depending on your device's communication rate.
    

####  **RawToGScaleFactor**

This factor converts the raw sensor values into G-forces based on the sensor's range. Adjust this value according to the sensor's datasheet.

-   **Default**: `0.000488` (for ±4g range on LIS2DW12)
    
    **Example**: Use different values like `0.000244` for ±2g or `0.000976` for ±8g.
    
| **Board/Range** | ±2 g | ±4 g(Default) | ±8 g | ±16 g |
|-----------------|------|------|------|-------|
| **LIS2DW12**    | 0.000244 | 0.000488 | 0.000976 | 0.001952 |
| **ADXL345**     | 0.00390625 | 0.00390625 | 0.00390625 | 0.00390625 |

####  **UseTestSignal**

Enables or disables the use of a **test signal** instead of live sensor data.

-   **Default**: `false` (live data)
    
    **Possible values**: `true` (use test signal), `false` (use sensor data).
    

####  **SampleSize**

Defines the number of data points collected in each sample. A larger size increases the frequency resolution in FFT but takes longer to process.

-   **Default**: `2048`
    
    **Adjustable**: Values like `1024`, `2048`, `4096` for better frequency resolution.
    

####  **SampleCount**

Number of samples to collect before processing.

-   **Default**: `9`
    
    **Adjustable**: Increase for averaging multiple samples.
    

----------

###  **ChartConfig**

Settings related to the time-based chart display.

####  **DisplayTimeSeconds**

The time window, in seconds, displayed in the real-time chart.

-   **Default**: `1` second
    
    **Example**: Increase for a wider time view, such as `2` or `3` seconds.
    

####  **RefreshRateSeconds**

Time interval for refreshing the chart display.

-   **Default**: `0.3` seconds
    
    **Example**: Adjust based on how frequently you want updates (e.g., `0.5` or `1`).
    

----------

###  **PlotConfig**

Defines the configuration for the plot output, such as the graph dimensions.

####  **PlotScaleFactor**

Adjusts the scale of the plots.

-   **Default**: `1.8`

####  **PlotWidth** and **PlotHeight**

Dimensions of the generated plot in pixels.

-   **Default Width**: `1920`
-   **Default Height**: `1080`

----------

###  **SensorOrientation**

This section allows you to configure the orientation of the sensor and apply roll/pitch offsets.

####  **XAxis, YAxis, ZAxis**

Assigns the correct axis labels according to your sensor’s orientation.

-   **Default**: `"X"`, `"Y"`, `"Z"`

####  **InvertRoll** and **InvertPitch**

Allows you to invert the roll and pitch axis if your sensor is mounted in reverse.

-   **Default**: `false`
    
    **Possible values**: `true` (invert axis), `false` (normal orientation).
    

####  **RollOffset** and **PitchOffset**

Offsets applied to correct for any tilt or misalignment in the sensor.

-   **Default**: `0` degrees
    
    **Example**: Apply small offsets to correct minor misalignments, e.g., `5` or `-5`.
    

----------

###  **AxisSelection**

Selects which axes (X, Y, Z) are included in the analysis.

-   **IncludeX**: `true`
-   **IncludeY**: `true`
-   **IncludeZ**: `true`

Set to `false` if you want to exclude a specific axis.

----------

###  **Calibration**

The calibration section allows you to manually offset and scale the sensor data.

####  **Enabled**

Determines if calibration is applied to the sensor data.

-   **Default**: `false`
    
    **Possible values**: `true` (apply calibration), `false` (no calibration).
    

####  **Offset**

Defines the manual offset applied to each axis.

-   **Default X**: `0.00`
-   **Default Y**: `0.00`
-   **Default Z**: `0.00`

Adjust to correct for any sensor drift or bias.

####  **ScaleFactor**

Applies a scale factor to each axis, allowing calibration for sensitivity.

-   **Default X**: `1.00`
-   **Default Y**: `1.00`
-   **Default Z**: `1.00`

Increase or decrease these values to calibrate the sensor sensitivity.

----------
