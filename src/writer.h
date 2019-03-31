// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#ifndef WRITER_H_
#define WRITER_H_

#include <string>
#include <sndfile.h>

/**
 * A class which writes to a .wav file from a buffer.
 */

class Writer {
public:

  /**
   * Constructor
   * Note: pass the SF_INFO struct from the input file using the getsfinfo()
   *     method
   */
  Writer(std::string filename, double *buffer, std::size_t bufferLen,
         SF_INFO &sfinfo);

  /**
   * Opens the file for writing
   * Returns true on success
   */
  bool open();

  /**
   * Writes data from buffer into file.
   * @param writeCount The number of samples to write
   * Returns number of items written
   */
  int write(std::size_t writeCount);

  /**
   * Closes the file
   */
  void close();

private:
  double *buffer;
  std::size_t bufferLen;
  std::string filename;

  SNDFILE *file;
  SF_INFO &sfinfo;
};

#endif
