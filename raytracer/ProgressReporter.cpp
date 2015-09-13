#include "ProgressReporter.h"
#include <iostream>
#include <math.h>

void ProgressReporter::handleProgress(unsigned x, unsigned y)
{
    unsigned index = y * width + x;
    const unsigned int i = index % REPORTS_TO_MERGE;
    if (i == REPORTS_TO_MERGE_MODULO) {
        std::cout << ".";
    }
    if (index % newRowIndex == newRowIndexModulo) {
        std::cout << std::endl;
    }
    if (index == width * height - 1) {
        std::cout << std::endl << "done!";
    }
}

void ProgressReporter::init() {
    unsigned total = width * height;
    unsigned outputsNum = total / REPORTS_TO_MERGE;
    float ratio = height / (float) width;
    float w = sqrtf(outputsNum / ratio);
    newRowIndex = (unsigned) (w * 2 * REPORTS_TO_MERGE);
    newRowIndexModulo = newRowIndex - 1;
}
