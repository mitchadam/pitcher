// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include <cmath>

#include "targetfreq.h"

double getTargetFreq(double actualFreq, int key) {
  // Frequency in Hz of A4
  double A4 = 440;
  // Frequency in Hz of C0
  double C0 = A4 * pow(2, -4.75);

  // Calculate semitones away from C0 using a logarithmic scale
  double semitonesFromC0 = 12 * log2(actualFreq / C0);
  // Calculate octave for later
  int octave = static_cast<int>(semitonesFromC0) / 12;
  // Map to one octave
  double semitonesModded = std::fmod(semitonesFromC0, 12);
  // Round to nearest integer semitone
  double semitonesRounded = std::round(semitonesModded);
  bool roundedUp = true;
  if (semitonesRounded < semitonesModded) {
    roundedUp = false;
  }
  // Cast to int for purposes of querying a map
  int semitone = static_cast<int>(semitonesRounded);

  /// Decide whether semitone of signal is in the key
  int targetSemitone;
  // Set of all semitones that are in the key
  std::unordered_set<int> keySet = keyToSemitones.at(key);
  // If the semitone is in the key, use it
  // If not, move one semitone over, depending on whether we rounded up or down
  if (keySet.find(semitone) == keySet.end()) {
    // Note is not in key
    if (roundedUp) {
      targetSemitone = semitone - 1;
    } else {
      targetSemitone = semitone + 1;
    }
  } else {
    targetSemitone = semitone;
  }

  // Ensure targetSemitone is in range [0, 11]
  if (targetSemitone < 0) {
    targetSemitone += 12;
  }
  targetSemitone %= 12;

  // The closest semitone might be in the octave below or above
  if (targetSemitone - semitone > 2) {
    targetSemitone -= 12;
  } else if (semitone - targetSemitone > 2) {
    targetSemitone += 12;
  }
  // Convert from semitone to frequency on Hz
  double target = static_cast<double>(targetSemitone + octave * 12);
  target = C0 * pow(2, target / 12);
  return target;
}
