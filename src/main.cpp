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
#include "targetfreq.h" // Key type
#include <valarray>
#include <complex>
#include <iostream>

constexpr std::size_t bufferLen = 4096;

int main(int argc, char *argv[]) {
  // Parse command line args
  std::string inputFileName;
  std::string keyString;
  if (argc == 3) {
    inputFileName = argv[1];
    keyString = argv[2];
  }
  else {
    std::cout << "Usage: pitcher [filename] [key]" << std::endl;
    return 1;
  }

  // Map command line arg to a Key enum type
  if (stringToKey.find(keyString) == stringToKey.end()) {
    std::cout << "Error: unrecognized key." << std::endl;
    return 1;
  }
  Key key = stringToKey.at(keyString);

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
    processBuffer(buffer, bufferLen, reader.getsfinfo().channels, key);
    writeCount = writer.write(readCount);
  }

  reader.close();
  writer.close();

  /*
  CVector varr = {{0, 0}, {0, 0}, {0, 0},  {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {0, 0},  {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {75, 0}, {75, 0}};
  std::cout << "Inital: " << std::endl;

  for (int i = 0; i < varr.size(); i++) {
    std::cout << varr[i] << " ";
  }
  std::cout << std::endl;
  FFT(varr);
  std::cout << "FFT: " << std::endl;

  for (int i = 0; i < varr.size(); i++) {
    std::cout << varr[i] << " ";
  }
  std::cout << std::endl;
  applyIFFT(varr);
  std::cout << "IFFT: " << std::endl;
  for (int i = 0; i < varr.size(); i++) {
    std::cout << varr[i] << " ";
  }
  std::cout << std::endl;
  CVector tester;
  CVector Sum;
  int size = 32768;
  Sum.resize(size,0);
  int sampleSize = 2048;
  int overlap = 4;
  tester.resize(size,100);
  std::vector<CVector> test = SFTF(tester, sampleSize, overlap);

  // for (size_t i = 0; i < test[0].size(); i++) {
  //     //Loop through the windows
  //     for (size_t j = 0; j < test.size(); j++) {
  //         // Set weach ouput bin as sum of corresponding window bins
  //         Sum[i] += test[j][i];
  //     }
  // }
  // for(int i =0; i <size; i++){
  //     std::cout << Sum[i] << " ";
  // }
  // std::cout << std::endl;
  // std::cout << std::endl;
  // CVector output = ISFTF(test, sampleSize, overlap);
  // for(int i = 0; i < size; i ++){
  //     std::cout << output[i] << " ";
  // }
  // std::cout << std::endl;
  */
}
