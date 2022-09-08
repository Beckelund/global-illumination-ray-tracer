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


private:
	double r;
	double g;
	double b;
};
#endif