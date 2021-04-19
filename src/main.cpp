#include "../include/raytracer.h"


int main()
{
	Material ivory({ 0.4, 0.4, 0.3 });
	Material red_rubber({ 0.3, 0.1, 0.1 });

	std::vector<Sphere> spheres;
	spheres.emplace_back(Sphere({ 0, 0, -3 }, 1, ivory));
	spheres.emplace_back(Sphere({ 0, 0, -2 }, 0.5, red_rubber));

	raytracer::render(spheres);

	return 0;
}