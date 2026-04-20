# Waveform Analysis Coursework

This project processes waveform data from a CSV file and performs calculations such as RMS.

## Features (in progress)
- Reading waveform data from a file
- Storing data using structs
-  Parsing multiple CSV rows into dynamically allocated structs
- Future: RMS calculations

## Files
- main.c: main program
- waveform.h: struct definition
- io.h: planned file handling functions

## Status
Currently reading multiple rows of CSV data using dynamic memory allocation.

Modularised code by separating file handling into io.c.

Implemented dynamic resizing using realloc for scalable data handling

Implemented RMS calculation for waveform data

Added waveform.c for signal processing functions