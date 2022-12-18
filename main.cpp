#include <iostream>
#include <cmath>
#include "ray.hpp"
#include "hittablelist.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "Lambertian.hpp"
#include "metal.hpp"
#include "dielectric.hpp"

namespace strangeloop {

}

using namespace std;
using strangeloop::Vector3;
using strangeloop::Color;
using strangeloop::Point;
using strangeloop::Ray;
using strangeloop::HittableList;
using strangeloop::Hittable;
using strangeloop::HitRecord;
using strangeloop::Sphere;
using strangeloop::Camera;

double hitTest(const Point& center, double radius, const Ray& r) {
    Vector3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b * half_b - a*c;
    // If discriminant is zero -> we have exactly one solution.(tangent)
    // If discriminant > zero -> we have two solutions.(passes through sphere)
    // If discriminant < zero -> ray does not intersect the sphere.
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant))/a;
    }
}

Color ray_color(const Ray& r) {
    auto t = hitTest(Point(0,0,-1),0.5,r);
    if (t > 0.0) {
        Vector3 normal = strangeloop::unit_vector(r.at(t) - Vector3(0,0,-1));
        return 0.5*Color(normal[0] + 1,normal[1] + 1,normal[2]+1);
    }
    Vector3 unitDir = strangeloop::unit_vector(r.direction());
    t = 0.5*(unitDir[1] + 1.0);
    return (1.0 - t)*Color(1.0,1.0,1.0) + t * Color(0.5,0.7,1.0);
}

Color ray_color(const Ray& r, const Hittable& world, int depth) {
    HitRecord rec;
    if (depth <= 0) {
        return Color(0,0,0);
    }
    if (world.hit(r,0.001,INF,rec)) { // <- optimize this loop
        Ray scattered;
        Color attenuation;
        if (rec.material->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
    }
    Vector3 unitDir = strangeloop::unit_vector(r.direction());
    auto t = 0.5*(unitDir[1] + 1.0);
    return (1.0 - t)*Color(1.0,1.0,1.0) + t * Color(0.5,0.7,1.0);
}

void writeColor(std::ostream& out, Color color, int samplesPerPixel) {
    auto r = color[0];
    auto g = color[1];
    auto b = color[2];

    auto scale = 1.0 / samplesPerPixel;
    r  = sqrt(scale * r);
    g  = sqrt(scale * g);
    b  = sqrt(scale * b);

    out << static_cast<int>(256 * strangeloop::clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * strangeloop::clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * strangeloop::clamp(b, 0.0, 0.999)) << std::endl;
}

HittableList random_scene() {
    HittableList world;
    auto material_ground = std::make_shared<strangeloop::Lambertian>(Color(0.5,0.5,0.5));
    world.add(make_shared<Sphere>(Point(0,-1000,0),1000,material_ground));

    for (int a = -3; a < 3; a++) {
        for (int b = -3; b < 3; b++) {
            auto choose = strangeloop::randomDouble(0,1);
            Point center(a + 0.9*strangeloop::randomDouble(0,1),0.2,b + 0.9*strangeloop::randomDouble(0,1));
            if ((center - Point(4,0.2,0)).length() > 0.9) {
                std::shared_ptr<strangeloop::Material> material;
                if (choose < 0.8) {
                    // diffuse
                    auto albedo = Color::random();
                    material = make_shared<strangeloop::Lambertian>(albedo);
                    world.add(make_shared<strangeloop::Sphere>(center, 0.2, material));
                } else if (choose < 0.95) {
                    // metal
                    auto albedo = Color::random()*Color::random();
                    material = make_shared<strangeloop::Metal>(albedo);
                    world.add(make_shared<strangeloop::Sphere>(center, 0.2, material));
                } else {
                    // Glass
                    material = make_shared<strangeloop::Dielectric>(1.5);
                    world.add(make_shared<strangeloop::Sphere>(center, 0.2, material));
                }
            }
        }
    }

    auto mat1 = make_shared<strangeloop::Dielectric>(1.5);
    world.add(make_shared<strangeloop::Sphere>(Point(0,1,0), 1, mat1));

    auto mat2 = make_shared<strangeloop::Lambertian>(Color(0.4,0.2,0.1));
    world.add(make_shared<strangeloop::Sphere>(Point(-4,1,0), 1, mat2));

    auto mat3 = make_shared<strangeloop::Metal>(Color(0.7,0.6,0.5));
    world.add(make_shared<strangeloop::Sphere>(Point(4,1,0), 1, mat3));

    return world;
}



int main()
{
    // Image in wide format
    auto aspectRatio = 3.0/2.0;
    int imgWidth = 1200;
    int imgHeight = static_cast<int>(imgWidth/aspectRatio);
    const int maxDepth = 5;

    // Camera and viewport setup
    Point lookFrom(13,2,3);
    Point lookAt(0,0,0);
    Vector3 vup(0,1,0);
    double aperture = 0.1;
    double focusDist = 10.0;
    Camera cam(lookFrom, lookAt, vup, 20.0, aspectRatio, aperture, focusDist);
    const int samplesPerPixel = 10;

    // World
    auto world = random_scene();

    std::cout << "P3" << endl;
    std::cout << imgWidth << " " << imgHeight << endl;
    std::cout << "255" << endl;

    for(int j = imgHeight - 1; j >= 0; j--)
    {
        std::cerr << "\rNo. of scanlines rendered: " << floor(((imgHeight - j)/imgHeight) * 100) << " %" << flush;
        for(int i = 0; i < imgWidth; i++)
        {
            Color pixelColor(0,0,0);
            for(int s = 0; s < samplesPerPixel; s++) {
                auto u = (i + strangeloop::randomDouble(0.0,1.0)) / (imgWidth - 1);
                auto v = (j + strangeloop::randomDouble(0.0,1.0)) / (imgHeight - 1);
                Ray r = cam.getRay(u,v);
                pixelColor += ray_color(r, world, maxDepth);
            }
            writeColor(std::cout, pixelColor,samplesPerPixel);
        }
    }
    return 0;
}
