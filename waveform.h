#ifndef WAVEFORM_H
#define WAVEFORM_H

/**
 * @file waveform.h
 * @brief Basic constants for UK Power Quality (230V RMS)
 */

#define CLIPPING_LIMIT 324.99  /**< Hard limit of the sensor */
#define NOMINAL_RMS 230.0      /**< Standard UK Grid Voltage */

typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} WaveformSample;

typedef struct {
    char phase_name[16];
    double rms;
    double peak_to_peak;
    double dc_offset;
    int clipped_count;
    int is_compliant; // 1 for Yes, 0 for No
} PhaseReport;

// Function Prototypes
void analyze_phase(WaveformSample *samples, int count, char phase, PhaseReport *report);
double get_voltage(WaveformSample *sample, char phase);

#endif
