// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include <cmath> // M_PI, fmod()

#include "processstft.h"

// Forward declaration
double constrainAngle(double angle);

/**
 * @param windowSize The size of a window in the stft
 * @param overlapFactor Amount of overlap between windows
 *   e.g. If the next window starts 1/4 of the way into the current window,
 *   then overlapFactor = 4
 */
void processSTFT(std::vector<CVector> &stft, std::size_t windowSize,
                 std::size_t overlapFactor, double pitchScaleFactor) {

  // TODO don't hard code
  double sampleRate = 44100;

  // Length of the buffer in samples (time domain length is same as freq domain
  // length)
  std::size_t bufferLen = stft[0].size();

  // frequency of bin 1
  double freqPerBin = sampleRate / ((double)bufferLen);

  // Number of windows in the stft
  std::size_t windowCount = stft.size();

  // Number of samples between start of a window and the next window
  // TODO account for edges
  std::size_t windowStride = bufferLen / windowCount;


  // Ensure actualFreqs and magnitudes vectors have correct size
  // Outer index is window, inner is freqency bin
  std::vector< std::vector<double> > actualFreqs;
  actualFreqs.resize(windowCount);
  for (std::size_t i = 0; i < windowCount; i++) {
    actualFreqs[i].resize(bufferLen);
  }
  std::vector< std::vector<double> > magnitudes;
  magnitudes.resize(windowCount);
  for (std::size_t i = 0; i < windowCount; i++) {
    magnitudes[i].resize(bufferLen);
  }

  // Store previous previous of each bin as we loop through windows
  std::vector<double> previousPhase;
  // TODO what to initialize previous to?
  previousPhase.resize(bufferLen, 0);

  // Loop across frequency bins
  for (std::size_t freqIndex = 0; freqIndex < bufferLen; freqIndex++) {
    // Loop across stft windows
    for (std::size_t windowIndex = 0; windowIndex < windowCount;
         windowIndex++) {

      // Calculate magnitude of the bin
      magnitudes[windowIndex][freqIndex] =
          std::abs(stft[windowIndex][freqIndex]);

      // Calculate phase of bin
      double phase = std::arg(stft[windowIndex][freqIndex]);

      // Calculate phase difference between current window and previous window
      double phaseDiff = phase - previousPhase[freqIndex];
      previousPhase[freqIndex] = phase;

      // Calculate the expected phase difference based on the overlap between
      // windows
      double expectedDiff = ((double)freqIndex) * 2 * M_PI *
                            ((double)windowStride) / ((double)bufferLen);

      // Correct phaseDiff by accounting for expectedDiff
      phaseDiff -= expectedDiff;

      // Map phase difference into [-pi, pi] interval
      phaseDiff = constrainAngle(phaseDiff);

      // Calculate actual frequency based on phaseDiff
      actualFreqs[windowIndex][freqIndex] =
          ((double)freqIndex) * freqPerBin +
          phaseDiff * ((double)overlapFactor) * freqPerBin / (2 * M_PI);
    }
  }

  // DO PITCH SHIFTING HERE
  // Do resampling to shift pitch
  // Simply move magnitudes to new indeces
  // Move AND scale actual frequencies

  // Update the stft representation based on the new magnitudes and frequencies
  // - Convert actual frequencies back to array of phases
  // - Use phase and magnitudes to calculate re and im parts

  // Since we calculate a change in phase between windows, we need to keep track
  // of the phase at the previous window
  std::vector<double> phaseAccum;
  // TODO what to initialize this to?
  phaseAccum.resize(bufferLen, 0);

  // Loop across frequency bins
  for (std::size_t freqIndex = 0; freqIndex < bufferLen; freqIndex++) {
    // Loop across stft windows
    for (std::size_t windowIndex = 0; windowIndex < stft.size();
         windowIndex++) {
      // Subtract ideal bin frequency to get change in frequency
      double deltaFreq = actualFreqs[windowIndex][freqIndex] -
                         ((double)freqIndex) * freqPerBin;

      // Convert change in frequency to actual change in phase
      double deltaPhase = deltaFreq * 2 * M_PI;
      deltaPhase /= overlapFactor;
      deltaPhase /= freqPerBin;

      // Convert actual change in phase back to measured change in phase
      // by adding the expected change in phase
      deltaPhase += ((double)freqIndex) * 2 * M_PI * ((double)windowStride) /
                    ((double)bufferLen);

      // Add the change in phase to the accumulator
      phaseAccum[freqIndex] += deltaPhase;
      double phase = phaseAccum[freqIndex];

      // Calculate real and imaginary parts of stft bin
      double mag = magnitudes[windowIndex][freqIndex];
      stft[windowIndex][freqIndex].real(mag * std::cos(phase));
      stft[windowIndex][freqIndex].imag(mag * std::sin(phase));
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
