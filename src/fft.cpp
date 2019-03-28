// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------
#include "fourier.h"

void FFT(CVector& z){
    const size_t n = z.size();
    // Base Case, ends recursion
    if (n <= 1) return;

    // Split up signal into even and odd components
    CVector zeven =  z[std::slice(0, n/2, 2)];
    CVector zodd = z[std::slice(1, n/2, 2)];

    // Recursivley call FFT on each component
    FFT(zeven);
    FFT(zodd);

    // Recombine the FFT of the even and odd components
    for (size_t i = 0; i < n/2; ++i) {
        // Mutiple odd components by common mutlipler
        CNum g =  std::polar(1.0, -2 * PI * i/n) * zodd[i];

        //From periodicity of complex ecponential
        //We can more efficiently combine the even and off components as
        //follows
        z[i] = zeven[i] + g;
        z[i+n/2]= zeven[i] - g;
    }
}
