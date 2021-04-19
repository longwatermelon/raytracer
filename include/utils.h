#pragma once
#include <cmath>

#define WIDTH 1000
#define HEIGHT 1000


class Vec3f
{
public:
	Vec3f()
		: m_x(0.f), m_y(0.f), m_z(0.f) {}

	Vec3f(float x, float y, float z)
		: m_x(x), m_y(y), m_z(z) {}

	Vec3f normalize() const
	{
		float len = std::sqrtf(m_x * m_x + m_y * m_x + m_z * m_z);

		return { m_x / len, m_y / len, m_z / len };
	}

	
	Vec3f operator+(const Vec3f& v) const
	{
		return { m_x + v.x(), m_y + v.y(), m_z + v.z() };
	}

	Vec3f operator+(float f) const
	{
		return { m_x + f, m_y + f, m_z + f };
	}

	Vec3f operator-(const Vec3f& v) const
	{
		return *this + Vec3f(-v.x(), -v.y(), -v.z());
	}

	Vec3f operator-(float f) const
	{
		return *this + -f;
	}


	float operator*(const Vec3f& v) const
	{
		return m_x * v.x() + m_y * v.y() + m_z * v.z();
	}

	Vec3f operator*(float f) const
	{
		return { m_x * f, m_y * f, m_z * f };
	}

	float x() const { return m_x; }
	float y() const { return m_y; }
	float z() const { return m_z; }

private:
	float m_x, m_y, m_z;
};