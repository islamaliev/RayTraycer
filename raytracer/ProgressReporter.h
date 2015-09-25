#ifndef HW3_PROGRESSREPORTER_H
#define HW3_PROGRESSREPORTER_H


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


#endif //HW3_PROGRESSREPORTER_H
