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

#include <iostream> // TODO remove

void processBuffer(double *buffer, std::size_t bufferLen, int channels,
                  std::string mode, std::string option) {
  int k, chan;

  // Construct a valarray of complex numbers from the input buffer
  CVector bufferVector;
  int sampleRate = 44100;
  bufferVector.resize(bufferLen);

  for (chan = 0; chan < channels; chan++) {
    for (k = chan; k < bufferLen; k += channels) {
      // Convert each value in the buffer into a complex number
      bufferVector[k] = CNum(buffer[k], 0);
    }
  }

  // SFTF the buffer
  std::size_t windowSize = 256;
  std::size_t overlapFactor = 16;
  std::vector<CVector> stft = SFTF(bufferVector, windowSize, overlapFactor);

if( mode == "tune"){
    // std::cout << "Tuning..." << std::endl;

    int key = stringToNote.at(option);

    // Calculate the fundamental frequency
    double fund = fundamental(bufferVector, sampleRate);
    // Calculate the target freqency and scale factor
    double target = getTargetFreq(fund, key);
    double pitchScaleFactor = target / fund;

    processSTFT(stft, windowSize, overlapFactor, pitchScaleFactor);

} else if (mode == "scale"){
    // std::cout << "Scaling..." << std::endl;

    double scale = std::stod(option);
    processSTFT(stft, windowSize, overlapFactor, scale);

} else if (mode == "lpf"){
    // std::cout << "Low Pass Filter..." << std::endl;

    double cutoff = std::stod(option);
    // Apply low pass filter to reduce noise
    CVector lpf = lowPassTransferFunction(cutoff, bufferLen, sampleRate);
    for (auto &freqSignal : stft) {
      freqSignal *= lpf;
    }

}else if (mode == "hpf"){
    // std::cout << "High Pass Filter..." << std::endl;
    double cutoff = std::stod(option);
    // Apply high pass filter to reduce noise
    CVector hpf = highPassTransferFunction(cutoff, bufferLen, sampleRate);
    for (auto &freqSignal : stft) {
      freqSignal *= hpf;
    }
}

  // Inverse STFT
  bufferVector = ISFTF(stft, windowSize, overlapFactor);
  // Compensates for increase in amplitude do to overlapping windows
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

  //TODO REMOVE
  // std::cout << "fund: " << fund << std::endl;
  // std::cout << "target: " << target << std::endl;
  // std::cout << "scale: " << pitchScaleFactor << std::endl;
  // std::cout << std::endl;

  // Taper the edges of the buffer
  //CVector window = createWindow(bufferLen, bufferLen / 2, bufferLen);
  //bufferVector *= window;
