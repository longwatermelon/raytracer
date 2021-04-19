#include "../include/sphere.h"


bool Sphere::ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t) const
{
	/*
	* point on a circle represented by P
	* distance(P, m_center) = r
	* |P - m_center| = r
	* length of a vector is equivalent to the sqrt of the dot product of itself
	* sqrt((P - m_center) * (P - m_center)) = m_radius
	* 
	* (P - m_center) * (P - m_center) = m_radius^2
	* 
	* A ray can be represente
	* P = orig + t * dir
	* 
	* Substitution
	* ((orig + t * dir) - m_center) * ((orig + t * dir) - m_center) = m_radius^2
	* Let co = orig - m_center
	* (oc + t * dir) * (oc + t * dir) = m_radius^2
	* 
	* expand dot product using its distributive properties
	* (co + td) * (co) + (co + td) * (td) = m_radius^2
	* 
	* (co * co) + 2 * (co * td) + (td * td) = r^2
	* 
	* quadratic equation
	* t^2(d * d) + t(2(co * d)) + (co * co) - r^2 = 0
	* 
	* a = d * d
	* b = 2(co * d)
	* c = (co * co) - r^2
	*/

	Vec3f co = orig - m_center;

	float a = dir * dir;
	float b = co * dir * 2;
	float c = co * co - m_radius * m_radius;

	// sqrt(b^2 - 4ac) in quadratic equation, if b^2 - 4ac is negative the ray has missed the sphere
	float discrim = b * b - 4 * a * c;

	if (discrim < 0) return false;

	float t1 = (-b + std::sqrtf(discrim)) / (2 * a);
	float t2 = (-b - std::sqrtf(discrim)) / (2 * a);

	t = std::fminf(t1, t2); // nearest intersection
	return true;
}