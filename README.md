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



## What I learned

* How to use structs in C
* How pointers and memory allocation work
* How to read files in C
* How to calculate electrical values like RMS
* How to organise code into multiple files



## Conclusion

This project shows how data from a CSV file can be analysed using C to check power quality.

The program works correctly and produces realistic results.
