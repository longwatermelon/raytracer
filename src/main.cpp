#include "raytracer.h"
#include <iostream>


int main()
{
	Material ivory({ 0.4f, 0.4f, 0.3f }, { 0.6f, 0.8f }, 50.f);
	Material red_rubber({ 0.3f, 0.1f, 0.1f }, { 0.9f, 0.1f }, 10.f);

	std::vector<Sphere> spheres;
	spheres.emplace_back(Sphere({ -1.f, 0.f, 14.f }, 2.f, ivory));
	spheres.emplace_back(Sphere({ 2.f, -1.f, 11.f }, 2.f, red_rubber));
	spheres.emplace_back(Sphere({ -0.5f, -2.f, 9.f }, 1.f, ivory));
	//spheres.emplace_back(Sphere({ 1.f, -1.f, 6.f }, 0.4f, red_rubber));

	std::vector<Light> lights;
	lights.emplace_back(Light({ -3.f, -10.f, 6.f }, 2.5f));
	lights.emplace_back(Light({ 2.f, -2.f, 2.f }, 3.f));

	raytracer::render(spheres, lights);

	return 0;
}
