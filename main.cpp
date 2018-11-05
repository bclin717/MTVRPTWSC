#include "Param.h"

vector<Customer> dCustomers;
vector<Customer> sCustomers;

vector<Customer> L1;
vector<Customer> L2;

vector<Chromosome> chromosomes;
Chromosome solution;

vector<Car> cars;
vector<Route> routes;

extern std::vector<int> Lbound = vector<int>(0); // ai.txt
extern std::vector<int> Ubound = vector<int>(0); // bi.txt
extern std::vector<int> Lbound2 = vector<int>(0); // ai2.txt
extern std::vector<int> Ubound2 = vector<int>(0); // bi2.txt
extern std::vector<std::vector<float>> costMatrix = vector<vector<float>>(0); // travel cost matrix.txt
extern std::vector<std::vector<float>> timeMatrix = vector<vector<float>>(0); // travel time matrix.txt

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

    for (int i = 0; i < 2; i++) {
        parent[i].setNOD(NumberOfDeterministicCustomers);
        child[i].setNOD(NumberOfDeterministicCustomers);
    }

    int id[2] = {-1, -1};
    do {
        for (int i = 0; i < 2; i++) {
            p = static_cast<double>(rand() / (RAND_MAX + 1.0));
            for (int i2 = 0; i2 < NumberOfChromosome; i2++) {
                if (p > chromosomes.at(i2).getWheelProbability()) {
                    if (i2 == NumberOfChromosome - 1) {
                        parent[i] = Chromosome(chromosomes.at(i2), true, NumberOfDeterministicCustomers);
                        id[i] = i2;
                        break;
                    } else if (p <= chromosomes.at(i2 + 1).getWheelProbability()) {
                        parent[i] = Chromosome(chromosomes.at(i2), true, NumberOfDeterministicCustomers);
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

    if (cutBegin > cutEnd) {
        int temp = cutBegin;
        cutBegin = cutEnd;
        cutEnd = temp;
    }

    for (int i = 0; i < 2; i++) {
        for (int i2 = cutBegin; i2 < cutEnd; i2++) {
            child[i].getCustomers().emplace_back(parent[i].getCustomers().at(i2));
        }
    }

    for (int i = cutBegin; i < parent[0].getCustomers().size(); i++) {
        if (!child[1].isExists(parent[0].getCustomers().at(i).getID()))
            child[1].getCustomers().emplace_back(parent[0].getCustomers().at(i));
    }

    for (int i = cutBegin; i < parent[1].getCustomers().size(); i++) {
        if (!child[0].isExists(parent[1].getCustomers().at(i).getID()))
            child[0].getCustomers().emplace_back(parent[1].getCustomers().at(i));
    }


    for (int i = 1; i < cutBegin; i++) {
        if (!child[1].isExists(parent[0].getCustomers().at(i).getID()))
            child[1].getCustomers().insert(child[1].getCustomers().begin(), parent[0].getCustomers().at(i));
        if (!child[0].isExists(parent[1].getCustomers().at(i).getID()))
            child[0].getCustomers().insert(child[0].getCustomers().begin(), parent[1].getCustomers().at(i));
    }

    for (auto &i : child) {
        i.getCustomers().insert(i.getCustomers().begin(), 0);
        i.calculateFitnessValue();
        chromosomes.emplace_back(i);
    }

    sort(chromosomes.begin(), chromosomes.end(), Chromosome::cmp);

    for (int i = 0; i < 2; i++)
        chromosomes.pop_back();
}

void algorithm3() {
    int minPos, minFitV;
    bool flag = false;
    solution.setNOD(NumberOfDeterministicCustomers);
    while (!L2.empty()) {
        Customer c = Customer(L2.at(0));
        L2.erase(L2.begin());
        minPos = 1;
        minFitV = 9999999;
        flag = false;
        for (int i = 1; i < solution.getCustomers().size(); i++) {
            if (flag) {
                solution.getCustomers().insert(solution.getCustomers().begin() + i, Customer(c));
                solution.calculateFitnessValue();
                if (solution.getFitnessValue() <= minFitV) {
                    minFitV = solution.getFitnessValue();
                    minPos = i;
                }
                solution.getCustomers().erase(solution.getCustomers().begin() + i);
            }
            if (solution.getCustomers().at(i).getID() == c.getID() - NumberOfDeterministicCustomers + 1) {
                flag = true;
            }
        }

        solution.getCustomers().insert(solution.getCustomers().begin() + minPos, c);
    }
//    chromosome.getCustomers().emplace_back(chromosome.getCustomers().at(1));
    solution.getCustomers().erase(solution.getCustomers().begin() + 1);
    solution.calculateFitnessValue();
}

bool isExist(int id, vector<int> IDs) {
    bool flag = false;
    for (int ID : IDs) {
        if (ID == id) {
            return flag;
        }
    }
    return flag;
}

void readFiles() {
    float finput;
    int input;
    char c;

    //Read ai.txt
    FILE *ai;
    if ((ai = fopen("ai.txt", "r")) == nullptr) {
        cout << "ai.txt does not exist!!" << endl;
        exit(1);
    }

    while (fscanf(ai, "%d%c", &input, &c) != EOF)
        Lbound.emplace_back(input);
    fclose(ai);

    //Read bi.txt
    FILE *bi;
    if ((bi = fopen("bi.txt", "r")) == nullptr) {
        cout << "bi.txt does not exist!!" << endl;
        exit(1);
    }

    while (fscanf(bi, "%d%c", &input, &c) != EOF)
        Ubound.emplace_back(input);
    fclose(bi);

    //Read ai2.txt
    FILE *ai2;
    if ((ai2 = fopen("ai2.txt", "r")) == nullptr) {
        cout << "ai2.txt does not exist!!" << endl;
        exit(1);
    }

    while (fscanf(ai2, "%d%c", &input, &c) != EOF)
        Lbound2.emplace_back(input);
    fclose(ai2);

    //Read bi2.txt
    FILE *bi2;
    if ((bi2 = fopen("bi2.txt", "r")) == nullptr) {
        cout << "bi2.txt does not exist!!" << endl;
        exit(1);
    }

    while (fscanf(bi2, "%d%c", &input, &c) != EOF)
        Ubound2.emplace_back(input);
    fclose(bi2);


    //Read travel cost matrix.txt
    FILE *tcm;
    if ((tcm = fopen("travel cost matrix.txt", "r")) == nullptr) {
        cout << "travel cost matrix.txt does not exist!!" << endl;
        exit(1);
    }
    costMatrix.emplace_back(vector<float>());
    for (int i = 0; fscanf(tcm, "%f%c", &finput, &c) != EOF;) {
        if (c == '\n') {
            costMatrix.at(i).emplace_back(finput);
            costMatrix.emplace_back(vector<float>());
            i++;
            continue;
        }
        costMatrix.at(i).emplace_back(finput);
    }
    fclose(tcm);


    //Read travel time matrix.txt
    FILE *ttm;
    if ((ttm = fopen("travel time matrix.txt", "r")) == nullptr) {
        cout << "travel time matrix.txt does not exist!!" << endl;
        exit(1);
    }
    timeMatrix.emplace_back(vector<float>());
    for (int i = 0; fscanf(ttm, "%f%c", &finput, &c) != EOF;) {
        if (c == '\n') {
            timeMatrix.at(i).emplace_back(finput);
            timeMatrix.emplace_back(vector<float>());
            i++;
            continue;
        }
        timeMatrix.at(i).emplace_back(finput);
    }
    fclose(ttm);
}

void init() {
    NumberOfDeterministicCustomers = Lbound.size() + 1;
    NumberOfStochasticCustomers = NumberOfDeterministicCustomers;

    // Generating customers
    dCustomers.emplace_back(0, 0, 720);
    for (int i = 0; i < NumberOfDeterministicCustomers; i++) {
        dCustomers.emplace_back(i + 1, Lbound[i], Ubound[i]);
    }

    for (int i = NumberOfDeterministicCustomers;
         i < NumberOfStochasticCustomers + NumberOfDeterministicCustomers - 1; i++) {
        sCustomers.emplace_back(i, Lbound2[i - NumberOfDeterministicCustomers],
                                Ubound2[i - NumberOfDeterministicCustomers]);
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
}

void runCars() {
    for(int i = 0; i < NumberOfVehicle2; i++) {
        cars.emplace_back(Car(timeMatrix, Lbound, Ubound, Lbound2, Ubound2));
    }
    int nowCar = 0;

    routes.emplace_back(Route());
    routes[0].addNode(0);
    for(int i = 1; i < solution.getCustomers().size(); i++) {
        routes[0].addNode(solution.getCustomers()[i].getID());
        if(solution.getCustomers()[i].getID() == 0) {
            routes.insert(routes.begin(), Route());
            routes[0].addNode(0);
        }
    }
    routes.erase(routes.begin());

    while(!routes.empty()) {
        cars[nowCar].setRoute(routes.at(routes.size()-1));
        routes.pop_back();

        cars[nowCar].run();
        cout << "Car " << nowCar+1 << " ";
        cars[nowCar].print();
        cars[nowCar].clearRoute();

        for(int i = routes.size()-1; i >= 0; i--) {
            int temp = routes[i]._customerIDs.at(0) >= NumberOfDeterministicCustomers ? Ubound2[routes[i]._customerIDs.at(0)-NumberOfDeterministicCustomers+1] : Ubound[routes[i]._customerIDs.at(0)];
            if(cars[nowCar].startTime < temp) {
                break;
            } else {
                if (nowCar < NumberOfVehicle2 - 1) {
                    nowCar++;
                    break;
                }
                else {
                    nowCar = 0;
                    continue;
                }

            }
        }
    }



}

int main() {
    readFiles();
    init();

    chromosomes.clear();
    for (int i = 0; i < NumberOfChromosome; i++)
        chromosomes.emplace_back(Chromosome(L1, NumberOfDeterministicCustomers));

    // Use Hybrid Generation Algorithm to generate a route.
    for (int i = 0; i < NumberOfGeneration; i++)
        algorithm2();

    // Best route (only dCustomer)
    solution = Chromosome(chromosomes.at(0));

    // Check if there's an error occurs
    for (int i = 1; i < solution.getCustomers().size(); i++) {
        if (solution.getCustomers().at(i).getID() == 0)
            solution.getCustomers().erase(solution.getCustomers().begin() + i);
    }

    solution.getIDs();
    algorithm3();


    solution.getCustomers().emplace_back(0);
    for (int i = 1; i < solution.getCustomers().size(); i++) {
        if (i % (CapacityOfVehicle + 1) == 0) {
            solution.getCustomers().insert(solution.getCustomers().begin() + i, 0);
        }
    }

    solution.getIDs();

    runCars();



    cout << endl;
    return 0;
}