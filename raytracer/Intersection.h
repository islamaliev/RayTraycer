#pragma once


class Object;
class Ray;

struct Intersection {
    Intersection(float dist, Ray* ray, Object* object): dist(dist), ray(ray), object(object) {};
    float dist;
    Object* object;
    Ray* ray;
};
