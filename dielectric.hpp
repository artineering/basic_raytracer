#ifndef DIELECTRIC_HPP
#define DIELECTRIC_HPP

#include "material.hpp"
#include "common.hpp"

namespace strangeloop {
class Dielectric : public Material {
public:
    Dielectric(double refractionIndex) : _index(refractionIndex) {}
    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
    ) const override
    {
        attenuation = Color(1.0,1.0,1.0);
        double refractRatio = rec.frontFace ? (1.0/_index) : _index;
        Vector3 unitDir = unit_vector(r_in.direction());
        double cosTheta = fmin(dot(-1 * unitDir, rec.normal),1.0);
        double sinTheta = sqrt(1 - cosTheta*cosTheta);
        bool cannotRefract = refractRatio * sinTheta > 1.0;
        Vector3 direction;
        if (cannotRefract || reflectance(cosTheta, refractRatio) > randomDouble(0.0,0.999)) {
            direction = reflect(unitDir,rec.normal);
        } else {
            direction = refract(unitDir,rec.normal,refractRatio);
        }
        scattered = Ray(rec.p,direction);
        return true;
    }
private:
    double _index;

    static double reflectance(double cosine, double refIndex) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refIndex) / (1 + refIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0)*pow(1 - cosine, 5);
    }
};
}
#endif // DIELECTRIC_HPP
