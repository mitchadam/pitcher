#ifndef WRITER_H_
#define WRITER_H_

#include <string>
#include <sndfile.h>

/**
 * A class which writes to a .wav file from a buffer.
 */

class Writer {
public:
  Writer(std::string filename, double *buffer, std::size_t bufferLen,
         SF_INFO &sfinfo);
  bool open();
  int write();
  void close();

private:
  double *buffer;
  std::size_t bufferLen;
  std::string filename;

  SNDFILE *file;
  SF_INFO &sfinfo;
};

#endif
