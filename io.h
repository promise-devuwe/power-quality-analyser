#ifndef IO_H
#define IO_H

#include "waveform.h"

/**
 * @brief Function prototypes for file handling
 */
WaveformSample* load_csv(const char *filename, int *count);
void save_results(PhaseReport *reports);

#endif