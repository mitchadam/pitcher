// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#ifndef _FUNDAMENTAL_H_
#define _FUNDAMENTAL_H_

#include <complex>
#include <valarray>

#include "fourier.h"

// Used to represent the complex numbers in arary
typedef std::complex<double> CNum;
typedef std::valarray<CNum> CVector;

/**
 * Estimates the fundamental frequency of a signal using autocorrelation
 * @param signal The signal to analyze
 * @param sampleRate The sample rate in Hz of the signal
 */
double fundamental(CVector &signal, unsigned long sampleRate);

#endif
