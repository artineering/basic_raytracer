#include "vector3.hpp"
#include "common.hpp"
#include <cmath>

using strangeloop::Vector3;

Vector3::Vector3()
    :_buffer{0,0,0}
{

}

Vector3::Vector3(double x, double y, double z)
    :_buffer{x,y,z}
{
}

Vector3::Vector3(Vector3 &vec)
{
    _buffer[0] = vec[0];
    _buffer[1] = vec[1];
    _buffer[2] = vec[2];
}

Vector3::Vector3(const Vector3 &vec)
{
    _buffer[0] = vec[0];
    _buffer[1] = vec[1];
    _buffer[2] = vec[2];
}

double Vector3::operator[](int i) const
{
    return _buffer[i];
}

//void Vector3::operator=(const Vector3 &vec)
//{
//    _buffer[0] = vec[0];
//    _buffer[1] = vec[1];
//    _buffer[2] = vec[2];
//}

Vector3& Vector3::operator+=(const Vector3 &vec)
{
    _buffer[0] += vec[0];
    _buffer[1] += vec[1];
    _buffer[2] += vec[2];
    return *this;
}

Vector3 &Vector3::operator*=(const Vector3 &vec)
{
    _buffer[0] *= vec[0];
    _buffer[1] *= vec[1];
    _buffer[2] *= vec[2];
    return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &vec)
{
    _buffer[0] -= vec[0];
    _buffer[1] -= vec[1];
    _buffer[2] -= vec[2];
    return *this;
}

Vector3 &Vector3::operator/=(const double t)
{
    _buffer[0] /= t;
    _buffer[1] /= t;
    _buffer[2] /= t;
    return *this;
}

Vector3 Vector3::random()
{
    return Vector3(strangeloop::randomDouble(0,1),strangeloop::randomDouble(0,1),strangeloop::randomDouble(0,1));
}

double& Vector3::operator[](int i)
{
    return _buffer[i];
}

double Vector3::length() const
{
    return std::sqrt(length_squared());
}

double Vector3::length_squared() const
{
    return _buffer[0]*_buffer[0] + _buffer[1]*_buffer[1] + _buffer[2]*_buffer[2];
}

bool Vector3::nearZero() const
{
    const auto s = 1e-8;
    return ((fabs(_buffer[0]) < s) && (fabs(_buffer[1]) < s) && (fabs(_buffer[2]) < s));
}

