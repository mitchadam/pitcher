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

constexpr std::size_t bufferLen = 32768;

int main() {
  double *buffer = new double[bufferLen];
  Reader reader("piano-c4.wav", buffer, bufferLen);
  if (!reader.open()) {
    std::cout << "Failed to open file." << std::endl;
    return 1;
  }
  // Need to pass the SF_INFO struct from the reader to the writer
  Writer writer("output.wav", buffer, bufferLen, reader.getsfinfo());
  writer.open();

  int readCount;
  while ((readCount = reader.read())) {
    processBuffer(buffer, bufferLen, reader.getsfinfo().channels);
    writer.write();
  }

  reader.close();
  writer.close();

  CVector varr = {{10,0}, {2,0}, {20,0}, {1,0} };
  std::cout <<"Inital: "<< std::endl;

  for(int i =0; i < varr.size(); i++){
      std::cout << varr[i]<< " ";
  }
  std::cout << std::endl;
  FFT(varr);
  std::cout <<"FFT: "<< std::endl;

  for(int i =0; i < varr.size(); i++){
      std::cout << varr[i]<< " ";
  }
  std::cout << std::endl;
  applyIFFT(varr);
  std::cout <<"IFFT: "<< std::endl;
  for(int i =0; i < varr.size(); i++){
      std::cout << varr[i]<< " ";
  }
  std::cout << std::endl;
  CVector tester;
  tester.resize(4096,100);
  std::vector<CVector> test = SFTF(tester);
}
