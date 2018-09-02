//
// Created by kevin on 2018/9/1.
//

#ifndef MTVRPTWSC_CHROMOSOME_H
#define MTVRPTWSC_CHROMOSOME_H

#include "Route.h"

class Chromosome {
public:
    Chromosome();

    void ClarkeAndWright();

    std::vector<int> getIDs();



private:
    bool ifInRoute(int num, std::vector<int> ids);

    std::vector<int> _ids;

};

#endif //MTVRPTWSC_CHROMOSOME_H
