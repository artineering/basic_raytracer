#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "material.hpp"

namespace strangeloop {
class Lambertian: public Material {
public:
    Lambertian(const Color& c) : _color(c) {}

    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
    ) const override
    {
        auto scatterDir = rec.normal + random_unit_vector();
        if (scatterDir.nearZero()) {
            scatterDir = rec.normal;
        }
        scattered = Ray(rec.p, scatterDir);
        attenuation = _color;
        return true;
    }
private:
    Color _color;
};
}
#endif // LAMBERTIAN_HPP
