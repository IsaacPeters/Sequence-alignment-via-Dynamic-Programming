//----------------------------------------------------------
// CS260 Assignment Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------
#include <iostream>
#include <fstream>
#include <ctime>

#include "Alignment.h"

using namespace std;

int main()
{
    

    // Start a timer
    clock_t startClock = clock();

    // Get the costs from cost file, only needs to happen once.
    // Will probably pass this off when we call alignment
    
    // Create input file for costs
    ifstream costFile("imp2cost.txt");
    if( !costFile.is_open() ) {
        cout << "Error opening file" << endl;
        return 1;
    }

    // Ignore first line, always holds *,-,A,T,G,C
    costFile.ignore(32, '\n');

    int costs[5][5] = {{0}};

    for (int i = 0; i < costDim - 1; i++) {
        // Ignore the first character, and the comma after it. Will be the title of the row
        costFile.ignore(2, ',');
        for (int j = 0; j < costDim - 1; j++) {
            costFile >> costs[i][j];  // Store the number we're at in the corresponding costs spot
            costFile.ignore(1, '\n');  // Skip the next character, a ','. If we're at the end of the line, stop at the endline (redundant)
        }
    }
    
    // Create input file for our strings
    ifstream inFile("imp2input.txt");
    if( !inFile.is_open() ) {
        cout << "Error opening file" << endl;
        return 1;
    }
    
    // Create output file for our optimized
    ofstream outFile("imp2output.txt");
    if( !inFile.is_open() ) {
        cout << "Error opening file" << endl;
        return 1;
    }
    int i = 0; 
    while (/*!inFile.eof()*/ i < 1) {
        i++;
        // get a line, will be of the form XXXX,XXXX (number of X's unknown). Store it in temp
        string temp;
        inFile >> temp;

        // Get index of the comma, split string of characters in half
        int commaIndex = temp.find(",");    

        // Split string into two parts, before and after the comma
        string firstSequence = temp.substr(0, commaIndex);
        string secondSequence = temp.substr(commaIndex + 1);

        // Take these strings and give them to our alignment function to be aligned...
        // alignedString = alignment(firstSequence, secondSequence);
        Result_t alignment = alignDNA(firstSequence, secondSequence, costs);

        // Store that bad boy in our output file
        outFile << alignment.finalString << ":" << alignment.editDistance << "\n";
    }

    // Find the time we timed :)
    clock_t clockDuration = clock() - startClock;
    double seconds = 1.0 * clockDuration / CLOCKS_PER_SEC;
    cout << "\nIn " << seconds << " seconds, we completed finding the sequence alignment!\n";
}
