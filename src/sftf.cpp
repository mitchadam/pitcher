// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------
#include "fourier.h"
#include <iostream> // remove

/*
implementation of Short time fourier transform
*/
std::vector<CVector> SFTF(CVector& signal, int sampleSize, int overlap){
    // Sample rate is always 44.1 kHz
    // Signal Size determines resolution

    int n = signal.size();
    // This will be a vector of the fft of each window
    std::vector<CVector> windowFFTS;

    // Create a window every half window size
    for (int i = 0; i <= n; i += sampleSize/overlap) {
        // Uses hann window function to create window, zero
        //everywhere outside of window
        CVector scalingWindow = createWindow(n, i, sampleSize);
        CVector signalWindow = signal * scalingWindow;

        //Now that we have the windowed signal, fft signal
        FFT(signalWindow);

        windowFFTS.push_back(signalWindow);
    }
    return windowFFTS;
}

CVector createWindow(int n, int center, int size){
    CVector scaling;
    scaling.resize(n,0);

    // Go backwards from center
    for(int i = 1; i <= size/2; i++){
        if ((center - i ) >= 0 && (center-i) < n){
            scaling[center -i]= {0.5 * (1 - cos(2*PI*(size/2-i)/(size-1))),0};
        }
    }
    // Go forwards from center
    for(int i =0; i <= size/2-1;i++){
        if((center + i) < n && (center + i >= 0)){
            scaling[center + i]= {0.5 * (1 - cos(2*PI*(size/2+i)/(size-1))),0};
        }
    }
    return scaling;
}

