//
// Created by timas on 27.07.2021.
//

#include "auxiliary.hpp"

int genalg::getRandomNumber(const int &min, const int &max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>((rand() * fraction * (max - min + 1) + min));
}