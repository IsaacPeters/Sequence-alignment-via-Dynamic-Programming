#include <iostream>
#include "Alignment.h"

using namespace std;

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

string alignDNA(string firstSequence, string secondSequence, const int (&costs)[costDim - 1][costDim - 1]) {
    int distances[firstSequence.length()][secondSequence.length()] = {{0}};
    cout << "test9\n";

    // Compute base cases
    distances[0][0] = costs[0][0];
    for (int i = 1; i < firstSequence.length(); i++) {
        distances[i][0] = distances[i-1][0] + costs[0][getIndexOfDNA(firstSequence.at(i))];
    }
    cout << "test11\n";
    for (int j = 1; j < secondSequence.length(); j++) {
        
    cout << "test11.5\n";
        distances[j][0] = distances[j-1][0] + costs[0][getIndexOfDNA(secondSequence.at(j))];
    }
    cout << "test12\n";

    for (int i = 1; i < firstSequence.length(); i++) {
        for (int j = 1; j < secondSequence.length(); j++) {
            // Compute the minimum edit distance, there are three options: 
    cout << "test1\n";

            // Option one: pair up the i'th character in the first sequence with '-'
            // This results in us adding the cost of the i'th character with '-'
            int downDistance = distances[i-1][j] + costs[0][getIndexOfDNA(firstSequence.at(i))];
    cout << "test2\n";

            // Option two: pair up the j'th character in the second sequence with '-'
            int leftDistance = distances[i][j-1] + costs[0][getIndexOfDNA(secondSequence.at(j))];
    cout << "test3\n";

            // Option three: pair up the i'th character with the j'th character
            int DandLDistance = distances[i-1][j-1] + costs[getIndexOfDNA(firstSequence.at(i))][getIndexOfDNA(secondSequence.at(j))];
    cout << "test4\n";

            distances[i][j] = min(min(downDistance, leftDistance), DandLDistance);
    cout << "test5\n";
        }
    }
    cout << "test6\n";


    for (int i = 0; i < firstSequence.length(); i++) {
        for (int j = 0; j < secondSequence.length(); j++) {
            cout << distances[i][j] << " ";
        }
        cout << "\n";
    }

    return "nothing";

}