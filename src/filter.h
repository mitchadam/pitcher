// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include "fourier.h" // CVector

#ifndef _FILTER_H_
#define _FILTER_H_

/**
 * Generates low pass filter transfer function (H(w)) for a given cutoff
 * frequency
 * @param cutoff The filter cutoff frequency in Hz
 * @param length The length of the signal or buffer
 * @param sampleRate The sample rate of the signal
 */
CVector lowPassTransferFunction(double cutoff, std::size_t length, int sampleRate);

/**
 * Generates high pass filter transfer function (H(w)) for a given cutoff
 * frequency
 * @param cutoff The filter cutoff frequency in Hz
 * @param length The length of the signal or buffer
 * @param sampleRate The sample rate of the signal
 */
CVector highPassTransferFunction(double cutoff, std::size_t length, int sampleRate);

#endif
