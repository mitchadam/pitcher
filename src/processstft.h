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
 * Computes corrected bin frequencies and bin magnitudes from stft
 */
void processSTFT(std::vector<CVector> &stft,
                 std::vector<std::vector<double>> &actualFreqs,
                 std::vector<std::vector<double>> &magnitudes);

#endif
