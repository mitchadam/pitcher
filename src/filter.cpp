// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include "filter.h"

#include <cmath>

CVector lowPassTransferFunction(double cutoff, std::size_t length,
                                int sampleRate) {

  // Angular frequency of bin 1
  double baseBinFreq = 2 * M_PI * ((double)sampleRate) / ((double)length);

  // RC factor of low pass system
  double RC = 2 * M_PI * cutoff;
  RC = 1 / RC;

  CVector output;
  output.resize(length, 0);

  CNum temp;
  for (std::size_t i = 0; i < length; i++) {
    temp = CNum(1, RC * baseBinFreq * ((double)i));
    output[i] = CNum(1, 0) / temp;
  }

  return output;
}

CVector highPassTransferFunction(double cutoff, std::size_t length,
                                 int sampleRate) {

  // Angular frequency of bin 1
  double baseBinFreq = 2 * M_PI * ((double)sampleRate) / ((double)length);

  // RC factor of high pass system
  double RC = 2 * M_PI * cutoff;
  RC = 1 / RC;

  CVector output;
  output.resize(length, 0);

  CNum temp;
  for (std::size_t i = 0; i < length; i++) {
    /*
    temp = CNum(1, RC * baseBinFreq * ((double)i));
    output[i] = CNum(0, RC * baseBinFreq * ((double)i)) / temp;
    */

    /*
    output[i] = CNum(0, RC * ((double)i) * baseBinFreq) /
        CNum(1, RC * ((double)i) * baseBinFreq);
    */

    output[i] = CNum(0, ((double)i) * baseBinFreq) /
        CNum(2 * M_PI * cutoff, ((double)i) * baseBinFreq);

    /*
    output[i] = CNum(0, RC * ((double)i - ((double)length) / 2) * baseBinFreq) /
        CNum(1, RC * ((double)i - ((double)length) / 2) * baseBinFreq);
    */

    /*
    if (std::abs(((double)i - ((double)length) / 2) * baseBinFreq) >
        2 * M_PI * cutoff) {
      output[i] = CNum(1, 0);
    } else {
      output[i] = CNum(0, 0);
    }
    */
  }

  return output;
}
