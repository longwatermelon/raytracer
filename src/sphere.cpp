#include "sphere.h"


bool Sphere::ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t) const
{
	Vec3f co = orig - m_center;

	float a = dir * dir;
	float b = co * dir * 2;
	float c = co * co - m_radius * m_radius;

	float discrim = b * b - 4 * a * c;

	if (discrim < 0) return false;

	float t1 = (-b + std::sqrtf(discrim)) / (2 * a);
	float t2 = (-b - std::sqrtf(discrim)) / (2 * a);

	// 1e-4f to count for floating point errors
	if (t1 <= 1e-4f) return false;

	if (t2 <= 1e-4f) { t = t1; }
	else { t = std::fminf(t1, t2); }

	return true;
}
