#include "Param.h"

vector<Customer> dCustomers;
vector<Customer> sCustomers;

vector<Customer> L1;
vector<Customer> L2;

vector<Chromosome> chromosomes;
Chromosome chromosome;

void algorithm2() {
    //Roulette Wheel Selection
    //Calculate probabilities of all Chromosome
    double total = 0;
    for (int i = 0; i < NumberOfChromosome; i++)
        total += chromosomes.at(i).getFitnessValue();

    chromosomes.at(0).setWheelProbability(0);

    for (int i = 1; i < NumberOfChromosome; i++)
        chromosomes.at(i).setWheelProbability(
                (chromosomes.at(i).getFitnessValue() / total) + chromosomes.at(i - 1).getWheelProbability());

    //Select
    double p;
    Chromosome parent[2] = {Chromosome(), Chromosome()}, child[2] = {Chromosome(), Chromosome()};

    int id[2] = {-1, -1};
    do {
        for (int i = 0; i < 2; i++) {
            p = static_cast<double>(rand() / (RAND_MAX + 1.0));
            for (int i2 = 0; i2 < NumberOfChromosome; i2++) {
                if (p > chromosomes.at(i2).getWheelProbability()) {
                    if (i2 == NumberOfChromosome - 1) {
                        parent[i] = Chromosome(chromosomes.at(i2), true);
                        id[i] = i2;
                        break;
                    } else if (p <= chromosomes.at(i2 + 1).getWheelProbability()) {
                        parent[i] = Chromosome(chromosomes.at(i2), true);
                        id[i] = i2;
                        break;
                    }

                }

            }
        }
    } while (id[0] == id[1]);


    int size = parent[0].getCustomers().size();
    int cutBegin = -1, cutEnd = -1;
    do {
        cutBegin = (rand() % size - 1) + 1;
        cutEnd = (rand() % size - 1) + 1;
    } while (cutBegin == cutEnd);

    if(cutBegin > cutEnd) {
        int temp = cutBegin;
        cutBegin = cutEnd;
        cutEnd = temp;
    }
    
    for(int i = 0; i < 2; i++) {
        for (int i2 = cutBegin; i2 < cutEnd; i2++) {
            child[i].getCustomers().emplace_back(parent[i].getCustomers().at(i2));
        }
    }

    for(int i = cutBegin; i < parent[0].getCustomers().size(); i++) {
        if(!child[1].isExists(parent[0].getCustomers().at(i).getID()))
            child[1].getCustomers().emplace_back(parent[0].getCustomers().at(i));
    }

    for (int i = cutBegin; i < parent[1].getCustomers().size(); i++) {
        if (!child[0].isExists(parent[1].getCustomers().at(i).getID()))
            child[0].getCustomers().emplace_back(parent[1].getCustomers().at(i));
    }


    for (int i = 1; i < cutBegin; i++) {
        if(!child[1].isExists(parent[0].getCustomers().at(i).getID()))
            child[1].getCustomers().insert(child[1].getCustomers().begin(), parent[0].getCustomers().at(i));
        if(!child[0].isExists(parent[1].getCustomers().at(i).getID()))
            child[0].getCustomers().insert(child[0].getCustomers().begin(), parent[1].getCustomers().at(i));
    }

    for (int i = 0; i < 2; i++) {
        child[i].getCustomers().insert(child[i].getCustomers().begin(), 0);
        child[i].calculateFitnessValue();
        chromosomes.push_back(Chromosome(child[i]));
    }

    sort(chromosomes.begin(), chromosomes.end(), Chromosome::cmp);

    for (int i = 0; i < 2; i++)
        chromosomes.pop_back();
}

void algorithm3() {
    chromosome = Chromosome(L1, true);

    int minPos, minFitV;
    bool flag = false;
    while (!L2.empty()) {
        Customer c = Customer(L2.at(0));
        L2.erase(L2.begin());
        minPos = 1;
        minFitV = 9999999;
        flag = false;
        // TODO algorithm3
        for (int i = 1; i < chromosome.getCustomers().size(); i++) {
            if (flag) {
                chromosome.getCustomers().insert(chromosome.getCustomers().begin() + i, Customer(c));
                chromosome.calculateFitnessValue();
                if (chromosome.getFitnessValue() <= minFitV) {
                    minFitV = chromosome.getFitnessValue();
                    minPos = i;
                }
                chromosome.getCustomers().erase(chromosome.getCustomers().begin() + i);
            }
            if (chromosome.getCustomers().at(i).getID() == c.getID() - NumberOfDeterministicCustomers + 1) {
                i++;
                flag = true;
            }
        }

        chromosome.getCustomers().insert(chromosome.getCustomers().begin() + minPos, c);
    }
    chromosome.getCustomers().emplace_back(chromosome.getCustomers().at(1));
    chromosome.getCustomers().erase(chromosome.getCustomers().begin()+1);
    chromosome.calculateFitnessValue();

}

int main() {
    // Genrating customers
    for (int i = 0; i < NumberOfDeterministicCustomers; i++) {
        dCustomers.emplace_back(i, Lbound[i], Ubound[i]);
    }

    for (int i = NumberOfDeterministicCustomers;
         i < NumberOfStochasticCustomers + NumberOfDeterministicCustomers - 1; i++) {
        sCustomers.emplace_back(i, Lbound[i - NumberOfDeterministicCustomers],
                                Ubound[i - NumberOfDeterministicCustomers]);
    }


    // Generating probability of stochastic customers randomly
    srand(static_cast<unsigned int>(time(nullptr)));
    float p;
    for (int i = 0; i < NumberOfStochasticCustomers - 1; i++) {
        p = static_cast<float>((float) rand() / (RAND_MAX + 1.0));
        sCustomers.at(i).setProbability(p);
    }

    // Classify high probability stochastic customers and low probability stochastic customers

    // Put deterministic customers into L1
    for (int i = 0; i < NumberOfDeterministicCustomers; i++) {
        L1.emplace_back(dCustomers.at(i));
    }

    // Classified by probability
    for (int i = 0; i < NumberOfStochasticCustomers - 1; i++) {
        L2.emplace_back(sCustomers.at(i));
    }

    // Sorting
    sort(L2.begin(), L2.end(), Customer::cmp);

    chromosomes.clear();
    for (int i = 0; i < NumberOfChromosome; i++)
        chromosomes.emplace_back(Chromosome(L1));

    // Use Hybrid Generation Algorithm to generate a route.
    for (int i = 0; i < NumberOfGeneration; i++)
        algorithm2();

    // Best route (only dCustomer)
    chromosomes.at(0).getIDs();


    // Add sCustomer then calculate best route
    L1.clear();
    L1 = vector<Customer>(chromosomes.at(0).getCustomers());
    for(int i = 1; i < L1.size(); i++) {
        if(L1.at(i).getID() == 0) L1.erase(L1.begin()+i);
    }

    algorithm3();

    for (int i = 0; i < chromosome.getCustomers().size(); i++) {
        cout << chromosome.getCustomers().at(i).getID() << " ";
    }
    cout << "Fitness Value : " << chromosome.getFitnessValue() << endl;

    return 0;
}