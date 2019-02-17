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