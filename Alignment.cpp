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

Result_t alignDNA(string firstSequence, string secondSequence, const int (&costs)[costDim - 1][costDim - 1]) {
    int distances[firstSequence.length()][secondSequence.length()] = {{0}};
    int backTrace[firstSequence.length()][secondSequence.length()] = {{0}};
    Result_t optimalResult;
        
    // for (int i = 0; i < costDim - 1; i++) {
    //     for (int j = 0; j < costDim - 1; j++) {
    //         cout << costs[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    // Setup backTrace
    for (int i = 1; i < firstSequence.length(); i++) {
        backTrace[i][0] = downbtr;
    }
    for (int j = 1; j < secondSequence.length(); j++) {
        backTrace[0][j] = leftbtr;
    }


    // Compute base cases
    distances[0][0] = costs[getIndexOfDNA(firstSequence.at(0))][getIndexOfDNA(firstSequence.at(0))];
    for (int i = 1; i < firstSequence.length(); i++) {
        distances[i][0] = distances[i-1][0] + costs[0][getIndexOfDNA(firstSequence.at(i))];
    }
    for (int j = 1; j < secondSequence.length(); j++) {
        distances[0][j] = distances[0][j-1] + costs[0][getIndexOfDNA(secondSequence.at(j))];
    }

    // cout << "\nSecond Test: \n";

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
            int leftDistance = distances[i][j-1] + costs[getIndexOfDNA(secondSequence.at(j))][0];

            // Option three: pair up the i'th character with the j'th character
            int DandLDistance = distances[i-1][j-1] + costs[getIndexOfDNA(firstSequence.at(i))][getIndexOfDNA(secondSequence.at(j))];

            // cout << "Minumum of " << downDistance << ", " << leftDistance << ", and " << DandLDistance << " is: " << min(min(downDistance, leftDistance), DandLDistance) << "\n";
            int minDistance = min(min(downDistance, leftDistance), DandLDistance);

            distances[i][j] = minDistance;

            // Backtrace which option we took, so we can reconstruct our string
            // I'm not going to worry about multiple possibilities for answers
            if (minDistance == downDistance) {
                backTrace[i][j] = downbtr;
            } 
            if (minDistance == leftDistance) {
                backTrace[i][j] = leftbtr;
            }
            if (minDistance == DandLDistance) {
                backTrace[i][j] = alignbtr;
            }
        }
    }

    cout << "\nThird Test: \n";

    for (int i = 0; i < firstSequence.length(); i++) {
        for (int j = 0; j < secondSequence.length(); j++) {
            cout << distances[i][j] << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < firstSequence.length(); i++) {
        for (int j = 0; j < secondSequence.length(); j++) {
            cout << backTrace[i][j] << " ";
        }
        cout << "\n";
    }
    
    // Store the optimal edit distance in our result
    optimalResult.editDistance = distances[firstSequence.length()-1][secondSequence.length()-1];

    // Compute the backtrace, to get our final string!
    int i = firstSequence.length() - 1;
    int j = secondSequence.length() - 1;
    while (i >= 0 && i >= 0) {
        // cout << "i: " << i << ", j: " << j << "\n";

        if (backTrace[i][j] == downbtr) {
            // Put an empty space in j
            secondSequence.insert(j+1, "-");
            i--; 
            
        } else if (backTrace[i][j] == leftbtr) {
            // Put an empty space in i
            firstSequence.insert(i+1, "-");
            j--; 

        } else if (backTrace[i][j] == alignbtr) {
            // These characters are OK lined up
            i--; 
            j--;
        }
    }

    // Finalize our string and save it in our result
    firstSequence.append("," + secondSequence);
    optimalResult.finalString = firstSequence;

    // cout << "tests\n";

    return optimalResult;

}