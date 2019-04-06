// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include <cmath> // log()

#include "fundamental.h"


double fundamental(CVector &signal, unsigned long sampleRate) {
  // Ignore this many elements from the edges of the autocorrelation signal
  // Sometimes the autocorrelation signal has weird behaviour at the edges
  std::size_t edgeIgnore = 100;

  // Create a copy of the signal to perform fft on
  CVector copy = signal;

  // Compute the autocorrelation of the signal via the frequency domain
  FFT(copy);
  for (auto &element : copy) {
    element = element * std::conj(element);
  }
  applyIFFT(copy);

  // Find peak in the autocorrelation
  // Ignore the edges (lowest and highest frequencies)
  double max = 0;
  std::size_t maxIndex = 0;
  for (std::size_t i = edgeIgnore; i < copy.size() - edgeIgnore; i++) {
    // Since we are back in the time domain, the autocorrelation signal should
    // be real
    if (copy[i].real() > max) {
      max = copy[i].real();
      maxIndex = i;
    }
  }

  // Calculate fundmental from index and sample rate
  double samplePeriod = 1/ ((double)sampleRate);
  double fundamentalPeriod = maxIndex * samplePeriod;
  double fundamental = 1 / fundamentalPeriod;
  return fundamental;
}
