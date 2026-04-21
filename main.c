#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "io.h"

int main() {
    WaveformSample *data = NULL;
    int count = load_data("power_quality_log.csv", &data);

    if (count <= 0) {
        printf("No data loaded\n");
        return 1;
    }

    double rmsA = compute_rms(data, count, 'A');
    double p2pA = compute_peak_to_peak(data, count, 'A');
    double dcA = compute_dc_offset(data, count, 'A');
    int clipped = detect_clipping(data, count);

    double fmin = compute_frequency_min(data, count);
    double fmax = compute_frequency_max(data, count);
    double pfmin = compute_pf_min(data, count);
    double pfmax = compute_pf_max(data, count);
    double thdmin = compute_thd_min(data, count);
    double thdmax = compute_thd_max(data, count);

    FILE *out = fopen("results.txt", "w");

    fprintf(out, "Phase A RMS: %.2f V\n", rmsA);
    fprintf(out, "Peak-to-Peak: %.2f V\n", p2pA);
    fprintf(out, "DC Offset: %.2f V\n", dcA);
    fprintf(out, "Clipped Samples: %d\n", clipped);
    fprintf(out, "Frequency Range: %.3f - %.3f Hz\n", fmin, fmax);
    fprintf(out, "Power Factor Range: %.3f - %.3f\n", pfmin, pfmax);
    fprintf(out, "THD Range: %.2f - %.2f %%\n", thdmin, thdmax);

    fclose(out);

    printf("Results written to results.txt\n");

    free(data);
    return 0;
}