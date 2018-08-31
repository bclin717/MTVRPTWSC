#include "Param.h"

vector<Customer> dCustomers;
vector<Customer> sCustomers;

vector<Customer> L1;
vector<Customer> L2;

vector<Link> links;



void algorithm1() {

}

void adsplit() {

}

bool ifInRoute(int num, vector<int> ids) {
    for (int id : ids) if(num == id) return true;
    return false;
}

Route algorithm2() {
    Route route;
    // Compute the savings for every customer i and j in L1
    for(int i = 1; i < NumberOfDeterministicCustomers; i++) {
        for(int j = i; j < NumberOfDeterministicCustomers; j++) {
            if(i == j) continue;
            links.emplace_back(i, j, distanceMatrix[i][0] + distanceMatrix[0][j] - distanceMatrix[i][j]);
        }
    }

    //Sort the savings in descending order.
    sort(links.begin(), links.end(), Link::cmp);

    //Clarke and Wright heuritstics
    vector<int> ids = route.getCustomerIDs();
    for (auto &link : links) {
        int start = link.getStart();
        int end = link.getEnd();

        if(ids.size() == NumberOfDeterministicCustomers-1) break;
        else if(ids.empty()) {
            ids.push_back(start);
            ids.push_back(end);
        } else if(!ifInRoute(start, ids) && !ifInRoute(end, ids)) {
            // TODO Ordering Problem
            continue;
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

    //Create other chromosome randomly
    int chromosome[NumberOfDeterministicCustomers+1][NumberOfChromosome];

    for(int i = 0; i < NumberOfChromosome - 1; i++) {
        chromosome[0][i] = 0;
        chromosome[NumberOfDeterministicCustomers][i] = 0;
    }

    for(int i = 0; i < NumberOfDeterministicCustomers; i++) {
        chromosome[i][NumberOfChromosome-1] = ids.at(i);
    }
    chromosome[NumberOfDeterministicCustomers][NumberOfChromosome-1] = 0;

    for(int all = 0; all < NumberOfChromosome - 1; all++) {
        for(int i = 1; i < NumberOfDeterministicCustomers; i++) {
            chromosome[i][all] = i;
        }
    }

    for(int all = 0; all < NumberOfChromosome - 1; all++) {
        for(int i = 1; i < NumberOfDeterministicCustomers; i++) {
            int j = (rand() % (NumberOfDeterministicCustomers-1))+1 ;
            int temp = chromosome[i][all];
            chromosome[i][all] = chromosome[j][all];
            chromosome[j][all] = temp;
        }
    }

    for(int i = 0; i < NumberOfChromosome ; i++) {
        for(int j = 0; j < NumberOfDeterministicCustomers+1; j++) {
            cout << chromosome[j][i] << " ";
        }
        cout << endl;
    }


    //

    // TODO algorithm2

    return Route();
}

Route algorithm3() {
    while (!L2.empty()) {
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
        dCustomers.emplace_back(i);
    for (int i = NumberOfDeterministicCustomers + 1;
         i < NumberOfStochasticCustomers + NumberOfDeterministicCustomers + 2; i++)
        sCustomers.emplace_back(i);

    // Generating probability of stochastic customers randomly
    srand(static_cast<unsigned int>(time(nullptr)));
    float p;
    for (int i = 0; i < NumberOfStochasticCustomers; i++) {
        p = static_cast<float>((float) rand() / (RAND_MAX + 1.0));
        sCustomers.at(i).setProbability(p);
    }

    // Classify high probability stochastic customers and low probability stochastic customers

    // Put deterministic customers into L1
    for (int i = 0; i < NumberOfDeterministicCustomers + 1; i++) {
        L1.emplace_back(dCustomers.at(i));
    }

    // Classified by probability
    for (int i = 0; i < NumberOfStochasticCustomers; i++) {
        if (sCustomers.at(i).getProbability() >= PriorityThresholdValue)
            L1.emplace_back(sCustomers.at(i));
        else
            L2.emplace_back(sCustomers.at(i));
    }

    // Sorting
    sort(L2.begin(), L2.end(), Customer::cmp);

    // Use Hybrid Generation Algorithm to generate a route.
    Route S = algorithm2();


    Route S2 = algorithm3();

    return 0;
}