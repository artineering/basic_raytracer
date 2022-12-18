#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "common.hpp"
#include "ray.hpp"

namespace strangeloop {
    class Material;
    typedef struct _record {
        Point p;
        Vector3 normal;
        double t;
        bool frontFace;
        std::shared_ptr<Material> material;

        inline void faceNormal(const Ray& r, const Vector3& outwardNormal) {
            frontFace = strangeloop::dot(r.direction(), outwardNormal) < 0;
            normal = frontFace ? outwardNormal : -1*outwardNormal;
        }
    } HitRecord;

    class Hittable
    {
    public:
        virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
    };
}




#endif // HITTABLE_HPP
