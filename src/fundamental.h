#ifndef _FUNDAMENTAL_H_
#define _FUNDAMENTAL_H_

#include <complex>
#include <valarray>

#include "fft.h"

// Used to represent the complex numbers in arary
typedef std::complex<double> CNum;
typedef std::valarray<CNum> CVector;

/**
 * Estimates the fundamental frequency of a signal
 * @param signal The signal to analyze
 * @param sampleRate The sample rate in Hz of the signal
 */
double fundamental(CVector &signal, unsigned long sampleRate);

#endif
