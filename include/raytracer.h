#pragma once
#include "../include/sphere.h"
#include <vector>


namespace raytracer
{
	void render(const std::vector<Sphere> spheres);

	Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, const std::vector<Sphere>& spheres);

	bool scene_intersect(const Vec3f& orig, const Vec3f& dir, const std::vector<Sphere>& spheres, Vec3f& hit, Vec3f& norm, Material& m);
}