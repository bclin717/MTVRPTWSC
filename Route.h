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

    void setID(int id);

    int getID();

    void addNode(int n);
    std::vector<int> _customerIDs;

private:
    int _id;
    std::vector<int> _time;
};


#endif //MTVRPTWSC_ROUTE_H
