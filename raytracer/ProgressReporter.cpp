#include "ProgressReporter.h"
#include <iostream>
#include <math.h>
#include <sstream>

void ProgressReporter::handleProgress(unsigned x, unsigned y) {
    current++;
    unsigned percents = current * 100 / total;
    while (printed < percents) {
        printed++;
        char symbol('.');
        if (printed % 10 == 0) {
            std::stringstream s;
            s << printed / 10;
            symbol = s.str()[0];
        }
        std::cout << symbol << std::flush;
    }

    if (current == total) {
        std::cout << std::endl << "done!" << std::endl;
    }
}
