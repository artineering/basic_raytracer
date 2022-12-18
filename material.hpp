#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "hittable.hpp"
#include "ray.hpp"
#include "common.hpp"

namespace strangeloop {
class Material
{
public:
    virtual bool scatter(
                const Ray& r_in, const HitRecord& rec, Color& attentuation, Ray& scattered
            ) const = 0;
};
}

#endif // MATERIAL_HPP
