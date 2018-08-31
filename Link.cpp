//
// Created by kevin on 2018/8/29.
//
#include "Param.h"

Link::Link() {}

Link::Link(int s, int e, float saving) {
    this->_start = s;
    this->_end = e;
    this->_saving = saving;
}

bool Link::cmp(const Link &l1, const Link &l2) {
    return l1._saving > l2._saving;
}

float Link::getSaving() {
    return _saving;
}

void Link::setSaving(float s) {
    this->_saving = s;
}

int Link::getStart() {
    return _start;
}

void Link::setStart(int s) {
    this->_start = s;
}

int Link::getEnd() {
    return _end;
}

void Link::setEnd(int e) {
    this->_end = e;
}

