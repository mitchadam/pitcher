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

static void process_data (double *data, int count, int channels) ;

int main() {
  std::size_t bufferLen = 1024;
  double *buffer = new double[bufferLen];
  Reader reader("violin.wav", buffer, bufferLen);
  reader.open();
  // Need to pass the SF_INFO struct from the reader to the writer
  Writer writer("output.wav", buffer, bufferLen, reader.getsfinfo());
  writer.open();

  int readCount;
  // Continue to read while we have not reached the end of the input file
  while ((readCount = reader.read())) {
    process_data(buffer, readCount, reader.getsfinfo().channels);
    writer.write();
  };

  reader.close();
  writer.close();
}


// Copied from example on libsndfile github
static void process_data(double *data, int count, int channels) {
  double channel_gain[] = {0.5, 0.8, 0.1, 0.4, 0.4, 0.9};
  int k, chan;

  /* Process the data here.
  ** If the soundfile contains more then 1 channel you need to take care of
  ** the data interleaving youself.
  ** Current we just apply a channel dependant gain.
  */

  for (chan = 0; chan < channels; chan++)
    for (k = chan; k < count; k += channels)
      data[k] *= channel_gain[chan];

  return;
} /* process_data */
