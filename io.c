#include <stdio.h>
#include <stdlib.h>
#include "io.h"

WaveformSample *load_csv(const char *filename, int *count) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    int capacity = 2;
    *count = 0;

    WaveformSample *data = malloc(capacity * sizeof(WaveformSample));

    if (data == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Skip header
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    while (fscanf(file, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                  &data[*count].timestamp,
                  &data[*count].phase_A_voltage,
                  &data[*count].phase_B_voltage,
                  &data[*count].phase_C_voltage,
                  &data[*count].line_current,
                  &data[*count].frequency,
                  &data[*count].power_factor,
                  &data[*count].thd_percent) == 8) {

        if (*count >= capacity) {
            capacity *= 2;

            WaveformSample *temp = realloc(data, capacity * sizeof(WaveformSample));

            if (temp == NULL) {
                printf("Memory reallocation failed\n");
                free(data);
                fclose(file);
                return NULL;
            }

            data = temp;
        }

        (*count)++;
    }

    fclose(file);
    return data;
}