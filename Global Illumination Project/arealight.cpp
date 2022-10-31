#include "arealight.h"
#include "sphere.h"
#include <iostream>

AreaLight::AreaLight(Vec3 pos, Vec3 inV1, Vec3 inV2, ColorDBL col, double flux)
{
	position = pos;
	v1 = inV1;
	v2 = inV2;
	color = col;

	//calculate normal
	normal = (v1 % v2).normalize();

	//Calculate irradiance
	irradiance = flux / (v1 % v2).length();

	area = (v1 % v2).length();
}

Vec3 AreaLight::RandomPoint() const
{
	double r1 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	double r2 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

	return position + v1 * r1 + v2 * r2;
}

double AreaLight::CalculateFluxOnSurface(const Surface& s) const
{
	
	return 0.0;
}

double AreaLight::CalculateFluxOnSurface(const Sphere* s) const
{
	double PI = 3.14;
	
	Vec3 middle = position + v1 * (1.0 / 2.0) + v2 * (1.0 / 2.0);
	Vec3 dist = middle - s->getPosition();
	
	double Gm = Vec3(0, 0, -1.0) * (dist.normalize() * -1.0) / dist.lengthSquared();
	
	double area = Gm * PI * s->getRadius() * s->getRadius();
	
	return area * irradiance;
}

std::vector<Photon> AreaLight::GeneratePhotons(std::vector<Object>& objects, Surface* s, int n_photons) const
{
	//std::cout << "Dereferenced as a Surface" << std::endl;
	std::vector<Photon> photons;
	return photons;
}

std::vector<Photon> AreaLight::GeneratePhotons(std::vector<Object>& objects, Sphere* s, int n_photons) const
{
	//std::cout << "Dereferenced as a Sphere" << std::endl;
	std::vector<Photon> photons;

	double flux = CalculateFluxOnSurface(s) / (double) n_photons;

	for (int i = 0; i < n_photons; i++)
	{
		Vec3 start = RandomPoint();
		Vec3 dir = (s->getPosition() - start);
		
		//transformation local-world system
		Vec3 Zl = dir.normalize() * -1.0;
		Vec3 Yl = (Zl % Vec3(1, 0, 0)).normalize();
		Vec3 Xl = Yl % Zl;
		
		//Get random point on circle
		double r1 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		double r2 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		
		double theta = 2.0 * 3.14 * r1;
		double r = s->getRadius() * sqrt(r2);
		
		Vec3 pointOnCircle = Vec3(r * cos(theta), r * sin(theta), 0.0);

		//Transform to world system
		Vec3 pointOnSphere = s->getPosition() + pointOnCircle.matrixMult(Xl, Yl, Zl);
		
		//Create Ray
		Vec3 ray_dir = (pointOnSphere - start);
		ray_dir = ray_dir.normalize();
		Ray start_ray(start,ray_dir);
		
		//Trace ray to end
		Ray* end_ray = start_ray.BounceSelf(objects);

		//Create photon
		if (end_ray != nullptr)
		{
			Photon p(end_ray->getEnd(), end_ray->getDirection(), flux);
			photons.push_back(p);
		}
	}

	return photons;
}
