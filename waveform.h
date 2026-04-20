#ifndef WAVEFORM_H
#define WAVEFORM_H

typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} WaveformSample;

// Functions
double calculate_rms(WaveformSample *data, int count);
double calculate_peak_to_peak(WaveformSample *data, int count);
double calculate_dc_offset(WaveformSample *data, int count);
int detect_clipping(WaveformSample *data, int count);
int check_tolerance(double rms);

#endif