#include "../include/raytracer.h"


int main()
{
	std::vector<Sphere> spheres;
	spheres.emplace_back(Sphere({ 0, 0, -3 }, 1));

	raytracer::render(spheres);

	return 0;
}