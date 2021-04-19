#include "../include/raytracer.h"
#include "../include/utils.h"
#include <vector>
#include <fstream>
#include <iostream>


void raytracer::render(const std::vector<Sphere> spheres)
{
	std::vector<Vec3f> frame_buf(WIDTH * HEIGHT);

	std::ofstream ofs("output.ppm", std::ofstream::trunc | std::ofstream::out);
	ofs << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";

	float fov = 1.f;

	std::cout << "casting rays\n";

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			float ha = ((float)x / (float)WIDTH) * fov - (fov / 2.f);
			float va = ((float)y / (float)HEIGHT) * fov - (fov / 2.f);

			float px = sinf(ha);
			float py = sinf(va);

			Vec3f dir = Vec3f(px, py, -1).normalize();
			frame_buf[y * WIDTH + x] = cast_ray(Vec3f(0, 0, 0), dir, spheres);
		}
	}

	std::cout << "writing to file\n";

	for (int i = 0; i < WIDTH * HEIGHT; ++i)
	{
		int x = (int)(255.f * frame_buf[i].x());
		int y = (int)(255.f * frame_buf[i].y());
		int z = (int)(255.f * frame_buf[i].z());

		ofs << (x > 255 ? 255 : x) << ' '
			<< (y > 255 ? 255 : y) << ' '
			<< (z > 255 ? 255 : z) << '\n';
	}

	std::cout << "done\n";

	ofs.close();
}


Vec3f raytracer::cast_ray(const Vec3f& orig, const Vec3f& dir, const std::vector<Sphere>& spheres)
{
	float t;

	for (auto& s : spheres)
	{
		if (!s.ray_intersect(orig, dir, t))
		{
			return Vec3f(0.2f, 0.7f, 0.8f);
		}
	}

	return Vec3f(0.9f, 0.1f, 0.5f);
}