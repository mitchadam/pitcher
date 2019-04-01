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

  /**
   * Opens the file.
   * Returns true on success.
   */
  bool open();

  /**
   * Reads the next chunk of data from the file into the buffer
   * Returns number of items read into buffer. If this is zero, you have reached
   * the end of the file.
   */
  int read();

  /**
   * Moves the file pointer by offset. Offset can be negative.
   * Returns offset from the start of the file or -1 on failure.
   */
  int seek(int offset);

  /**
   * Returns true if the file pointer is at the end of the file.
   */
  bool atEnd();

  /**
   * Closes the file
   */
  void close();

  /**
   * Get SF_INFO struct that is generated on opening the file.
   * libsndfile uses this struct to keep track of number of channels and other
   * parameters
   */
  SF_INFO& getsfinfo(); 

private:
  double *buffer;
  std::size_t bufferLen;
  std::string filename;

  SNDFILE *file;
  SF_INFO sfinfo;
};

#endif
