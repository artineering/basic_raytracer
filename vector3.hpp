#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <iostream>
#include <cmath>

namespace strangeloop {
class Vector3
{
public:
    Vector3();
    Vector3(double x, double y, double z);
    Vector3(Vector3 &vec);
    Vector3(const Vector3 &vec);

    double operator[](int i) const;
    double& operator[](int i);

    //void operator=(const Vector3& vec);

    Vector3& operator+=(const Vector3& vec);
    Vector3& operator*=(const Vector3& vec);
    Vector3& operator-=(const Vector3& vec);
    Vector3& operator/=(const double t);

    static Vector3 random();

    double length() const;
    double length_squared() const;

    bool nearZero() const;

private:
    double _buffer[3];
};

inline std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
    return out << vec[0] << " " << vec[1] << " " << vec[2] << std::endl;
}

inline Vector3 operator+(const Vector3& vec1, const Vector3& vec2) {
    return Vector3(vec1[0] + vec2[0], vec1[1] + vec2[1], vec1[2] + vec2[2]);
}

inline Vector3 operator-(const Vector3& vec1,const Vector3& vec2) {
    return Vector3(vec1[0] - vec2[0], vec1[1] - vec2[1], vec1[2] - vec2[2]);
}

inline Vector3 operator*(const Vector3& vec1, const Vector3& vec2) {
    return Vector3(vec1[0] * vec2[0], vec1[1] * vec2[1], vec1[2] * vec2[2]);
}

inline Vector3 operator*(const Vector3& vec, double t) {
    return Vector3(vec[0] * t, vec[1] * t, vec[2] * t);
}

inline Vector3 operator*(double t, const Vector3& vec) {
    return vec * t;
}

inline Vector3 operator/(const Vector3& vec, double t) {
    return vec * (1/t);
}

inline double dot(const Vector3& vec1, const Vector3& vec2) {
    return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

inline Vector3 cross(Vector3& vec1, Vector3& vec2) {
    return Vector3(vec1[1]*vec2[2] - vec1[2]*vec2[1],
            vec1[2]*vec2[0] - vec1[0]*vec2[2],
            vec1[0]*vec2[1] - vec1[1]*vec2[0]);
}

inline Vector3 unit_vector(const Vector3& vec) {
    return vec / vec.length();
}

inline Vector3 floor(Vector3& vec) {
    return Vector3(std::floor(vec[0]),std::floor(vec[1]),std::floor(vec[2]));
}

inline Vector3 reflect(const Vector3& v, const Vector3& n) {
    return v - 2*dot(v,n)*n;
}

inline Vector3 refract(const Vector3& uv, const Vector3& n, double etaiOverEta) {
    auto cosTheta = fmin(dot(-1 * uv,n), 1.0);
    Vector3 rPerp = etaiOverEta * (uv + cosTheta * n);
    Vector3 rPara = -sqrt(fabs(1.0 - rPerp.length_squared())) * n;
    return rPerp + rPara;
}

}

#endif // VECTOR3_HPP
