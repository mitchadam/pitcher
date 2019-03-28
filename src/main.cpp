// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include <iostream>

#include "reader.h"
#include "writer.h"
#include "fourier.h"
#include "fundamental.h"
#include <valarray>
#include <complex>
#include <iostream>

constexpr std::size_t bufferLen = 32768;

static void process_data (double *data, int count, int channels) ;

int main() {
  double *buffer = new double[bufferLen];
  Reader reader("piano-c4.wav", buffer, bufferLen);
  if (!reader.open()) {
    std::cout << "Failed to open file." << std::endl;
    return 1;
  }
  // Need to pass the SF_INFO struct from the reader to the writer
  Writer writer("output.wav", buffer, bufferLen, reader.getsfinfo());
  writer.open();

  int readCount;

  reader.close();
  writer.close();
}


// Copied from example on libsndfile github
static void process_data(double *data, int count, int channels) {
  //double channel_gain[] = {0.5, 0.8, 0.1, 0.4, 0.4, 0.9};
  int k, chan;

  /* Process the data here.
  ** If the soundfile contains more then 1 channel you need to take care of
  ** the data interleaving youself.
  ** Current we just apply a channel dependant gain.
  */

  // Construct a valarray of complex numbers from the input buffer
  CVector bufferVector;
  bufferVector.resize(bufferLen);

  for (chan = 0; chan < channels; chan++) {
    for (k = chan; k < count; k += channels) {
      //data[k] *= channel_gain[chan];

      // Convert each value in the buffer into a complex number
      bufferVector[k] = CNum(data[k], 0);
    }
  }

  // Calculate the fundamental frequency
  double fund = fundamental(bufferVector, 44100);
  std::cout << fund << std::endl;

  return;
} /* process_data */
