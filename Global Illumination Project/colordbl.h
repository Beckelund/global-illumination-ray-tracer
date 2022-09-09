#pragma once

#ifndef COLORDBL_H
#define COLORDBL_H
class ColorDBL
{
public:
	ColorDBL();
	ColorDBL(double r, double g, double b);

	double getR() const;
	double getG() const;
	double getB() const;

	ColorDBL operator+(ColorDBL const a);
	ColorDBL operator*(ColorDBL const a);
	ColorDBL operator*(double const d);

private:
	double r;
	double g;
	double b;
};
#endif