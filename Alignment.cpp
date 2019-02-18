#include <iostream>
#include "Alignment.h"

using namespace std;

// Enum to keep track of our backtrace directions for our backtrace
enum directions { downbtr, leftbtr, alignbtr};

int getIndexOfDNA(char DNA) {
    if (DNA == '-') {
        return 0;
    } else if (DNA == 'A') {
        return 1;
    } else if (DNA == 'T') {
        return 2;
    } else if (DNA == 'G') {
        return 3;
    } else if (DNA == 'C') {
        return 4;
    }
}

Result alignDNA(string firstSequence, string secondSequence, const int (&costs)[costDim - 1][costDim - 1]) {
    int distances[firstSequence.length()][secondSequence.length()] = {{0}};
    int backTrace[firstSequence.length()][secondSequence.length()] = {{0}};
    
    // cout << "First test: \n";
    
    // for (int i = 0; i < firstSequence.length(); i++) {
    //     for (int j = 0; j < secondSequence.length(); j++) {
    //         cout << distances[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    // Setup backTrace
    for (int i = 1; i < firstSequence.length(); i++) {
        backTrace[i][0] = downbtr;
    }
    for (int j = 1; j < secondSequence.length(); j++) {
        distances[0][j] = leftbtr;
    }


    // Compute base cases
    distances[0][0] = costs[0][0];
    for (int i = 1; i < firstSequence.length(); i++) {
        distances[i][0] = distances[i-1][0] + costs[0][getIndexOfDNA(firstSequence.at(i))];
    }
    for (int j = 1; j < secondSequence.length(); j++) {
        distances[0][j] = distances[0][j-1] + costs[0][getIndexOfDNA(secondSequence.at(j))];
    }

    // cout << "\n\nSecond test: \n";

    // for (int i = 0; i < firstSequence.length(); i++) {
    //     for (int j = 0; j < secondSequence.length(); j++) {
    //         cout << distances[i][j] << " ";
    //     }
    //     cout << "\n";
    // }


    for (int i = 1; i < firstSequence.length(); i++) {
        for (int j = 1; j < secondSequence.length(); j++) {
            // Compute the minimum edit distance, there are three options: 

            // Option one: pair up the i'th character in the first sequence with '-'
            // This results in us adding the cost of the i'th character with '-'
            int downDistance = distances[i-1][j] + costs[0][getIndexOfDNA(firstSequence.at(i))];
            // Option two: pair up the j'th character in the second sequence with '-'
            int leftDistance = distances[i][j-1] + costs[0][getIndexOfDNA(secondSequence.at(j))];

            // Option three: pair up the i'th character with the j'th character
            int DandLDistance = distances[i-1][j-1] + costs[getIndexOfDNA(firstSequence.at(i))][getIndexOfDNA(secondSequence.at(j))];

            int minDistance = min(min(downDistance, leftDistance), DandLDistance);

            distances[i][j] = minDistance;

            // Backtrace which option we took, so we can reconstruct our string
            // I'm not going to worry about multiple possibilities for answers
            if (minDistance == downDistance) {
                backTrace[i][j] = downbtr;
            } else if (minDistance == leftDistance) {
                backTrace[i][j] = leftbtr;
            } else if (minDistance == DandLDistance) {
                backTrace[i][j] = alignbtr;
            }
        }
    }

    
    // cout << "\n\nThird Test: \n";


    // for (int i = 0; i < firstSequence.length(); i++) {
    //     for (int j = 0; j < secondSequence.length(); j++) {
    //         cout << distances[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    // Compute the backtrace, to get our final string!
    string finalString = "";

    Result optimalResult = {finalString, distances[firstSequence.length()][secondSequence.length()]};

    return optimalResult;

}