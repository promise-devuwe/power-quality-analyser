#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#define MAX_SAMPLES 1000
WaveformSample* load_csv(const char *filename, int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File not found!\n");
        return NULL;
    }

    char header[1024];
    if (fgets(header, sizeof(header), file) == NULL) {
        printf("Error: File is empty or invalid!\n");
        fclose(file);
        return NULL;
    }

    WaveformSample *data = malloc(sizeof(WaveformSample) * MAX_SAMPLES);
    if (data == NULL) {
        printf("Error: Memory allocation failed!\n");
        fclose(file);
        return NULL;
    }

    int i = 0;

    while (i < MAX_SAMPLES &&
        fscanf(file, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
               &data[i].timestamp, &data[i].phase_A_voltage,
               &data[i].phase_B_voltage, &data[i].phase_C_voltage,
               &data[i].line_current, &data[i].frequency,
               &data[i].power_factor, &data[i].thd_percent) == 8) {
        i++;
               }

    if (i == 0) {
        printf("Error: No valid sample data found in file!\n");
        free(data);
        fclose(file);
        return NULL;
    }
    *count = i;
    fclose(file);
    return data;
}
void save_results(PhaseReport *reports) {
    FILE *f = fopen("power_quality_log_results.txt", "w");
    if (f == NULL) {
        printf("Error: Could not create output file!\n");
        return;
    }

    fprintf(f, "Power Quality Waveform Analysis Report\n");
    fprintf(f, "====================================\n\n");

    for (int i = 0; i < 3; i++) {
        fprintf(f, "%s\n", reports[i].phase_name);
        fprintf(f, "------------------------------\n");
        fprintf(f, "RMS Voltage: %.3f V\n", reports[i].rms);
        fprintf(f, "Peak-to-Peak Voltage: %.3f V\n", reports[i].peak_to_peak);
        fprintf(f, "DC Offset: %.6f V\n", reports[i].dc_offset);
        fprintf(f, "Clipped Samples: %d\n", reports[i].clipped_count);
        fprintf(f, "Compliance: %s\n\n", reports[i].is_compliant ? "COMPLIANT" : "NON-COMPLIANT");
    }

    fclose(f);
