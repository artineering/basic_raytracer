#include "ray.hpp"

using namespace strangeloop;

Ray::Ray()
    :_origin(0,0,0),_direction(0,0,0)
{

}

Ray::Ray(Point origin,Vector3 direction)
    :_origin(origin),_direction(direction)
{

}

Ray::Ray(Ray &r)
    :_origin(r._origin),_direction(r._direction)
{

}

const Point& Ray::origin() const
{
    return _origin;
}

const Vector3& Ray::direction() const
{
    return _direction;
}

Point Ray::origin()
{
    return _origin;
}

Vector3 Ray::direction()
{
    return _direction;
}

Point Ray::at(double t) const
{
    return _origin + t * _direction;
}
