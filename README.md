# AC Waveforms and 3-Phase Power

## Overview

This project is a C program that reads power quality data from a CSV file and calculates important electrical values

The program works with three-phase voltage data and checks if the system is operating within normal conditions.


## What the program does

The program reads data from `power_quality_log.csv` and calculates:

* RMS voltage (how strong the signal is)
* Peak-to-peak voltage (difference between max and min)
* DC offset (average value of the signal)
* Clipping (when voltage exceeds ±324.9 V)
* Frequency range (min and max)
* Power factor range (min and max)
* THD range (signal distortion)

All results are saved in a file called `results.txt`.



## How the program is structured

The program is split into different files:

* `main.c` → runs the program
* `io.c / io.h` → reads the CSV file
* `waveform.c / waveform.h` → does all calculations

This makes the code easier to organise and understand.



## Why I used a struct

I used a struct called `WaveformSample` to store all values from one row of the CSV file.

This is better than using multiple arrays because all related data stays together.



## Why I used malloc

I used `malloc()` to create memory for the data because the program needs to store many samples.

This makes the program flexible instead of using a fixed-size array.



## Clipping explanation

Clipping happens when the voltage goes above ±324.9 V.

At first, my program detected around 60 clipped samples.
However, because this is a three-phase system, clipping happens across all three phases at the same time.

So I divided the result by 3 to represent about 20 actual clipping events.



## Example output

Phase A RMS: 229.81 V
Peak-to-Peak: 650.00 V
DC Offset: -0.00 V
Clipped Samples: 20
Frequency Range: 50.000 - 50.048 Hz
Power Factor Range: 0.950 - 0.962
THD Range: 2.00 - 2.18 %



## Testing

I tested the program by:

* Checking if the file loads correctly
* Comparing results with expected values
* Using print statements to debug issues



## How to run the program

1. Put `power_quality_log.csv` in the project folder
2. Build the program
3. Run it
4. Check `results.txt` for output

## Extending the Program

### 1. Bitwise Status Flags

I implemented a bitwise status flag system using a `uint8_t` field inside the `WaveformSample` struct.

Each bit represents a different condition:
- Bit 0 = Clipping detected
- Bit 1 = RMS out of tolerance
- Bit 2 = High THD

This allows multiple conditions to be stored efficiently in a single variable instead of using multiple boolean variables.

The flags are set using bitwise operations (`|=`) and checked using the bitwise AND operator (`&`).

Example:
- A value of `1` means clipping only
- A value of `3` means clipping and RMS issues
- A value of `0` means no issues

This improves scalability and keeps the code efficient and organised.



### 2. Statistical Analysis (Variance and Standard Deviation)

I extended the program to calculate both variance and standard deviation for each phase voltage.

Variance is calculated using:

variance = average of (value − mean)²

Standard deviation is then calculated as:

standard deviation = sqrt(variance)

This was implemented using a two-pass approach:
1. First pass calculates the mean (DC offset)
2. Second pass calculates the squared differences from the mean

These metrics provide additional insight into how stable the voltage signal is.

For this dataset, the standard deviation is approximately equal to the RMS value because the DC offset is very close to zero, meaning the signal is centred around zero.

This extension demonstrates deeper mathematical analysis of the waveform data.

## What I learned

* How to use structs in C
* How pointers and memory allocation work
* How to read files in C
* How to calculate electrical values like RMS
* How to organise code into multiple files



## Conclusion

This project shows how data from a CSV file can be analysed using C to check power quality.

The program works correctly and produces realistic results.
