#pragma once
#include <math.h> 

#ifndef VEC3_H
#define VEC3_H
struct Vec3 {
    double x;
    double y;
    double z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3 operator+(Vec3 const& a) const{
        return Vec3(x + a.x, y + a.y, z + a.z);
    }
    Vec3 operator-(Vec3 const& a) const{
        return Vec3(x - a.x, y - a.y, z - a.z);
    }
    double operator*(Vec3 const& a) const{ // dot product 
        return (x * a.x + y * a.y + z * a.z);
    }
    Vec3 operator%(Vec3 const& a) const{ // cross product 
        return Vec3(y * a.z - a.y * z, a.x * z - x * a.z, x * a.y - a.x * y);
    }
    Vec3 operator*(double const& a) const{
        return Vec3(x * a, y * a, z * a);
    }

    double lengthSquared(){
        return (x*x + y*y + z*z);
    }

    double length(){
        return sqrt(lengthSquared());
    }   

    Vec3 normalize(){
        double l = this->length();
        return this->operator*(1 / l);
    }

    Vec3 matrixMult(Vec3 col1, Vec3 col2, Vec3 col3) {
        Vec3 row1 = Vec3(col1.x, col2.x, col3.x);
        Vec3 row2 = Vec3(col1.y, col2.y, col3.y);
        Vec3 row3 = Vec3(col1.z, col2.z, col3.z);
        return Vec3(row1 * (*this), row2 * (*this), row3 * (*this));
    }
};
#endif