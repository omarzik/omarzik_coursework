#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <stdint.h>

#define CLIPPING_FLAG  (1 << 0)
#define RMS_FLAG       (1 << 1)
#define THD_FLAG       (1 << 2)

typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double current;
    double frequency;
    double power_factor;
    double thd;
    uint8_t status;
} WaveformSample;

double compute_rms(WaveformSample *data, int count, char phase);
double compute_peak_to_peak(WaveformSample *data, int count, char phase);
double compute_dc_offset(WaveformSample *data, int count, char phase);

int detect_clipping(WaveformSample *data, int count);
double compute_frequency_min(WaveformSample *data, int count);
double compute_frequency_max(WaveformSample *data, int count);
double compute_pf_min(WaveformSample *data, int count);
double compute_pf_max(WaveformSample *data, int count);
double compute_thd_min(WaveformSample *data, int count);
double compute_thd_max(WaveformSample *data, int count);
double compute_variance(WaveformSample *data, int count, char phase);
double compute_standard_deviation(WaveformSample *data, int count, char phase);

void update_status_flags(WaveformSample *data, int count, double rmsA, double rmsB, double rmsC);

#endif