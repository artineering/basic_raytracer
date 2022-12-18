#ifndef HITTABLELIST_HPP
#define HITTABLELIST_HPP

#include "hittable.hpp"
#include "common.hpp"
#include "ray.hpp"

#include <memory>
#include <vector>

using strangeloop::Hittable;
using strangeloop::Ray;
using strangeloop::Vector3;
using strangeloop::Point;
using strangeloop::HitRecord;

namespace strangeloop {
class HittableList : public Hittable
{
public:
    HittableList();
    HittableList(std::shared_ptr<Hittable> object);

    void clear();
    void add(std::shared_ptr<Hittable> object);

    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
private:
    std::vector<std::shared_ptr<Hittable>> objects;
};
}
#endif // HITTABLELIST_HPP
