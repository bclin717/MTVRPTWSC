//
// Created by kevin on 2018/8/13.
//

#ifndef MTVRPTWSC_PARAM_H
#define MTVRPTWSC_PARAM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <unistd.h>
#include <thread>
#include <assert.h>
#include <chrono>

#include "Route.h"
#include "Customer.h"
#include "TimeWindow.h"
#include "Car.h"
#include "Scenario.h"
#include "Chromosome.h"

using namespace std;

static const int NumberOfVehicle = 1000;
static const int NumberOfVehicle2 = 260;
static const int CapacityOfVehicle = 4;
static const float PenalizationFactor = 1000;
static const int serviceTime = 8;

static int NumberOfDeterministicCustomers = 0;
static int NumberOfStochasticCustomers = 0;

static const int NumberOfChromosome = 20;

static const unsigned int NumberOfGeneration = 2000;

static std::vector<int> Lbound; // ai.txt
static std::vector<int> Ubound; // bi.txt
static std::vector<int> Lbound2; // ai2.txt
static std::vector<int> Ubound2; // bi2.txt
extern std::vector<std::vector<float>> costMatrix; // travel cost matrix.txt
extern std::vector<std::vector<float>> timeMatrix; // travel time matrix.txt
static std::vector<Scenario> scenarios; // travel time matrix.txt

#endif //MTVRPTWSC_PARAM_H
