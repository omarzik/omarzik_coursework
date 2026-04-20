#include <math.h>
#include "waveform.h"

double calculate_rms(WaveformSample *data, int count) {
    if (count == 0) return 0;

    double sum = 0.0;

    for (int i = 0; i < count; i++) {
        sum += data[i].phase_A_voltage * data[i].phase_A_voltage;
    }

    return sqrt(sum / count);
}

double calculate_peak_to_peak(WaveformSample *data, int count) {
    if (count == 0) return 0;

    double max = data[0].phase_A_voltage;
    double min = data[0].phase_A_voltage;

    for (int i = 1; i < count; i++) {
        if (data[i].phase_A_voltage > max)
            max = data[i].phase_A_voltage;

        if (data[i].phase_A_voltage < min)
            min = data[i].phase_A_voltage;
    }

    return max - min;
}

double calculate_dc_offset(WaveformSample *data, int count) {
    if (count == 0) return 0;

    double sum = 0.0;

    for (int i = 0; i < count; i++) {
        sum += data[i].phase_A_voltage;
    }

    return sum / count;
}

int detect_clipping(WaveformSample *data, int count) {
    for (int i = 0; i < count; i++) {
        if (fabs(data[i].phase_A_voltage) >= 324.9) {
            return 1;
        }
    }
    return 0;
}

int check_tolerance(double rms) {
    if (rms >= 207.0 && rms <= 253.0)
        return 1;
    return 0;
}