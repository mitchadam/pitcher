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
#include "processbuffer.h"
#include <valarray>
#include <complex>
#include <iostream>

constexpr std::size_t bufferLen = 1024;

int main(int argc, char *argv[]) {
  // Parse command line args
  std::string mode;
  std::string optionSelect;
  std::string inputFileName;
  if (argc == 4) {
    mode = argv[1];
    optionSelect = argv[2];
    inputFileName = argv[3];
  }
  else {
    std::cout << "Usage: pitcher [mode] [options] [file]" << std::endl;
    return 1;
  }

  // Allocate buffer to read sound file into
  double *buffer = new double[bufferLen];
  Reader reader(inputFileName, buffer, bufferLen);
  if (!reader.open()) {
    std::cout << "Error: Failed to open file." << std::endl;
    return 1;
  }
  // Need to pass the SF_INFO struct from the reader to the writer
  Writer writer("output.wav", buffer, bufferLen, reader.getsfinfo());
  writer.open();

  int readCount;
  int writeCount;
  while ((readCount = reader.read())) {
    processBuffer(buffer, bufferLen, reader.getsfinfo().channels, mode, optionSelect);
    writeCount = writer.write(readCount);
  }

  reader.close();
  writer.close();
}
