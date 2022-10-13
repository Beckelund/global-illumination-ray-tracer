#include "ray.h"
#include "object.h"
#include "surface.h"
#include "polygon.h"
#include "sphere.h"
#include "arealight.h"

Ray::Ray() : pos(Vec3(0, 0, 0)), dir(Vec3(1, 0, 0)), next(nullptr), prev(nullptr), hitSurface(nullptr) {
	t = DBL_MAX;
}

Ray::Ray(Vec3 position = Vec3(0, 0, 0), Vec3 direction = Vec3(1, 0, 0)) : pos(position), dir(direction), next(nullptr), prev(nullptr), hitSurface(nullptr) {
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

Surface* Ray::getStarSurface() const
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

ColorDBL Ray::castRay(std::vector<Object>& objs, std::vector<AreaLight>& lights)
{
	//Check for intersections
	for (int i = 0; i < objs.size(); i++)
	{
		objs[i].Intersection(*this);
	}

	if (hitSurface == nullptr) return ColorDBL(0.0, 0.0, 0.0); 

	//Cast next ray
	next = hitSurface->getMaterial().BRDF(hitSurface->getNormal(*this), *this);
	
	//Direct light contribution
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
						+ light.getColor() * (light.getArea() * light.getIrradiance() / (double)n_samples)
						* (rflct / 3.14) * ((lightRay.getDirection()*-1) * nrml)*(1/(lightRay.t * lightRay.t));
				}
			}
		}
	}

	//Calculate color to return
	ColorDBL result = hitSurface->getMaterial().getColor();
	result = result * lightContribution;
	if (next != nullptr) {
		ColorDBL MCColor = next->castRay(objs, lights);
		result = result + MCColor * hitSurface->getMaterial().getColor();
	}
	
	return result;
}
