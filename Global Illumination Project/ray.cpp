#include "ray.h"
#include "object.h"
#include "surface.h"
#include "polygon.h"
#include "sphere.h"
#include "arealight.h"
#include "photonmap.h"

Ray::Ray() : pos(Vec3(0, 0, 0)), dir(Vec3(1, 0, 0)), next(nullptr), prev(nullptr), hitSurface(nullptr), originSurface(nullptr) {
	t = DBL_MAX;
}

Ray::Ray(Vec3 position = Vec3(0, 0, 0), Vec3 direction = Vec3(1, 0, 0)) : pos(position), dir(direction), next(nullptr), prev(nullptr), hitSurface(nullptr), originSurface(nullptr) {
	t = DBL_MAX;
}

Ray::Ray(Vec3 position, Vec3 direction, Ray* previous) : Ray(position, direction) {
	prev = previous;
	originSurface = previous->hitSurface;
	t = DBL_MAX;
}

Ray::~Ray()
{
	delete next;
	next = nullptr;
	prev = nullptr;
	hitSurface = nullptr;
	originSurface = nullptr;
}

Vec3 Ray::getDirection() const {
	return dir;
}

Vec3 Ray::getOrigin() const {
	return pos;
}

Vec3 Ray::getPoint(double t) const {
	return pos + dir * t;
}

Vec3 Ray::getEnd() const {
	return pos + dir * t;
}

Surface* Ray::getStartSurface() const
{
	return originSurface;
}

Surface* Ray::getHitSurface() const
{
	return hitSurface;
}

void Ray::setHit(double t, Surface* surface)
{
	if (t < this->t) {
		this->t = t;
		hitSurface = surface;
	}
}

ColorDBL Ray::castRay(std::vector<Object>& objs, std::vector<AreaLight>& lights, PhotonMap& photonmap, bool has_hit_lambertian)
{
	//Check for intersections
	for (int i = 0; i < objs.size(); i++)
	{
		objs[i].Intersection(*this);
	}

	if (hitSurface == nullptr) return ColorDBL(0.0, 0.0, 0.0); 
	//Photon Mapping support:
	double max_radius = 0.1;
	double totalFlux = 0;
	
	if (has_hit_lambertian == false && hitSurface->getMaterial().getType() == Material::Type::lambertian) {
		has_hit_lambertian = true;
		//std::cout << photonmap.photons.size() << std::endl;
		std::vector<Photon> photons = photonmap.getPhotons(getEnd(), max_radius);
		
		for (Photon& p : photons) {
			double distance = (p.getPosition() - getEnd()).length();
			totalFlux += p.getFlux() * (1 / distance);
		}
		/*if(photons.size() > 1)
			std::cout << "photons gotten: " << photons.size() << std::endl;*/
	}		

	ColorDBL photonContribution = ColorDBL(1, 1, 1) * totalFlux *20; // TODO the 20 should not be here, 

	//View just the photonMap 
	//return photonContribution;

	//Direct light contribution
	ColorDBL lightContribution = DirectLightContribution(objs, lights);
		
	//Calculate color to return
	ColorDBL result = hitSurface->getMaterial().getColor();
	result = result * lightContribution + result * photonContribution;
	
	//Cast next ray
	next = hitSurface->getMaterial().BRDF(hitSurface->getNormal(*this), *this);
	if (next != nullptr) {
		ColorDBL MCColor = next->castRay(objs, lights, photonmap, has_hit_lambertian);
		result = result + MCColor * hitSurface->getMaterial().getColor();
	}
	
	return result;
}


ColorDBL Ray::DirectLightContribution(std::vector<Object>& objs, std::vector<AreaLight>& lights)
{
	ColorDBL lightContribution = ColorDBL(0.0, 0.0, 0.0);
	Material::Type matType = hitSurface->getMaterial().getType();
	int n_samples = 1;
	if (matType == Material::Type::lambertian) {
		for (AreaLight& light : lights) {
			for (int i = 0; i < n_samples; i++) {
				Vec3 point = light.RandomPoint();
				//Check for intersections
				Ray lightRay = Ray(point, (this->getEnd() - point).normalize());
				for (int i = 0; i < objs.size(); i++) {
					objs[i].Intersection(lightRay);
				}

				if (lightRay.hitSurface == this->hitSurface) {
					double rflct = hitSurface->getMaterial().getReflectivity();
					Vec3 nrml = hitSurface->getNormal(lightRay);

					lightContribution = lightContribution
						+ light.getColor() * (light.getArea() * light.getRadiosity() / (double)n_samples)
						* (rflct / 3.14) * ((lightRay.getDirection() * -1) * nrml) * (1 / (lightRay.t * lightRay.t));
				}
			}
		}
	}

	return lightContribution;
}

Ray* Ray::BounceSelf(std::vector<Object>& objs)
{
	for (int i = 0; i < objs.size(); i++)
	{
		objs[i].Intersection(*this);
	}

	if (hitSurface != nullptr && hitSurface->getMaterial().getType() != Material::Type::lambertian)
	{
		next = hitSurface->getMaterial().BRDF(hitSurface->getNormal(*this), *this);
		return next->BounceSelf(objs);
	}

	if (hitSurface != nullptr && hitSurface->getMaterial().getType() == Material::Type::lambertian)
	{
		return this;
	}

	//Ray hits outside the scene or something else
	return nullptr;
}
