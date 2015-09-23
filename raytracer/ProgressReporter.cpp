#include "ProgressReporter.h"
#include <iostream>
#include <math.h>
#include <sstream>

void ProgressReporter::handleProgress(unsigned x, unsigned y) {
    unsigned index = y * width + x;
    unsigned percents = index * 100 / total;
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

    if (index == total - 1) {
        std::cout << std::endl << "done!";
    }
}
