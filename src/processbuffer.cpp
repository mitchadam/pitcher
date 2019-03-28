// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include "processbuffer.h"

void processBuffer(double *buffer, std::size_t bufferLen, int channels) {
  int k, chan;

  // Construct a valarray of complex numbers from the input buffer
  CVector bufferVector;
  bufferVector.resize(bufferLen);

  for (chan = 0; chan < channels; chan++) {
    for (k = chan; k < bufferLen; k += channels) {
      // Convert each value in the buffer into a complex number
      bufferVector[k] = CNum(buffer[k], 0);
    }
  }

  // Calculate the fundamental frequency
  double fund = fundamental(bufferVector, 44100);

  // Construct array of actual frequencies of each bin
  // based on how the phase changes in the same bin between windows

  // Construct array of magnitudes

  // Do resampling to shift pitch
  // Simply move magnitudes to new indeces
  // Move AND scale actual frequencies

  // Convert actual frequencies back to array of phases

  // Use phase and magnitudes to calculate re and im parts

  // Inverse FFT each window

  // Add windows back together

  return;
}
