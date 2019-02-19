#ifndef ALIGN_H
#define ALIGN_H

#include <string>

using namespace std;

// Constant declarations
const int costDim = 6;      // width and height of our cost matrix

struct Result_t {
    string finalString;
    int editDistance;
};

/** 
 * This is a function to transcode our individual DNA characters into an index to be used for our costs matrices
 * Takes in a character ('-', 'A', 'T', 'G', 'C') and turns them into an index 0-4 (in that order)
 **/
int getIndexOfDNA(char DNA);

/**
 * Alignment function
 * 
 * Takes in two strings of DNA sequences (containing 'A', 'T', 'G', 'C'),
 * and aligns them in the optimal way, given the array of costs given
 * 
 * Returns a new string with an aligned pair of the form <string1>,<string2>.
 * Both of the stirngs will be the same length with padding:
 * This new string may also contain '-', indicating an empty space.
 **/
Result_t alignDNA(string firstSequence, string secondSequence, const int (&costs)[costDim - 1][costDim - 1]);

#endif // ALIGN_H