#include "aabb.hpp"

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

bool AABB::test(const Ray &ray) const
{
    return false;
}
