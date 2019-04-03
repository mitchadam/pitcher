#ifndef _PITCHER_H_
#define _PITCHER_H_

#include "reader.h"
#include "writer.h"
#include "processbuffer.h"
#include <valarray>
#include <complex>
#include <cstring>
#include <iostream>

// Used for cross fading the buffers to reduce noise
constexpr std::size_t inputBufferLen = 1024;
constexpr std::size_t outputBufferLen = 1536; // 1.5x inputBufferLen

/*
    Run Pitcher
    @param: argc number of arguments
    @param: *argv[] input arugments

*/
int pitcher(int argc, char *argv[]);

#endif