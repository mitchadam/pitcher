// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------
#include "fourier.h"

CVector ISFTF (std::vector<CVector> windowFFTS, int sampleSize, int overlap){

    //Create output signal
    CVector outputSignal;
    size_t n = windowFFTS[0].size();
    outputSignal.resize(n,0);

    for (size_t i = 0; i < windowFFTS.size(); i++) {
        //Inverse FT each window first
        applyIFFT(windowFFTS[i]);
        // Apply window
        CVector window = createWindow(n, i * sampleSize / overlap, sampleSize);
        windowFFTS[i] *= window;
    }
    //Add together all the windows to get the ouput window
    //Loop through the bins
    for (size_t i = 0; i < n; i++) {
        //Loop through the windows
        for (size_t j = 0; j < windowFFTS.size(); j++) {
            // Set weach ouput bin as sum of corresponding window bins
            outputSignal[i] += windowFFTS[j][i];
        }
    }
    return outputSignal;
}
