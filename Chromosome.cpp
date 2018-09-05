//
// Created by kevin on 2018/9/1.
//

#include "Param.h"

Chromosome::Chromosome(std::vector<Customer>& c) {
    _fitnewssValue = 0;

    _customers.assign(c.begin(), c.end());

    for(unsigned int i = 1; i < _customers.size(); i++) {
        int j = static_cast<int>((rand() % (_customers.size() - 1)) + 1);
        Customer temp = _customers.at(i);
        _customers.at(i) = _customers.at(j);
        _customers.at(j) = temp;
    }

    calculateFitnessValue();
}

bool Chromosome::ifInRoute(int num, vector<int> ids) {
    for (int id : ids) if(num == id) return true;
    return false;
}

//void Chromosome::ClarkeAndWright() {
//    vector<Link> links;
//    // Compute the savings for every customer i and j in L1
//    for(int i = 1; i < _customers.size(); i++) {
//        for(int j = i; j < _customers.size(); j++) {
//            if(i == j) continue;
//            if(i >= NumberOfDeterministicCustomers)
//                links.emplace_back(i, j, distanceMatrix[i-NumberOfDeterministicCustomers+1][0] + distanceMatrix[0][j-NumberOfDeterministicCustomers+1] - distanceMatrix[i-NumberOfDeterministicCustomers+1][j-NumberOfDeterministicCustomers+1]);
//            else
//                links.emplace_back(i, j, distanceMatrix[i][0] + distanceMatrix[0][j] - distanceMatrix[i][j]);
//        }
//    }
//    //Sort the savings in descending order.
//    sort(links.begin(), links.end(), Link::cmp);
//
//    _ids.clear();
//    //Clarke and Wright heuritstics
//    for (auto &link : links) {
//        int start = link.getStart();
//        int end = link.getEnd();
//
//        if(_ids.size() == _customers.size()-1) break;
//        else if(_ids.empty()) {
//            _ids.emplace_back(start);
//            _ids.emplace_back(end);
//        } else if(!ifInRoute(start, _ids) && !ifInRoute(end, _ids)) {
//            // TODO Ordering Problem;
//            _ids.emplace_back(start);
//            _ids.emplace_back(end);
//        } else if(ifInRoute(start, _ids) && ifInRoute(end, _ids)) {
//            continue;
//        } else if(_ids.at(0) == start) {
//            _ids.insert(_ids.begin(), end);
//        } else if(_ids.at(0) == end) {
//            _ids.insert(_ids.begin(), start);
//        } else if(_ids.at(_ids.size()-1) == start) {
//            _ids.emplace_back(end);
//        } else if(_ids.at(_ids.size()-1) == end) {
//            _ids.emplace_back(start);
//        }
//    }
//    _ids.insert(_ids.begin(), 0);
//    _ids.emplace_back(0);
//
//    calculateFitnessValue();
//}

float Chromosome::penalty(float TW, float lowerbound) {
    return (TW - lowerbound) * PenalizationFactor;
}

float Chromosome::calculateFitnessValue() {
    Car car[NumberOfVehicle];
    float COST = 0;
    float TW = 0;
    int LOAD = 0;
    int carCount = 0;
    car[carCount].route.push_back(0);
    for(unsigned int i = 1; i < _customers.size(); i++) {
        LOAD += _customers.at(i).getDemandQuantity();
        if(LOAD > CapacityOfVehicle) {
            COST += (distanceMatrix[_customers.at(i).getID()][0] * SpeedKmMin);
            car[++carCount].route.push_back(0);
            i--;
            LOAD = 0;
            continue;
        } else {
            TW = COST > _customers.at(i).getTimeWindow().getLowerBound() ? COST : _customers.at(i).getTimeWindow().getLowerBound();

            COST += (distanceMatrix[_customers.at(i-1).getID()][_customers.at(i).getID()] * SpeedKmMin);

            if(TW > _customers.at(i).getTimeWindow().getUpperBound())
                COST += penalty(TW, _customers.at(i).getTimeWindow().getUpperBound());

        }
    }
    return COST;
}


vector<Customer> Chromosome::getIDs() {
    for(int i = 0; i < _customers.size(); i++)
        std::cout << _customers.at(i).getID() << " ";
    cout << endl;
    return _customers;
}
