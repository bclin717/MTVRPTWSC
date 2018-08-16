//
// Created by kevin on 2018/8/13.
//

#ifndef MTVRPTWSC_TIMEWINDOW_H
#define MTVRPTWSC_TIMEWINDOW_H


class TimeWindow {
public:
    TimeWindow();

    TimeWindow(const TimeWindow &t);

    int getLowerBound();

    void setLowerBound(int lb);

    int getUpperBound();

    void setUpperBound(int ub);

private:
    int _lowerBound;
    int _upperBound;
};


#endif //MTVRPTWSC_TIMEWINDOW_H
