#ifndef HW3_PROGRESSREPORTER_H
#define HW3_PROGRESSREPORTER_H


class ProgressReporter {
public:
    ProgressReporter(unsigned width, unsigned height)
        : total(width * height)
        , width(width)
        , printed(0) {
    }

    void handleProgress(unsigned x, unsigned y);

private:
    unsigned total;
    unsigned width;
    unsigned printed;
};


#endif //HW3_PROGRESSREPORTER_H
