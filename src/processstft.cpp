// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include "processstft.h"

void processSTFT(std::vector<CVector> &stft,
                 std::vector<std::vector<double>> &actualFreqs,
                 std::vector<std::vector<double>> &magnitudes) {
  // Length of the buffer (time domain length is same as freq domain length)
  std::size_t bufferLen = stft[0].size();

  // Ensure actualFreqs and magnitudes vectors have length equal to the number
  // of bins (which is the same as bufferLen)
  actualFreqs.resize(bufferLen);
  magnitudes.resize(bufferLen);

  // Loop across frequency bins
  for (std::size_t freqIndex = 0; freqIndex < bufferLen; freqIndex++) {
    // Loop across stft windows
    for (std::size_t windowIndex = 0; windowIndex < stft.size();
         windowIndex++) {
      // Calculate magnitude of the bin
      magnitudes[windowIndex][freqIndex] =
          std::abs(stft[windowIndex][freqIndex]);
    }
  }
}
