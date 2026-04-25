#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "io.h"
#include <math.h>

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
    update_status_flags(data, count, rmsA, rmsB, rmsC);
    double peakA = compute_peak_to_peak(data, count, 'A');
    double dcOffsetA = compute_dc_offset(data, count, 'A');
    int clipped = detect_clipping(data, count);

    double fmin = compute_frequency_min(data, count);
    double fmax = compute_frequency_max(data, count);
    double pfmin = compute_pf_min(data, count);
    double pfmax = compute_pf_max(data, count);
    double thdmin = compute_thd_min(data, count);
    double thdmax = compute_thd_max(data, count);
    double varA = compute_variance(data, count, 'A');
    double varB = compute_variance(data, count, 'B');
    double varC = compute_variance(data, count, 'C');

    double stdA = compute_standard_deviation(data, count, 'A');
    double stdB = compute_standard_deviation(data, count, 'B');
    double stdC = compute_standard_deviation(data, count, 'C');

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
    for (int i = 0; i < count; i++) {
        if (data[i].status != 0) {
            fprintf(output, "Sample %d Status: ", i);

            if (data[i].status & CLIPPING_FLAG) {
                fprintf(output, "[CLIPPING: ");

                if (fabs(data[i].phase_A_voltage) >= 324.9)
                    fprintf(output, "A ");

                if (fabs(data[i].phase_B_voltage) >= 324.9)
                    fprintf(output, "B ");

                if (fabs(data[i].phase_C_voltage) >= 324.9)
                    fprintf(output, "C ");

                fprintf(output, "] ");
            }
            if (data[i].status & RMS_FLAG)
                fprintf(output, "[RMS OUT OF TOLERANCE] ");
            if (data[i].status & THD_FLAG)
                fprintf(output, "[HIGH THD] ");

            fprintf(output, "\n");
        }
    }
    fprintf(output, "Phase A Variance: %.2f V^2\n", varA);
    fprintf(output, "Phase B Variance: %.2f V^2\n", varB);
    fprintf(output, "Phase C Variance: %.2f V^2\n", varC);

    fprintf(output, "Phase A Standard Deviation: %.2f V\n", stdA);
    fprintf(output, "Phase B Standard Deviation: %.2f V\n", stdB);
    fprintf(output, "Phase C Standard Deviation: %.2f V\n", stdC);
    fclose(output);

    printf("Results written to results.txt\n");

    free(data);
    return 0;
}