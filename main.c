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
    double rmsB = compute_rms(data, count, 'B');
    double rmsC = compute_rms(data, count, 'C');
    double peakA = compute_peak_to_peak(data, count, 'A');
    double dcOffsetA = compute_dc_offset(data, count, 'A');
    int clipped = detect_clipping(data, count);

    double fmin = compute_frequency_min(data, count);
    double fmax = compute_frequency_max(data, count);
    double pfmin = compute_pf_min(data, count);
    double pfmax = compute_pf_max(data, count);
    double thdmin = compute_thd_min(data, count);
    double thdmax = compute_thd_max(data, count);

    FILE *output = fopen("results.txt", "w");

    fprintf(output, "Phase A RMS: %.2f V (%s, range: 207–253 V)\n",
            rmsA, (rmsA >= 207.0 && rmsA <= 253.0) ? "COMPLIANT" : "OUT OF TOLERANCE");
    fprintf(output, "Phase B RMS: %.2f V (%s, range: 207–253 V)\n",
            rmsB, (rmsB >= 207.0 && rmsB <= 253.0) ? "COMPLIANT" : "OUT OF TOLERANCE");
    fprintf(output, "Phase C RMS: %.2f V (%s, range: 207–253 V)\n",
            rmsC, (rmsC >= 207.0 && rmsC <= 253.0) ? "COMPLIANT" : "OUT OF TOLERANCE");
    fprintf(output, "Peak-to-Peak: %.2f V\n", peakA);
    fprintf(output, "DC Offset: %.2f V\n", dcOffsetA);
    fprintf(output, "Clipped Samples: %d\n", clipped);
    fprintf(output, "Frequency Range: %.3f - %.3f Hz\n", fmin, fmax);
    fprintf(output, "Power Factor Range: %.3f - %.3f\n", pfmin, pfmax);
    fprintf(output, "THD Range: %.2f - %.2f %%\n", thdmin, thdmax);

    fclose(output);

    printf("Results written to results.txt\n");

    free(data);
    return 0;
}