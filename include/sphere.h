#pragma once
#include "utils.h"
#include <array>


class Material
{
public:
	Material() = default;

	Material(const Vec3f& col, const std::array<float, 2>& r, float exp)
		: m_diffuse_color(col), m_reflectiveness(r), m_specular_exp(exp) {}

	Vec3f diffuse_color() const { return m_diffuse_color; }
	std::array<float, 2> reflectiveness() const { return m_reflectiveness; }
	float specular_exp() const { return m_specular_exp; }

private:
	Vec3f m_diffuse_color;

	std::array<float, 2> m_reflectiveness;
	float m_specular_exp;
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