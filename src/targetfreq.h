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
 * All possible major keys
 */
enum Key {
  C,
  Db,
  D,
  Eb,
  E,
  F,
  Gb,
  G,
  Ab,
  A,
  Bb,
  B,
};

/**
 * Mappings from each key to which semitones relative to C are acceptable
 */
static const std::unordered_map<Key, std::unordered_set<int>> keyToSemitones{
    {C, {note_c, note_d, note_e, note_f, note_g, note_a, note_b}},
    {Db, {note_db, note_eb, note_f, note_gb, note_ab, note_bb, note_c}},
    {D, {note_d, note_e, note_gb, note_g, note_a, note_b, note_db}},
    {Eb, {note_eb, note_f, note_g, note_ab, note_bb, note_c, note_d}},
    {E, {note_e, note_gb, note_ab, note_a, note_b, note_db, note_eb}},
    {F, {note_f, note_g, note_a, note_bb, note_c, note_d, note_e}},
    {Gb, {note_gb, note_ab, note_bb, note_b, note_db, note_eb, note_f}},
    {G, {note_g, note_a, note_b, note_c, note_d, note_e, note_gb}},
    {Ab, {note_ab, note_bb, note_c, note_db, note_eb, note_f, note_g}},
    {A, {note_a, note_b, note_db, note_d, note_e, note_gb, note_ab}},
    {Bb, {note_bb, note_c, note_d, note_eb, note_f, note_g, note_a}},
    {B, {note_b, note_db, note_eb, note_e, note_gb, note_ab, note_bb}},
};

/**
 * Maps string to a Key enum type.
 * Used to parse command line args.
 */
static const std::unordered_map<std::string, Key> stringToKey {
  {"c", C,},
  {"db", Db},
  {"d", D},
  {"eb", Eb},
  {"e", E},
  {"f", F},
  {"gb", Gb},
  {"g", G},
  {"ab", Ab},
  {"a", A},
  {"bb", Bb},
  {"b", B},
};

/**
 * Calculates nearest frequency that corresponds to a note in the key
 */
double getTargetFreq(double actualFreq, Key key);

#endif
