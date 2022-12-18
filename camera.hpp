#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "common.hpp"
#include "ray.hpp"

using strangeloop::Vector3;
using strangeloop::Point;
using strangeloop::Ray;

namespace strangeloop {
class Camera
{
public:
    Camera();
    Camera(double fov, double aspectRatio);
    Camera(Point from, Point lookAt, Vector3 vup, double fov, double ar);
    Camera(Point from, Point lookAt, Vector3 vup, double fov, double ar, double aperture, double focusDist);
    Ray getRay(double u, double v) const;
private:
    Point origin;
    Point lowerLeftCorner;
    Vector3 horz;
    Vector3 vert;
    Vector3 u,v,w;
    double lensRadius;
};
}
#endif // CAMERA_HPP
