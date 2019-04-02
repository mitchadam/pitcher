// -------------------------------------------------
// Name: Mitchell Adam, Ryan Shukla
// ID: 1528592, 1537980
// CMPUT 275, Winter 2018
//
// Final Project
// -------------------------------------------------

#ifndef _TARGET_FREQ_H_
#define _TARGET_FREQ_H_

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "fourier.h"

/**
 * This file contains utilities to work with musical notes
 */

/**
 * Notes expressed as semitones above C
 */
constexpr int note_c = 0;
constexpr int note_db = 1;
constexpr int note_d = 2;
constexpr int note_eb = 3;
constexpr int note_e = 4;
constexpr int note_f = 5;
constexpr int note_gb = 6;
constexpr int note_g = 7;
constexpr int note_ab = 8;
constexpr int note_a = 9;
constexpr int note_bb = 10;
constexpr int note_b = 11;

/**
 * Mappings from each key to which semitones relative to C are acceptable
 * Note: adding the octave (e.g. note_c + 12) makes it easier to calculate the
 * target frequency in getTargetFreq
 */
static const std::unordered_map<int, std::unordered_set<int>> keyToSemitones{
  {note_c, {note_c, note_d, note_e, note_f, note_g, note_a, note_b, note_c + 12}},
  {note_db, {note_db, note_eb, note_f, note_gb, note_ab, note_bb, note_c, note_db + 12}},
  {note_d, {note_d, note_e, note_gb, note_g, note_a, note_b, note_db, note_d + 12}},
  {note_eb, {note_eb, note_f, note_g, note_ab, note_bb, note_c, note_d, note_eb + 12}},
  {note_e, {note_e, note_gb, note_ab, note_a, note_b, note_db, note_eb, note_e + 12}},
  {note_f, {note_f, note_g, note_a, note_bb, note_c, note_d, note_e, note_f + 12}},
  {note_gb, {note_gb, note_ab, note_bb, note_b, note_db, note_eb, note_f, note_gb + 12}},
  {note_g, {note_g, note_a, note_b, note_c, note_d, note_e, note_gb, note_g + 12}},
  {note_ab, {note_ab, note_bb, note_c, note_db, note_eb, note_f, note_g, note_ab + 12}},
  {note_a, {note_a, note_b, note_db, note_d, note_e, note_gb, note_ab, note_a + 12}},
  {note_bb, {note_bb, note_c, note_d, note_eb, note_f, note_g, note_a, note_bb + 12}},
  {note_b, {note_b, note_db, note_eb, note_e, note_gb, note_ab, note_bb, note_b + 12}},
};

/**
 * Maps string to a note as an int (see constants above)
 * Used to parse command line args.
 */
static const std::unordered_map<std::string, int> stringToNote {
  {"c", note_c,},
  {"db", note_db},
  {"d", note_d},
  {"eb", note_eb},
  {"e", note_e},
  {"f", note_f},
  {"gb", note_gb},
  {"g", note_g},
  {"ab", note_ab},
  {"a", note_a},
  {"bb", note_bb},
  {"b", note_b},
};

/**
 * Calculates nearest frequency that corresponds to a note in the key
 * @param actualFreq The frequency of the signal (can be estimated using
 *     fundamental())
 * @param key The desired key in which to search for the closest acceptable note
 */
double getTargetFreq(double actualFreq, int key);

#endif
