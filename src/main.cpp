#include <iostream>
#include <cstdio>

#include "reader.h"
#include "writer.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <fftw3.h>

#define NUM_POINTS 64

/* Never mind this bit */
#define REAL 0
#define IMAG 1

void acquire_from_somewhere(fftw_complex* signal) {
    /* Generate two sine waves of different frequencies and
     * amplitudes.
     */
    int i;
    for (i = 0; i < NUM_POINTS; ++i) {
        double theta = (double)i / (double)NUM_POINTS * M_PI;

        signal[i][REAL] = 1.0 * cos(10.0 * theta) +
                          0.5 * cos(25.0 * theta);

        signal[i][IMAG] = 1.0 * sin(10.0 * theta) +
                          0.5 * sin(25.0 * theta);
    }
}

void do_something_with(fftw_complex* result) {
    int i;
    for (i = 0; i < NUM_POINTS; ++i) {
        double mag = sqrt(result[i][REAL] * result[i][REAL] +
                          result[i][IMAG] * result[i][IMAG]);

        printf("%g\n", mag);
    }
}


/* Resume reading here */

int main() {

    const std::string file_name = "waveform.wav";

    const float sampleRate = 44100;
    const float bitDepth = 16;

    SineOscillator sineOscillator(440, 0.5, sampleRate);

    Writer writer(sampleRate, bitDepth);
    writer.write(file_name, [&sineOscillator]() { 
        return sineOscillator.process(); 
    });



    fftw_complex signal[NUM_POINTS];
    fftw_complex result[NUM_POINTS];

    fftw_plan plan = fftw_plan_dft_1d(NUM_POINTS,
                                      signal,
                                      result,
                                      FFTW_FORWARD,
                                      FFTW_ESTIMATE);

    acquire_from_somewhere(signal);
    fftw_execute(plan);
    do_something_with(result);
    fftw_destroy_plan(plan);
    std::cin.get();
    return 0;
}