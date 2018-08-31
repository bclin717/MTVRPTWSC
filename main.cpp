#include "Param.h"

vector<Customer> dCustomers;
vector<Customer> sCustomers;

vector<Customer> L1;
vector<Customer> L2;

vector<Link> links;



void algorithm1() {

}

bool ifInRoute(int num, vector<int> ids) {
    for(int i = 0; i < ids.size(); i++) {
        if(num == ids.at(i)) return true;
    }
    return false;
}


Route algorithm2() {
    Route route;
    // Compute the savings for every customer i and j in L1
    for(int i = 1; i < NumberOfDeterministicCustomers; i++) {
        for(int j = i; j < NumberOfDeterministicCustomers; j++) {
            if(i == j) continue;
            links.push_back(Link(i, j, distanceMatrix[i][0] + distanceMatrix[0][j] - distanceMatrix[i][j]));
        }
    }

    //Sort the savings in descending order.
    sort(links.begin(), links.end(), Link::cmp);

    //Clarke and Wright heuritstics
    vector<int> ids = route.getCustomerIDs();
    for(int i = 0; i < links.size(); i++) {
        int start = links.at(i).getStart();
        int end = links.at(i).getEnd();

        if(ids.size() == NumberOfDeterministicCustomers-1) break;
        else if(ids.size() == 0) {
            ids.push_back(start);
            ids.push_back(end);
        } else if(!ifInRoute(start, ids) && !ifInRoute(end, ids)) {
            // TODO Ordering Problem
            ids.push_back(start);
            ids.push_back(end);
        } else if(ifInRoute(start, ids) && ifInRoute(end, ids)) {
            continue;
        } else if(ids.at(0) == start) {
            ids.insert(ids.begin(), end);
        } else if(ids.at(0) == end) {
            ids.insert(ids.begin(), start);
        } else if(ids.at(ids.size()-1) == start) {
            ids.push_back(end);
        } else if(ids.at(ids.size()-1) == end) {
            ids.push_back(start);
        }
    }
    ids.insert(ids.begin(), 0);
    ids.push_back(0);

    //

    // TODO algorithm2

    return Route();
}

Route algorithm3() {
    while (L2.size() != 0) {
        Customer c = Customer(L2.at(0));
        L2.erase(L2.begin());

        // TODO algorithm3
        /*algorithm3
            ...
            ...
            ...
        */
    }
    return Route();
}

void algorithm4() {

}



int main() {

    // Genrating customers
    for (int i = 0; i < NumberOfDeterministicCustomers + 1; i++)
        dCustomers.push_back(Customer(i));
    for (int i = NumberOfDeterministicCustomers + 1;
         i < NumberOfStochasticCustomers + NumberOfDeterministicCustomers + 2; i++)
        sCustomers.push_back(Customer(i));

    // Generating probability of stochastic customers randomly
    srand(time(NULL));
    float p;
    for (int i = 0; i < NumberOfStochasticCustomers; i++) {
        p = (float) rand() / (RAND_MAX + 1.0);
        sCustomers.at(i).setProbability(p);
    }

    // Classify high probability stochastic customers and low probability stochastic customers

    // Put deterministic customers into L1
    for (int i = 0; i < NumberOfDeterministicCustomers + 1; i++) {
        L1.push_back(Customer(dCustomers.at(i)));
    }

    // Classified by probability
    for (int i = 0; i < NumberOfStochasticCustomers; i++) {
        if (sCustomers.at(i).getProbability() >= PriorityThresholdValue)
            L1.push_back(Customer(sCustomers.at(i)));
        else
            L2.push_back(Customer(sCustomers.at(i)));
    }

    // Sorting
    sort(L2.begin(), L2.end(), Customer::cmp);

    Route S = algorithm2();

    Route S2 = algorithm3();

    return 0;
}