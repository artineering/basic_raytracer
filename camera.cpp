#include "camera.hpp"

using namespace strangeloop;

strangeloop::Camera::Camera()
    :origin(0,0,0)
{
    auto aspectRatio = 16.0 / 9.0;
    auto viewPortHeight = 2.0;
    auto viewPortWidth = viewPortHeight * aspectRatio;
    auto focalLength = 1.0;

    horz = Vector3(viewPortWidth,0.0,0.0);
    vert = Vector3(0.0,viewPortHeight,0.0);
    lowerLeftCorner = origin - horz/2 - vert/2 - Vector3(0,0,focalLength);
}

Camera::Camera(double fov, double aspectRatio)
{
    auto theta = strangeloop::degsToRads(fov);
    auto h = tan(theta / 2);
    auto viewPortHeight = 2.0 * h;
    auto viewPortWidth = viewPortHeight * aspectRatio;

    auto focalLength = 1.0;

    horz = Vector3(viewPortWidth,0.0,0.0);
    vert = Vector3(0.0,viewPortHeight,0.0);
    lowerLeftCorner = origin - horz/2 - vert/2 - Vector3(0,0,focalLength);
}

Camera::Camera(Point from, Point lookAt, Vector3 vup, double fov, double ar)
{
    auto theta = strangeloop::degsToRads(fov);
    auto h = tan(theta / 2);
    auto viewPortHeight = 2.0 * h;
    auto viewPortWidth = viewPortHeight * ar;

    auto w = unit_vector(from - lookAt);
    auto u = unit_vector(cross(vup,w));
    auto v = cross(w,u);

    origin = from;
    horz = viewPortWidth * u;
    vert = viewPortHeight * v;
    lowerLeftCorner = origin - horz/2 - vert/2 - w;
}

Camera::Camera(Point from, Point lookAt, Vector3 vup, double fov, double ar, double aperture, double focusDist)
{
    auto theta = strangeloop::degsToRads(fov);
    auto h = tan(theta / 2);
    auto viewPortHeight = 2.0 * h;
    auto viewPortWidth = viewPortHeight * ar;

    w = unit_vector(from - lookAt);
    u = unit_vector(cross(vup,w));
    v = cross(w,u);

    origin = from;
    horz = focusDist * viewPortWidth * u;
    vert = focusDist * viewPortHeight * v;
    lowerLeftCorner = origin - horz/2 - vert/2 - focusDist*w;

    lensRadius = aperture/2;
}

Ray strangeloop::Camera::getRay(double s, double t) const
{
    Vector3 rd = lensRadius * randomInUnitDisk();
    Vector3 offset = (u * rd[0]) + (v * rd[1]);
    auto direction = lowerLeftCorner + s*horz + t*vert - origin - offset;
    return Ray(origin + offset, direction);
}
