#ifndef HW3_PROGRESSREPORTER_H
#define HW3_PROGRESSREPORTER_H


class ProgressReporter {
public:
    ProgressReporter(unsigned width, unsigned height)
        : width(width)
        , height(height) {
        init();
    }

    void handleProgress(unsigned x, unsigned y);

private:
    static const unsigned REPORTS_TO_MERGE = 50;
    static const unsigned REPORTS_TO_MERGE_MODULO = REPORTS_TO_MERGE - 1;

    void init();

    unsigned width;
    unsigned height;
    unsigned newRowIndex;
    unsigned newRowIndexModulo;
};


#endif //HW3_PROGRESSREPORTER_H
