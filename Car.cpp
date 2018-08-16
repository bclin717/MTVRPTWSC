//
// Created by kevin on 2018/8/16.
//

#include "Car.h"

Route Car::getRoute() { return Route(_route); }

void Car::setRoute(Route r) { _route = Route(r); }