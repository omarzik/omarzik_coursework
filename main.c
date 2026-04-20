#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "waveform.h"

int main() {
    WaveformSample *data;
    int count = 0;

    data = load_csv("power_quality_log.csv", &count);

    printf("Count: %d\n", count); // DEBUG

    if (data == NULL || count == 0) {
        printf("Error: No data loaded\n");
        return 1;
    }

    double rms = calculate_rms(data, count);
    double peak = calculate_peak_to_peak(data, count);
    double dc = calculate_dc_offset(data, count);
    int clipping = detect_clipping(data, count);
    int within_tolerance = check_tolerance(rms);

    printf("Total samples: %d\n", count);
    printf("RMS Voltage: %.2f\n", rms);
    printf("Peak-to-Peak: %.2f\n", peak);
    printf("DC Offset: %.2f\n", dc);
    printf("Clipping: %s\n", clipping ? "YES" : "NO");
    printf("Within Tolerance: %s\n", within_tolerance ? "YES" : "NO");

    FILE *out = fopen("results.txt", "w");

    if (out != NULL) {
        fprintf(out, "Total samples: %d\n", count);
        fprintf(out, "RMS Voltage: %.2f\n", rms);
        fprintf(out, "Peak-to-Peak: %.2f\n", peak);
        fprintf(out, "DC Offset: %.2f\n", dc);
        fprintf(out, "Clipping: %s\n", clipping ? "YES" : "NO");
        fprintf(out, "Within Tolerance: %s\n", within_tolerance ? "YES" : "NO");

        fclose(out);
    }

    free(data);
    return 0;
}