#include "aabb.hpp"
#include "vector3.hpp"

using namespace strangeloop;

AABB::AABB()
    :center(0,0,0),size{0.0,0.0,0.0}
{

}

AABB::AABB(Point center, double size)
    :center(center),size{size,size,size}
{

}

AABB::AABB(Point min, Point max)
    :center((min[0] + max[0])/2,(min[1] + max[1])/2,(min[2] + max[2])/2),
      size{fabs(min[0] - max[0])/2,fabs(min[1] - max[1])/2,fabs(min[2] - max[2])/2}
{

}

Point AABB::getMin() const
{
    return Point(center[0] - size[0],center[1] - size[1],center[2] - size[2]);
}

Point AABB::getMax() const
{
    return Point(center[0] + size[0],center[1] + size[1],center[2] + size[2]);
}

bool AABB::test(const AABB &target) const
{
    return false;
}

bool AABB::test(const Ray &ray, Point &coord) const
{
    const int NUMDIM = 3;
    const int RIGHT = 0;
    const int LEFT = 1;
    const int MIDDLE = 2;
    bool inside = true;
    int whichPlane;
    Vector3 maxT;
    Vector3 quadrant;
    Vector3 candidatePlane;
    Point min = getMin();
    Point max = getMax();
    Point origin = ray.origin();
    Vector3 direction = ray.direction();

    // Find the candidate planes.
    for (int i = 0; i < NUMDIM; i++) {
        if (origin[i] < min[i]) {
            quadrant[i] = LEFT;
            candidatePlane[i] = min[i];
            inside = false;
        } else if (origin[i] > max[i]) {
            quadrant[i] = RIGHT;
            candidatePlane[i] = max[i];
            inside = false;
        } else {
            quadrant[i] = MIDDLE;
        }
    }
    // If the ray origin is inside the bounding box, return the origin as the coordinate
    // and return the test as true.
    if (inside) {
        coord = origin;
        return true;
    }

    // Calculate the T distances to the candidate planes.
    for (int i = 0; i < NUMDIM; i++) {
        if (quadrant[i] != MIDDLE && direction[i] != 0.0) {
            maxT[i] = (candidatePlane[i] - origin[i]) / direction[i];
        } else {
            maxT[i] = -1.0;
        }
    }

    // Get the largest of the T distances to get the actual intersection plane.
    whichPlane = 0;
    for (int i = 0; i < NUMDIM; i++) {
        if (maxT[whichPlane] < maxT[i]) {
            whichPlane = i;
        }
    }

    if (maxT[whichPlane]  < 0.0) {
        return false;
    }

    for (int i = 0; i < NUMDIM; i++) {
        if (whichPlane != i) {
            coord[i] = origin[i] + maxT[whichPlane] * direction[i];
            if (coord[i] < min[i] || coord[i] > max[i]) {
                return false;
            }
        } else {
            coord[i] = candidatePlane[i];
        }
    }

    return true;
}

bool AABB::test(const Sphere &sphere) const
{
    Point min = getMin();
    Point max = getMax();
    Point center = sphere.center();
    double radius = sphere.radius();
    double a, b, dmin, dmax;
    double r2 = sqrt(radius);
    return true;
}

