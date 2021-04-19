#pragma once
#include "utils.h"


class Material
{
public:
	Material() = default;

	Material(const Vec3f& col)
		: m_diffuse_color(col) {}

	Vec3f diffuse_color() const { return m_diffuse_color; }

private:
	Vec3f m_diffuse_color;
};


class Sphere
{
public:
	Sphere() = default;

	Sphere(const Vec3f& c, float r, const Material& mat)
		: m_center(c), m_radius(r), m_mat(mat) {}

	bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t) const;

	Vec3f center() const { return m_center; }
	float radius() const { return m_radius; }
	Material mat() const { return m_mat; }

private:
	Vec3f m_center;
	float m_radius;

	Material m_mat;
};