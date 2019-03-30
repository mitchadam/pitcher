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
 *
 * @param stft The short time Fourier Transform representation of the signal
 * @param windowSize The size of a window in the stft
 * @param overlapFactor Amount of overlap between windows
 *   e.g. If the next window starts 1/4 of the way into the current window,
 *   then overlapFactor = 4
 * @param pitchScaleFactor The amount to multiply all the frequency components
 * of the signal
 */
void processSTFT(std::vector<CVector> &stft, std::size_t windowSize,
                 std::size_t overlapFactor, double pitchScaleFactor);

#endif
