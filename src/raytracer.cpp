#include "raytracer.h"
#include "utils.h"
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

	// phong reflection
	// ambient + diffuse + specular

	float diffuse_light_intensity = 0.f, specular_light_intensity = 0.f;

	for (auto& light : lights)
	{
		Vec3f light_dir = (light.pos() - intersection).normalize();

		Vec3f shadow_intersection, shadow_norm;
		Material tmp;

		Vec3f shadow_orig = intersection/* + normal * 0.1f*/;

		if (scene_intersect(shadow_orig, light_dir, spheres, shadow_intersection, shadow_norm, tmp) &&
			(shadow_intersection - shadow_orig).length() < (light.pos() - shadow_orig).length())
			continue;

		diffuse_light_intensity += light.intensity() * std::max(0.f, light_dir * normal);
		Vec3f r = light_dir - normal * 2 * (normal * light_dir);
		specular_light_intensity += std::powf(std::max(0.f, r * intersection.normalize()), mat.specular_exp());
	}

	return mat.diffuse_color() * diffuse_light_intensity * mat.reflectiveness()[0] + specular_light_intensity * mat.reflectiveness()[1];
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
