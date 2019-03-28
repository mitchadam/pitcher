// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------
#ifndef _FFT_H_
#define _FFT_H_

#include <complex>
#include <valarray>

// Used to represent the complex numbers in arary
typedef std::complex<double> CNum;
typedef std::valarray<CNum> CVector;

const double PI = 3.141592653589793238460;

/*
    Implmentation of the Cooley-Tukey FFT algorthim
    Algorthim works by splitting signal into odd and even components and
    recursivley computing the FFT of each component
    Runs in O(nlog(n)) where n is the length of the array representing the s
    ignal
    Note: n must be a power of 2
    Parameters: z - an array representing the signal, using the valarray
    library
*/
void FFT(CVector& z);

void applyIFFT(CVector& z);
void IFFT(CVector& z);

#endif