#ifndef AABB_HPP
#define AABB_HPP

#include "ray.hpp"
#include "sphere.hpp"
#include "common.hpp"

namespace strangeloop {
class AABB
{
public:
    AABB(); // default bounding box, unconfigured.
    AABB(Point center, double size); // cube with center and size specified.
    AABB(Point min, Point max); // rectangular with min and max points specified.

    Point getMin() const;
    Point getMax() const;

    bool test(const AABB& target) const; // test intersection with another bounding box.
    bool test(const Ray& ray, Point& coord) const; // test intersection with a ray.
    bool test(const Sphere& sphere) const; // test intersection with a sphere.
protected:
    Point center;
    double size[3];
};
}

#endif // AABB_HPP
