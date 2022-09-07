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

    Vec3 operator+(Vec3 const& a) {
        return Vec3(x + a.x, y + a.y, z + a.z);
    }
    Vec3 operator-(Vec3 const& a) {
        return Vec3(x - a.x, y - a.y, z - a.z);
    }
    double operator*(Vec3 const& a) {
        return (x * a.x + y * a.y + z * a.z);
    }
    Vec3 operator%(Vec3 const& a) {
        return Vec3(y * a.z - a.y * z, a.x * z - x * a.z, x * a.y - a.x * y);
    }
    Vec3 operator*(double const& a){
        return Vec3(x * a, y * a, z * a);
    }

    double lengthSquared(){
        return (x*x + y*y + z*z);
    }

    double length(){
        return sqrt(lengthSquared());
    }   

    vec3 normaliz(){
        double l = this->length();
        reurn this* (1 / l);

    } 
};
#endif