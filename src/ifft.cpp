// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------
#include "fourier.h"

void applyIFFT(CVector& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);

    // forward fft
    FFT(x);

    // conjugate the complex numbers again
    x = x.apply(std::conj);

    // scale the numbers
    x /= x.size();
}
