cmake_minimum_required(VERSION 3.5)

project(basic_raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    basic_raytracer
    main.cpp
    common.hpp
    vector3.hpp vector3.cpp
    ray.hpp ray.cpp
    hittable.hpp
    hittablelist.hpp hittablelist.cpp
    sphere.hpp sphere.cpp
    camera.hpp camera.cpp
    material.hpp
    Lambertian.hpp
    metal.hpp
    dielectric.hpp
    aabb.hpp aabb.cpp
    image.hpp image.cpp
)

install(TARGETS basic_raytracer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
