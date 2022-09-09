#include "colordbl.h"

ColorDBL::ColorDBL():r(0),g(0),b(0){}

ColorDBL::ColorDBL(double r, double g, double b):r(r),g(g),b(b) {}

double ColorDBL::getR() const
{
	return this->r;
}

double ColorDBL::getG() const
{
	return this->g;
}

double ColorDBL::getB() const
{
	return this->b;
}

ColorDBL ColorDBL::operator+(ColorDBL const a)
{
	return ColorDBL(r + a.r, g + a.g, b + a.b);
}

ColorDBL ColorDBL::operator*(ColorDBL const a)
{
	return ColorDBL(r * a.r, g * a.g, b * a.b);
}

ColorDBL ColorDBL::operator*(double const d)
{
	return ColorDBL(r * d, g * d, b * d);
}
