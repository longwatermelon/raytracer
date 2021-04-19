#pragma once
#include "utils.h"


class Sphere
{
public:
	Sphere() = default;

	Sphere(const Vec3f& c, float r)
		: m_center(c), m_radius(r) {}

	bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t) const;

private:
	Vec3f m_center;
	float m_radius;
};