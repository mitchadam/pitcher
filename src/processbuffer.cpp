// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include "processbuffer.h"

#include "processstft.h"

#include <iostream> // TODO remove

void processBuffer(double *buffer, std::size_t bufferLen, int channels,
                   Key key) {
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

  // Calculate the target freqency and scale factor
  double target = getTargetFreq(fund, key);
  double pitchScaleFactor = target / fund;

  std::cout << "fund: " << fund << std::endl;
  std::cout << "target: " << target << std::endl;
  std::cout << "scale: " << pitchScaleFactor << std::endl;
  std::cout << std::endl;

  // Taper the edges of the buffer
  CVector window = createWindow(bufferLen, bufferLen / 2, bufferLen);
  bufferVector *= window;

  // SFTF the buffer
  std::size_t windowSize = 2048;
  std::size_t overlapFactor = 8;
  std::vector<CVector> stft = SFTF(bufferVector, windowSize, overlapFactor);

  processSTFT(stft, windowSize, overlapFactor, 2);

  // Inverse STFT
  bufferVector = ISFTF(stft, windowSize, overlapFactor);

  // compensates for increase in amplitude do to overlapping windows
  double gain = 0.25;
  // Covert CVector back into array of doubles
  for (chan = 0; chan < channels; chan++) {
    for (k = chan; k < bufferLen; k += channels) {
      // Convert each value in the buffer into a complex number
      buffer[k] = bufferVector[k].real() * gain;
    }
  }

  return;
}
