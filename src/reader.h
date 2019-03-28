// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#ifndef READER_H_
#define READER_H_

#include <string>
#include <sndfile.h>

/**
 * A class which repeatedly reads a .wav file into a buffer.
 */

class Reader {
public:
  Reader(std::string filename, double* buffer, std::size_t bufferLen);
  bool open();
  int read();
  void close();
  SF_INFO& getsfinfo(); 

private:
  double *buffer;
  std::size_t bufferLen;
  std::string filename;

  SNDFILE *file;
  SF_INFO sfinfo;
};

#endif
