#include "processbuffer.h"

#include "processstft.h"

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

  // SFTF the buffer
  std::vector<CVector> stft = SFTF(bufferVector, 2048, 4);

  processSTFT(stft, 2);

  // Inverse STFT

  return;
}
