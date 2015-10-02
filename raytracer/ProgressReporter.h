#pragma once


class ProgressReporter {
public:
    ProgressReporter(unsigned width, unsigned height)
        : width(width)
        , total(width * height)
        , current(0)
        , printed(0) {
    }

    void handleProgress(unsigned x, unsigned y);

private:
    unsigned width;
    unsigned total;
    unsigned current;
    unsigned printed;
};
