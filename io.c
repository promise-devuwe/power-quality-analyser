#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"

WaveformSample* load_csv(const char *filename, int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File not found!\n");
        return NULL;
    }

    char header[1024];
    fgets(header, 1024, file); // Skip top row

    // Allocate memory for 1000 samples
    WaveformSample *data = malloc(sizeof(WaveformSample) * 1000);
    int i = 0;

    while (fscanf(file, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                  &data[i].timestamp, &data[i].phase_A_voltage,
                  &data[i].phase_B_voltage, &data[i].phase_C_voltage,
                  &data[i].line_current, &data[i].frequency,
                  &data[i].power_factor, &data[i].thd_percent) == 8) {
        i++;
                  }

    *count = i;
    fclose(file);
    return data;
}

void save_results(PhaseReport *reports) {
    FILE *f = fopen("results.txt", "w");
    fprintf(f, "UWE Power Quality Report\n--------------------\n");
    for (int i = 0; i < 3; i++) {
        fprintf(f, "Phase: %s\n", reports[i].phase_name);
        fprintf(f, "RMS: %.2f V\n", reports[i].rms);
        fprintf(f, "Pass/Fail: %s\n", reports[i].is_compliant ? "PASS" : "FAIL");
        fprintf(f, "Clipped: %d samples\n\n", reports[i].clipped_count);
    }
    fclose(f);
}