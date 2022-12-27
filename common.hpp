#ifndef COMMON_HPP
#define COMMON_HPP

#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <random>
#include <memory>

#include "vector3.hpp"

using std::shared_ptr;
using std::vector;
using std::sqrt;

const double INF = std::numeric_limits<double>::infinity();
const double PI = M_PI;
const double PI_2 = M_PI_2;
const double PI_4 = M_PI_4;
const double ONE_OVER_PI = M_1_PI;
const double TWO_OVER_PI = M_2_PI;

namespace strangeloop {
    using Color = Vector3;
    using Point = Vector3;

inline double degsToRads(double degrees) {
    return degrees * PI / 180.0;
}

inline double radsToDegs(double radians) {
    return radians * 180.0 / PI;
}

inline double randomDouble(double min, double max) {
    static std::uniform_real_distribution<double> distribution(min,max);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double clamp(double val, double min, double max) {
    if (val < min) {
        return min;
    }
    if (val > max) {
        return max;
    }
    return val;
}

inline Vector3 random_vector() {
    return Vector3(randomDouble(0.0,1.0),randomDouble(0.0,1.0),randomDouble(0.0,1.0));
}

inline Vector3 random_vector(double min, double max) {
    return Vector3(randomDouble(min,max),randomDouble(min,max),randomDouble(min,max));
}

inline Vector3 randomInUnitSphere() {
    while(true) {
        auto p = random_vector(-1,1);
        if (p.length_squared() >= 1) {
            continue;
        }
        return p;
    }
}

inline Vector3 random_unit_vector() {
    return unit_vector(randomInUnitSphere());
}

inline Vector3 randomInUnitDisk() {
    while (true) {
        auto p = Vector3(randomDouble(-1,1), randomDouble(-1,1),0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

}


#endif // COMMON_HPP
