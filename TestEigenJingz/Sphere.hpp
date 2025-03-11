#pragma once

#include "Object.hpp"
#include "Vector.hpp"

class Sphere : public Object
{
public:
    Sphere(const Vector3f& c, const float& r)
        : center_world(c)
        , radius(r)
        , radius2(r * r)
    {}

    //世界坐标
    bool intersect(const Vector3f& orig_world, const Vector3f& dir_world, float& tnear, uint32_t&, Vector2f&) const override
    {
        // analytic solution
        Vector3f L = orig_world - center_world;
        float a = dotProduct(dir_world, dir_world);
        float b = 2 * dotProduct(dir_world, L);
        float c = dotProduct(L, L) - radius2;
        float t0, t1;
        if (!solveQuadratic(a, b, c, t0, t1))
            return false;
        if (t0 < 0)
            t0 = t1;
        if (t0 < 0)
            return false;
        tnear = t0;

        return true;
    }

    void getSurfaceProperties(const Vector3f& P, const Vector3f&, const uint32_t&, const Vector2f&,Vector3f& N, Vector2f&) const override
    {
        N = normalize(P - center_world);
    }

    Vector3f center_world;//世界坐标
    float radius, radius2;
};
