#include <stdio.h>
#include <math.h>
#include "waveform.h"

/** Helper to pick the right phase from the struct */
double get_voltage(WaveformSample *sample, char phase) {
    if (phase == 'A') return sample->phase_A_voltage;
    if (phase == 'B') return sample->phase_B_voltage;
    return sample->phase_C_voltage;
}

/** The main analysis logic using pointers */
void analyze_phase(WaveformSample *samples, int count, char phase, PhaseReport *report) {
    if (samples == NULL || report == NULL || count <= 0) {
        return;
    }
    double sum_sq = 0.0;
    double sum_raw = 0.0;
    double max_v = get_voltage(samples, phase);
    double min_v = get_voltage(samples, phase);
    int clipped = 0;

    for (int i = 0; i < count; i++) {
        // Pointer arithmetic: moving to the next memory address
        WaveformSample *current = (samples + i);
        double v = get_voltage(current, phase);

        sum_sq += (v * v);
        sum_raw += v;

        if (v > max_v) max_v = v;
        if (v < min_v) min_v = v;
        if (fabs(v) >= CLIPPING_LIMIT) clipped++;
    }

    report->rms = sqrt(sum_sq / count);           // RMS calculation
    report->dc_offset = sum_raw / count;          // DC offset calculation
    report->peak_to_peak = max_v - min_v;         // P-P calculation
    report->clipped_count = clipped;              // Clipping check

    // Set acceptable voltage range (±10% of nominal)
    double lower_limit = NOMINAL_RMS * 0.9;
    double upper_limit = NOMINAL_RMS * 1.1;

    // Check if RMS is within limits
    if (report->rms >= lower_limit && report->rms <= upper_limit) {
        report->is_compliant = 1;  // within range
    } else {
        report->is_compliant = 0;  // outside range
    }
    }
