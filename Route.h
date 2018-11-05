//
// Created by kevin on 2018/8/13.
//

#ifndef MTVRPTWSC_ROUTE_H
#define MTVRPTWSC_ROUTE_H

#include <vector>

class Route {
public:
    Route();

    Route(const Route &r);

    std::vector<int> getCustomerIDs();

    std::vector<int> getTime();

    int getOverhead();

    void setOverhead(int overhead);

    void addNode(int n);
    std::vector<int> _customerIDs;

private:

    std::vector<int> _time;
    int _overhead;
};


#endif //MTVRPTWSC_ROUTE_H
