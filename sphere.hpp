#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "ray.hpp"
#include "common.hpp"

#include <memory>

using strangeloop::Hittable;
using strangeloop::HitRecord;
using strangeloop::Point;
using strangeloop::Ray;

namespace strangeloop {
class Sphere : public Hittable
{
public:
    Sphere();
    Sphere(Point center, double r);
    Sphere(Point center, double r, std::shared_ptr<Material> m);

    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;

private:
    Point _center;
    double _radius;
    std::shared_ptr<Material> _material;
};
}
#endif // SPHERE_HPP
