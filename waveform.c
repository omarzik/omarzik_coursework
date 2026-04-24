#include <math.h>
#include "waveform.h"

double get_voltage(WaveformSample s, char phase) {
    if (phase == 'A')
        return s.phase_A_voltage;
    if (phase == 'B')
        return s.phase_B_voltage;
    return s.phase_C_voltage;
}

double compute_rms(WaveformSample *data, int count, char phase) {
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        double v = get_voltage(data[i], phase);
        sum += v * v;
    }
    return sqrt(sum / count);
}

double compute_peak_to_peak(WaveformSample *data, int count, char phase) {
    double max = get_voltage(data[0], phase);
    double min = max;

    for (int i = 1; i < count; i++) {
        double v = get_voltage(data[i], phase);
        if (v > max)
            max = v;
        if (v < min)
            min = v;
    }
    return max - min;
}

double compute_dc_offset(WaveformSample *data, int count, char phase) {
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += get_voltage(data[i], phase);
    }
    return sum / count;
}

int detect_clipping(WaveformSample *data, int count) {
    int clipped_rows = 0;

    for (int i = 0; i < count; i++) {
        if (fabs(data[i].phase_A_voltage) >= 324.9 ||
            fabs(data[i].phase_B_voltage) >= 324.9 ||
            fabs(data[i].phase_C_voltage) >= 324.9) {
            clipped_rows++;
        }
    }

    // Convert phase-based rows into cycle-based events
    int clipped_events = clipped_rows / 3;

    return clipped_events;
}
double compute_frequency_min(WaveformSample *data, int count) {
    double min = data[0].frequency;
    for (int i = 1; i < count; i++)
        if (data[i].frequency < min)
            min = data[i].frequency;
    return min;
}

double compute_frequency_max(WaveformSample *data, int count) {
    double max = data[0].frequency;
    for (int i = 1; i < count; i++)
        if (data[i].frequency > max)
            max = data[i].frequency;
    return max;
}

double compute_pf_min(WaveformSample *data, int count) {
    double min = data[0].power_factor;
    for (int i = 1; i < count; i++)
        if (data[i].power_factor < min) min = data[i].power_factor;
    return min;
}

double compute_pf_max(WaveformSample *data, int count) {
    double max = data[0].power_factor;
    for (int i = 1; i < count; i++)
        if (data[i].power_factor > max)
            max = data[i].power_factor;
    return max;
}

double compute_thd_min(WaveformSample *data, int count) {
    double min = data[0].thd;
    for (int i = 1; i < count; i++)
        if (data[i].thd < min)
            min = data[i].thd;
    return min;
}

double compute_thd_max(WaveformSample *data, int count) {
    double max = data[0].thd;
    for (int i = 1; i < count; i++)
        if (data[i].thd > max)
            max = data[i].thd;
    return max;
}

void update_status_flags(WaveformSample *data, int count, double rmsA, double rmsB, double rmsC) {
    for (int i = 0; i < count; i++) {
        data[i].status = 0;

        if (fabs(data[i].phase_A_voltage) >= 324.9 ||
            fabs(data[i].phase_B_voltage) >= 324.9 ||
            fabs(data[i].phase_C_voltage) >= 324.9) {
            data[i].status |= CLIPPING_FLAG;
        }

        if (rmsA < 207.0 || rmsA > 253.0 ||
            rmsB < 207.0 || rmsB > 253.0 ||
            rmsC < 207.0 || rmsC > 253.0) {
            data[i].status |= RMS_FLAG;
        }

        if (data[i].thd > 5.0) {
            data[i].status |= THD_FLAG;
        }
    }
}