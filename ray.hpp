#ifndef RAY_HPP
#define RAY_HPP

#include "vector3.hpp"
#include "common.hpp"

using strangeloop::Vector3;
using strangeloop::Point;

namespace strangeloop {
    class Ray
    {
    public:
        Ray();
        Ray(Point origin, Vector3 direction);
        Ray(Ray& r);

        const Point& origin() const;
        const Vector3& direction() const;

        Point origin();
        Vector3 direction();

        Point at(double t) const;
    private:
        Point _origin;
        Vector3 _direction;
    };
}

#endif // RAY_HPP
