// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#ifndef _CALC_FREQ_H_
#define _CALC_FREQ_H_

#include <vector>

#include "fourier.h" // CVector

/**
 * Does desired pitch shifting in the frequency domain
 */
void processSTFT(std::vector<CVector> &stft, double pitchScaleFactor);

#endif
