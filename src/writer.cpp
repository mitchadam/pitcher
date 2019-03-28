#include <cstring> // std::memset()

#include "writer.h"

/**
 * Note: pass the sfinfo struct from the input file
 */
Writer::Writer(std::string filename, double *buffer, std::size_t bufferLen,
               SF_INFO &sfinfo) : sfinfo(sfinfo) {
  this->filename = filename;
  this->buffer = buffer;
  this->bufferLen = bufferLen;

  // Initialize sfinfo struct
  std::memset(&sfinfo, 0, sizeof(sfinfo)) ;
}

bool Writer::open() {
  file = sf_open(filename.c_str(), SFM_WRITE, &sfinfo);

  if (!file) {
    // sf_open failed (returned nullptr)
    return false;
  }

  return true;
}

/**
 * Writes data from buffer into file.
 * Returns number of items written
 */
int Writer::write() {
  return sf_write_double(file, buffer, bufferLen);
}

void Writer::close() {
  sf_close(file);
}
