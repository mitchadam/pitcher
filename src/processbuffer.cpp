// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include "processbuffer.h"
#include "processstft.h"
#include "filter.h"
#include "targetfreq.h"

void processBuffer(double *inputBuffer, std::size_t inputBufferLen,
                   double *outputBuffer, std::size_t outputBufferLen,
                   int channels, std::string mode, std::string option) {
  int k, chan;

  // Construct a valarray of complex numbers from the input buffer
  CVector bufferVector;
  int sampleRate = 44100;
  bufferVector.resize(inputBufferLen);

  for (chan = 0; chan < channels; chan++) {
    for (k = chan; k < inputBufferLen; k += channels) {
      // Convert each value in the buffer into a complex number
      bufferVector[k] = CNum(inputBuffer[k], 0);
    }
  }

  // SFTF the buffer
  std::size_t windowSize = 256;
  std::size_t overlapFactor = 16;
  std::vector<CVector> stft = SFTF(bufferVector, windowSize, overlapFactor);

  if (mode == "tune") {
    int key = stringToNote.at(option);

    // Calculate the fundamental frequency
    double fund = fundamental(bufferVector, sampleRate);
    // Calculate the target freqency and scale factor
    double target = getTargetFreq(fund, key);
    double pitchScaleFactor = target / fund;

    processSTFT(stft, windowSize, overlapFactor, pitchScaleFactor);

  } else if (mode == "scale") {

    double scale = std::stod(option);
    processSTFT(stft, windowSize, overlapFactor, scale);

  } else if (mode == "lpf") {

    double cutoff = std::stod(option);
    // Apply low pass filter to reduce noise
    CVector lpf = lowPassTransferFunction(cutoff, inputBufferLen, sampleRate);
    for (auto &freqSignal : stft) {
      freqSignal *= lpf;
    }

  } else if (mode == "hpf") {
    double cutoff = std::stod(option);
    // Apply high pass filter to reduce noise
    CVector hpf = highPassTransferFunction(cutoff, inputBufferLen, sampleRate);
    // Increase "strength" of hpf
    for (auto &num : hpf) {
      num = std::pow(num, 100);
    }
    for (auto &freqSignal : stft) {
      freqSignal *= hpf;
    }
  }

  // Inverse STFT
  bufferVector = ISFTF(stft, windowSize, overlapFactor);

  // Window the entire processed buffer so that it can be crossfaded
  CVector crossfadeWindow = createWindow(inputBufferLen, inputBufferLen / 2,
                                         inputBufferLen);
  bufferVector *= crossfadeWindow;

  // Compensates for increase in amplitude do to overlapping windows
  double gain = 0.25;
  // Covert CVector back into array of doubles
  for (chan = 0; chan < channels; chan++) {
    for (k = chan; k < inputBufferLen; k += channels) {
      // Convert each value in the buffer into a complex number
      // Add to the last 2/3 of the output buffer
      if (k + inputBufferLen / 2 < outputBufferLen) {
        outputBuffer[k + inputBufferLen / 2] += bufferVector[k].real() * gain;
      }
    }
  }
  return;
}
