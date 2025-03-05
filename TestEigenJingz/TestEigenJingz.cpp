// TestEigenJingz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<cmath>
#include <iostream>
#include "/WorkSpace/Eigen/Core"
#include "/WorkSpace/Eigen/Dense"

#include "Scene.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Renderer.hpp"

int main()
{
    Scene scene(1280, 960);

    auto sphere1 = std::make_unique<Sphere>(Vector3f(-1, 0, -12), 2);
    sphere1->materialType = DIFFUSE_AND_GLOSSY;
    sphere1->diffuseColor = Vector3f(0.6, 0.7, 0.8);

    auto sphere2 = std::make_unique<Sphere>(Vector3f(0.5, -0.5, -8), 1.5);
    sphere2->materialType = REFLECTION_AND_REFRACTION;
    sphere2->ior = 1.5;

    scene.Add(std::move(sphere1));
    scene.Add(std::move(sphere2));

    //OpenGL使用右手环绕方向（逆时针）
    //                     0,           1,        2,           3,
    Vector3f verts[4] = { {-5,-3,-6}, {5,-3,-6}, {5,-3,-16}, {-5,-3,-16} };
    uint32_t vertIndex[6] = { 0, 1, 3, 1, 2, 3 };
    Vector2f st[4] = { {0, 0}, {1, 0}, {1, 1}, {0, 1} };
    auto mesh = std::make_unique<MeshTriangle>(verts, vertIndex, 2, st);
    mesh->materialType = DIFFUSE_AND_GLOSSY;

    scene.Add(std::move(mesh));
    scene.Add(std::make_unique<Light>(Vector3f(-20, 70, 20), 0.5));
    scene.Add(std::make_unique<Light>(Vector3f(30, 50, -12), 0.5));

    Renderer r;
    r.Render(scene);

    return 0;
}
