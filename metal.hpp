#ifndef METAL_HPP
#define METAL_HPP

#include "material.hpp"

namespace strangeloop {
class Metal : public Material
{
public:
    Metal(const Color& c) : _color(c) {}
    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
    ) const override
    {
        Vector3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
        scattered = Ray(rec.p,reflected);
        attenuation = _color;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
private:
    Color _color;
};
}
#endif // METAL_HPP
