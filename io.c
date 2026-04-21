#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "io.h"

int load_data(const char *filename, WaveformSample **data) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("Error opening file\n");
        return 0;
    }

    int capacity = 1000;
    int count = 0;

    *data = malloc(capacity * sizeof(WaveformSample));


    fscanf(file, "%*[^\n]\n");

    while (fscanf(file, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                  &(*data)[count].timestamp,
                  &(*data)[count].phase_A_voltage,
                  &(*data)[count].phase_B_voltage,
                  &(*data)[count].phase_C_voltage,
                  &(*data)[count].current,
                  &(*data)[count].frequency,
                  &(*data)[count].power_factor,
                  &(*data)[count].thd) == 8) {
        count++;
    }

    fclose(file);
    return count;
}