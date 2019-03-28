// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------
#include "fourier.h"

/*
implementation of Short time fourier transform
*/
std::vector<CVector> SFTF(CVector& signal){
    // This will change the resolution
    // Sample rate is always 44.1 kHz
    int sampleSize = 2048;
    int n = signal.size();
    // This will be a vector of the fft of each window
    std::vector<CVector> windowFFTS;

    // Create a window every half window size
    for (size_t i = 0; i <=n; i += sampleSize/2) {
        // Uses hann window function to create window, zero
        //everywhere outside of window
        CVector scalingWindow = createWindow(n, i, sampleSize);
        CVector signalWindow = signal * scalingWindow;

        FFT(signalWindow);
        windowFFTS.push_back(signalWindow);
    }
    return windowFFTS;
}

/*
    Creates an array to multiple buffer by in order to get the correct sample
    window
    Uses the hann Window function
*/
CVector createWindow(int n, int center, int size){
    CVector scaling;
    scaling.resize(n,0);
    //Start and end points of each window
    int start = center - size/2;
    int end = center + size/2-1;
    int j = 0;

    //Handle Edge cases of first and last window
    if(center == 0){
        start = 0;
        end = size/2-1;
    }else if (center == n){
        start = n-size/2;
        end = n-1;
    }
    // If outside start and end value will be zero
    for(int i = start; i <= end; i ++){
        // Set scaling value if inside the window
        scaling[i]= {0.5 * (1 - cos(2*PI*j/(size-1))),0};
        j++;
    }
    return scaling;
}

