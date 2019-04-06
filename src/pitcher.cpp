#include "pitcher.h"

int pitcher(int argc, char *argv[]) {
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
    double *inputBuffer = new double[inputBufferLen];
    std::memset(inputBuffer, 0, inputBufferLen);

    // Allocate buffer to store and crossfade processed sound
    double *outputBuffer = new double[outputBufferLen];
    std::memset(outputBuffer, 0, outputBufferLen);
    double *outputBufferThird = outputBuffer + inputBufferLen / 2;
    double *outputBufferLastThird = outputBuffer + inputBufferLen;

    //Ensure Correct Opening
    Reader reader(inputFileName, inputBuffer, inputBufferLen);
    if (!reader.open()) {
      std::cout << "Error: Failed to open file." << std::endl;
      return 1;
    }

    // Need to pass the SF_INFO struct from the reader to the writer
    // Writer only writes from the first 2/3 of output buffer
    Writer writer("output.wav", outputBuffer, inputBufferLen, reader.getsfinfo());
    writer.open();

    int readCount;
    int writeCount;
    // Since we are processing overlapping sections, we can only write every other
    // iteration of the loop
    bool write = false;
    while ((readCount = reader.read())) {
      processBuffer(inputBuffer, inputBufferLen, outputBuffer, outputBufferLen,
                    reader.getsfinfo().channels, mode, optionSelect);
      if (write) {
          //Handle edge case
        writeCount = writer.write(inputBufferLen);
        write = false;
      } else {
        write = true;
      }
      // Shift output buffer
      std::memmove(outputBuffer, outputBufferThird,
                   inputBufferLen * sizeof(double));
      // Set last third of output buffer to zeros
      std::memset(outputBufferLastThird, 0,
                  (inputBufferLen / 2) * sizeof(double));
      int pos = reader.seek(0);
      if (!(reader.atEnd())) {
        // Move the file pointer backwards so that we can read overlapping
        // sections
        pos = reader.seek(-1 * (((int)inputBufferLen) / 2));
      }
    }

    // Close reader and writer when finished
    reader.close();
    writer.close();
    return 0;
}
