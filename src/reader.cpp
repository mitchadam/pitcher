// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

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

int Reader::read() {
  return sf_read_double(file, buffer, bufferLen);
}

void Reader::close() {
  sf_close(file);
}
