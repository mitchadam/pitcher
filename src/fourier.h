// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------
#ifndef _FOURIER_H_
#define _FOURIER_H_

#include <vector>
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

/*
    Handles the Inverse fourier transform by scaling 1/n
*/
void applyIFFT(CVector& z);
/*
    Inverse fft, works by chagning the sign in exponenent of fft
*/
void IFFT(CVector& z);

/*
    Implemntation of the short time fourier transform
    Breaks up signal into windows to get more accurate ffts
*/
std::vector<CVector> SFTF(CVector& z, int sampleSize, int overlap);
/*
    Used by STFT to create the windows of a signal
*/
CVector createWindow(int n, int center, int size);
/*
    Inverse SFTF
    First does the IFFT and then adds the windows back up
*/
CVector ISFTF (std::vector<CVector> windowFFTS, int sampleSize, int overlap);
#endif