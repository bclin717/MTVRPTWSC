//
// Created by kevin on 2018/9/1.
//

#include "Param.h"

Chromosome::Chromosome() {
    for(int i = 0; i < NumberOfDeterministicCustomers; i++)
        _ids.emplace_back(i);
    _ids.emplace_back(0);
    for(int i = 1; i < NumberOfDeterministicCustomers; i++) {
        int j = (rand() % (NumberOfDeterministicCustomers-1))+1 ;
        int temp = _ids.at(i);
        _ids.at(i) = _ids.at(j);
        _ids.at(j) = temp;
    }
}

bool Chromosome::ifInRoute(int num, vector<int> ids) {
    for (int id : ids) if(num == id) return true;
    return false;
}

void Chromosome::ClarkeAndWright() {
    vector<Link> links;
    // Compute the savings for every customer i and j in L1
    for(int i = 1; i < NumberOfDeterministicCustomers; i++) {
        for(int j = i; j < NumberOfDeterministicCustomers; j++) {
            if(i == j) continue;
            links.emplace_back(i, j, distanceMatrix[i][0] + distanceMatrix[0][j] - distanceMatrix[i][j]);
        }
    }

    //Sort the savings in descending order.
    sort(links.begin(), links.end(), Link::cmp);

    _ids.clear();
    //Clarke and Wright heuritstics
    for (auto &link : links) {
        int start = link.getStart();
        int end = link.getEnd();

        if(_ids.size() == NumberOfDeterministicCustomers-1) break;
        else if(_ids.empty()) {
            _ids.emplace_back(start);
            _ids.emplace_back(end);
        } else if(!ifInRoute(start, _ids) && !ifInRoute(end, _ids)) {
            // TODO Ordering Problem
            continue;
        } else if(ifInRoute(start, _ids) && ifInRoute(end, _ids)) {
            continue;
        } else if(_ids.at(0) == start) {
            _ids.insert(_ids.begin(), end);
        } else if(_ids.at(0) == end) {
            _ids.insert(_ids.begin(), start);
        } else if(_ids.at(_ids.size()-1) == start) {
            _ids.emplace_back(end);
        } else if(_ids.at(_ids.size()-1) == end) {
            _ids.emplace_back(start);
        }
    }
    _ids.insert(_ids.begin(), 0);
    _ids.emplace_back(0);
}

vector<int> Chromosome::getIDs() {
    for(int i = 0; i < _ids.size(); i++)
        std::cout << _ids.at(i) << " ";
    cout << endl;
    return _ids;
}
