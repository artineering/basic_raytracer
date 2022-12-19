#include "sphere.hpp"

using namespace strangeloop;

Sphere::Sphere()
    :_center(0,0,0),_radius(0.0)
{

}

Sphere::Sphere(Point center, double r)
    :_center(center), _radius(r)
{

}

Sphere::Sphere(Point center, double r, std::shared_ptr<Material> m)
    :_center(center), _radius(r), _material(m)
{

}

bool Sphere::hit(const strangeloop::Ray &r, double tMin, double tMax, strangeloop::HitRecord &rec) const
{
    Vector3 oc = r.origin() - _center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc,r.direction());
    auto c = oc.length_squared() - _radius*_radius;
    auto d = half_b*half_b - a*c;
    if (d < 0) {
        return false;
    }
    auto sqrtd = sqrt(d);
    auto root = (-half_b - sqrtd) / a;
    if (root < tMin || root > tMax) {
        root = -(half_b + sqrtd) / a;
        if (root < tMin || root > tMax) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vector3 normal = (rec.p - _center)/_radius;
    rec.faceNormal(r,normal);
    rec.material = _material;

    return true;
}

Point Sphere::center() const
{
    return _center;
}

double Sphere::radius() const
{
    return _radius;
}

