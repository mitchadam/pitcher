// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#ifndef _PROCESS_BUFFER_H_
#define _PROCESS_BUFFER_H_

#include "fourier.h"
#include "fundamental.h"
#include "targetfreq.h"
#include <string>

/**
 * Does all signal processing on buffer.
 * Note: this function modifies buffer
 * @param buffer Pointer to the start of the buffer
 * @param bufferLen Length of the buffer
 * @param channels Number of audio channels in buffer
 * @param mode The operating mode ("lpf", "scale", etc.)
 * @param option The option within the mode (e.g. the scaling factor if the
 *     mode is "scale")
 */
void processBuffer(double *buffer, std::size_t bufferLen, int channels,
                    std::string mode, std::string option);

#endif
