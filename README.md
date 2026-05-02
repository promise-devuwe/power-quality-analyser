 Power Quality Waveform Analysis Tool

This program analyses 3-phase industrial power quality waveform data from a CSV sensor log. It processes real-world electrical measurements, performs mathematical waveform analysis for each phase, and generates a structured engineering compliance report.

## Project Purpose
The software is designed to:
- Read and parse power quality CSV data
- Analyse Phase A, Phase B, and Phase C voltage waveforms
- Detect abnormalities in industrial power systems
- Evaluate compliance with UK nominal voltage standards

## Files Included
- main.c
- waveform.c
- waveform.h
- io.c
- io.h
- CMakeLists.txt
- power_quality_log.csv
- results.txt
- logbook.pdf
- README.md

## Mathematical Analysis Performed
The program calculates:

### For each voltage phase:
- RMS Voltage
- Peak-to-Peak Voltage
- DC Offset
- Clipping Detection (`|voltage| >= 324.9V`)
- Voltage Compliance Check (±10% of 230V nominal)

### Engineering formulas used:
- RMS = sqrt(mean(V²))
- Peak-to-Peak = Vmax - Vmin
- DC Offset = mean(V)

## Output File
The generated `results.txt` file contains:
- Phase name
- RMS voltage
- Peak-to-peak voltage
- DC offset
- Clipped sample count
- PASS/FAIL compliance status

## Build Instructions

### Using CLion
1. Open CLion
2. Select **Open Project**
3. Open the project folder containing all source files
4. Ensure `CMakeLists.txt` is present
5. Build using:
   - Build > Build Project
6. Run using:
   - Run > Run
7. Add command-line argument:
   - `power_quality_log.csv`

### Using Command-Line (GCC)
Compile:
```bash
gcc main.c waveform.c io.c -o analyser -lm
```

Run:
```bash
./analyser power_quality_log.csv
```

## Program Requirements Met
- Struct-based data organisation
- Dynamic memory allocation
- Pointer arithmetic
- File I/O
- Modular source structure
- Mathematical waveform analysis
- Report generation
- GitHub version control

## GitHub Repository
Replace with your actual repository:
https://github.com/promise-devuwe/power-quality-analyser

## Author
Promise Oviahon Agho

## Module
UGMFGT-15-1 Programming for Engineers  
University of the West of England
