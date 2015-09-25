#pragma once


class Object;
class Ray;

struct Intersection {
    Intersection(double dist, Ray* ray, Object* object): dist(dist), ray(ray), object(object) {};
    double dist;
    Object* object;
    Ray* ray;
};
