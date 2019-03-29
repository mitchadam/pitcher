// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include <cmath> // M_2_PI, fmod()

#include "processstft.h"

// Forward declaration
double constrainAngle(double angle);

void processSTFT(std::vector<CVector> &stft,
                 std::vector<std::vector<double>> &actualFreqs,
                 std::vector<std::vector<double>> &magnitudes) {

  double sampleRate = 44100;

  // Length of the buffer in samples (time domain length is same as freq domain
  // length)
  std::size_t bufferLen = stft[0].size();

  // frequency of bin 1
  double freqPerBin = sampleRate / bufferLen;

  // Length of a window in samples
  std::size_t windowLen = stft.size();

  // Number of samples between start of a window and the next window
  std::size_t windowStride = bufferLen / windowLen;

  // Amount of overlap between windows
  // e.g. If the next window starts 1/4 of the way into the current window,
  //      then overlapFactor = 4
  std::size_t overlapFactor = windowLen / windowStride;

  // Ensure actualFreqs and magnitudes vectors have length equal to the number
  // of bins (which is the same as bufferLen)
  actualFreqs.resize(bufferLen);
  magnitudes.resize(bufferLen);

  // Store previous previous of each bin as we loop through windows
  std::vector<double> previousPhase;
  // TODO what to initialize previous to?
  previousPhase.resize(bufferLen, 0);

  // Phase of current bin
  double phase;
  // Phase difference from previous bin
  double phaseDiff;
  // Expected phase difference between windows based on window overlap
  double expectedDiff;

  // Loop across frequency bins
  for (std::size_t freqIndex = 0; freqIndex < bufferLen; freqIndex++) {
    // Loop across stft windows
    for (std::size_t windowIndex = 0; windowIndex < stft.size();
         windowIndex++) {
      // Calculate magnitude of the bin
      magnitudes[windowIndex][freqIndex] =
          std::abs(stft[windowIndex][freqIndex]);
      // Calculate phase of bin
      phase = std::arg(stft[windowIndex][freqIndex]);

      // Calculate phase difference between current window and previous window
      phaseDiff = phase - previousPhase[freqIndex];
      previousPhase[freqIndex] = phase;

      // Calculate the expected phase difference based on the overlap between
      // windows
      expectedDiff = ((double)freqIndex) * M_2_PI * ((double)windowStride) /
                     ((double)bufferLen);

      // Correct phaseDiff by accounting for expectedDiff
      phaseDiff -= expectedDiff;

      // Map phase difference into [-pi, pi] interval
      phaseDiff = constrainAngle(phaseDiff);

      // Calculate actual frequency based on phaseDiff
      actualFreqs[windowIndex][freqIndex] =
          freqIndex * freqPerBin +
          phaseDiff * ((double)overlapFactor) * freqPerBin / (2 * M_PI);
    }
  }
}


/**
 * Maps an angle in radians to the interval [-pi, pi]
 */
double constrainAngle(double angle) {
  angle = fmod(angle, 2 * M_PI);
  if (angle > M_PI) {
    angle -= 2 * M_PI;
  }
  if (angle < - M_PI) {
    angle += 2 * M_PI;
  }
  return angle;
}
