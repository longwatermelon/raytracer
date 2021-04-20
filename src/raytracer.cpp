#include "../include/raytracer.h"
#include "../include/utils.h"
#include <vector>
#include <fstream>
#include <iostream>


void raytracer::render(const std::vector<Sphere>& spheres, const std::vector<Light>& lights)
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

			Vec3f dir = Vec3f(px, py, 1).normalize();
			frame_buf[y * WIDTH + x] = cast_ray(Vec3f(0, 0, 0), dir, spheres, lights);
		}
	}

	std::cout << "writing to file\n";

	for (int i = 0; i < WIDTH * HEIGHT; ++i)
	{
		int x = (int)(255.f * std::max(0.f, std::min(1.f, frame_buf[i].x())));
		int y = (int)(255.f * std::max(0.f, std::min(1.f, frame_buf[i].y())));
		int z = (int)(255.f * std::max(0.f, std::min(1.f, frame_buf[i].z())));

		ofs << x << ' ' << y << ' ' << z << "\n";
	}

	std::cout << "done\n";

	ofs.close();
}


Vec3f raytracer::cast_ray(const Vec3f& orig, const Vec3f& dir, const std::vector<Sphere>& spheres, const std::vector<Light>& lights)
{
	Vec3f intersection, normal;
	Material mat;

	if (!scene_intersect(orig, dir, spheres, intersection, normal, mat))
	{
		return Vec3f(0.2, 0.7, 0.8);
	}

	float diffuse_light_intensity = 0.f;

	for (int i = 0; i < lights.size(); ++i)
	{
		Vec3f light_dir = (lights[i].pos() - intersection).normalize();
		diffuse_light_intensity += lights[i].intensity() * (light_dir * normal);
	}

	return mat.diffuse_color() * diffuse_light_intensity;
}


bool raytracer::scene_intersect(const Vec3f& orig, const Vec3f& dir, const std::vector<Sphere>& spheres, Vec3f& hit, Vec3f& norm, Material& m)
{
	float nearest = std::numeric_limits<float>::max();

	for (int i = 0; i < spheres.size(); ++i)
	{
		float dist;
		if (spheres[i].ray_intersect(orig, dir, dist) && dist < nearest)
		{
			nearest = dist;
			hit = orig + dir * dist;
			norm = (hit - spheres[i].center()).normalize();
			m = spheres[i].mat();
		}
	}

	return nearest < 1000.f;
}