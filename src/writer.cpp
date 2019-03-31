// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#include <cstring> // std::memset()

#include "writer.h"

Writer::Writer(std::string filename, double *buffer, std::size_t bufferLen,
               SF_INFO &sfinfo) : sfinfo(sfinfo) {
  this->filename = filename;
  this->buffer = buffer;
  this->bufferLen = bufferLen;
}

bool Writer::open() {
  file = sf_open(filename.c_str(), SFM_WRITE, &sfinfo);

  if (!file) {
    // sf_open failed (returned nullptr)
    return false;
  }

  return true;
}

int Writer::write(std::size_t writeCount) {
  return sf_write_double(file, buffer, writeCount);
}

void Writer::close() {
  sf_close(file);
}
