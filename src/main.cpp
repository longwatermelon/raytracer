#include "../include/raytracer.h"
#include <iostream>


int main()
{
	Material ivory({ 0.4, 0.4, 0.3 });
	Material red_rubber({ 0.3, 0.1, 0.1 });

	std::vector<Sphere> spheres;
	spheres.emplace_back(Sphere({ -1.f, 0.f, 14.f }, 2.f, ivory));
	spheres.emplace_back(Sphere({ 2.f, -1.f, 11.f }, 2.f, red_rubber));
	spheres.emplace_back(Sphere({ -0.5f, -2.f, 9.f }, 1.f, ivory));

	std::vector<Light> lights;
	lights.emplace_back(Light({ -3.f, -10.f, -8.f }, 2.f));
	lights.emplace_back(Light({ -5.f, -3.f, -8.f }, 1.f));

	raytracer::render(spheres, lights);

	return 0;
}