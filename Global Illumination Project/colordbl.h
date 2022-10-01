#pragma once

#ifndef COLORDBL_H
#define COLORDBL_H
class ColorDBL
{
public:
	ColorDBL();
	ColorDBL(double r, double g, double b);

	ColorDBL operator+(ColorDBL const a);
	ColorDBL operator*(ColorDBL const a);
	ColorDBL operator*(double const d);
	
	double getR() const;
	double getG() const;
	double getB() const;

	void setR(double inR) { r = inR; };
	void setG(double inG) { g = inG; };
	void setB(double inB) { b = inB; };

private:
	double r;
	double g;
	double b;
};
#endif