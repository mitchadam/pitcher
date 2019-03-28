#include <cstring> // std::memset()

#include "reader.h"

Reader::Reader(std::string filename, double* buffer, std::size_t bufferLen) {
  this->filename = filename;
  this->buffer = buffer;
  this->bufferLen = bufferLen;

  // Initialize sfinfo struct
  std::memset(&sfinfo, 0, sizeof(sfinfo)) ;
}

bool Reader::open() {
  file = sf_open(filename.c_str(), SFM_READ, &sfinfo);

  if (!file) {
    // sf_open failed (returned nullptr)
    return false;
  }

  return true;
}

SF_INFO &Reader::getsfinfo() {
  return sfinfo;
}

/**
 * Reads the next chunk of data from the file into the buffer
 * Returns number of items read into buffer. If this is zero, you have reached
 * the end of the file.
 */
int Reader::read() {
  return sf_readf_double(file, buffer, bufferLen);
}

void Reader::close() {
  sf_close(file);
}
