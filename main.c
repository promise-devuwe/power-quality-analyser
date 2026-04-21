#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "waveform.h"
#include "io.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Drag your CSV onto the program or type: ./program file.csv\n");
        return 1;
    }

    int total_samples = 0;
    WaveformSample *data = load_csv(argv[1], &total_samples);

    if (data == NULL) return 1;

    PhaseReport reports[3];
    char names[] = {'A', 'B', 'C'};

    for (int i = 0; i < 3; i++) {
        snprintf(reports[i].phase_name, sizeof(reports[i].phase_name), "Phase %c", names[i]);
        analyze_phase(data, total_samples, names[i], &reports[i]);
    }

    save_results(reports);

    save_results(reports);
    printf("Successfully analyzed %d samples. Check power_quality_log_results.txt\n", total_samples);

    free(data); // free allocated memory

    return 0;
}
