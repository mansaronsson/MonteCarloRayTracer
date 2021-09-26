#include "Objects.h"
#include <iostream>

double Sphere::rayIntersection(Ray& ray) {

	//Intersection for spheres
	//Follows following theroey viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/

	//A = rayStart, B = rayDirection, C = sphereCenter
	//All dot products for the quadratic formula
	dvec3 dotProds;

	dotProds.x = glm::dot(ray.getDirection(), ray.getDirection());
	dotProds.y = 2.0 * glm::dot(ray.getDirection(), ray.getStart() - vec3(position));
	dotProds.z = glm::dot(ray.getStart() - vec3(position), ray.getStart() - vec3(position)) - radius * radius;

	//std::cout << "x: " << dotProds.x << "y: " << dotProds.y << "z: " << dotProds.z << std::endl;

	//The dicriminant which check for hits
	double discriminant = dotProds.y * dotProds.y - 4 * dotProds.x * dotProds.z;

	//If determinant < 0: No hit, If ==0, It scraped along the surface
	if (discriminant < EPSILON) {
		return -1.0;
	}
	else {
		double numerator = -dotProds.y + sqrt(discriminant);

		if (numerator > 0.0) { //Check if hit was behind camera, we dont want that
			return numerator / (2.0 * dotProds.x);
		}
		//Check both possibilities since its +-sqrt
		numerator = -dotProds.y - sqrt(discriminant);

		if (numerator > 0.0) {
			return numerator / (2.0 * dotProds.x);
		}
		else {
			return -1.0;
		}

	return -1.0;
	}
}

ColorDbl Sphere::getColor()
{
	return color;
}

Triangle::Triangle(const vec3& x, const vec3& y, const vec3& z, const ColorDbl& col)
	: color{ col }
{
	vertices[0] = x;
	vertices[1] = y;
	vertices[2] = z;

	normal = glm::normalize(glm::cross(z - x, y - x));
	edge1 = y - x;
	edge2 = z - x;
		
}

double Triangle::rayIntersection(Ray& ray)
{
	//M�ller-Trumbore
	vec3 T = vec3(ray.getStart() - vertices[0]);
	vec3 D = ray.getDirection();
	vec3 P = glm::cross(D, edge2);
	vec3 Q = glm::cross(T, edge1);

	vec3 hit = (1 / glm::dot(P, edge1)) * vec3(dot(Q, edge2), dot(P, T), dot(Q, D));

	if (hit.x < EPSILON || hit.y < EPSILON || hit.z < EPSILON || hit.z + hit.y > 1.0f) {
		return -1.0;
	}
	else {
		return hit.x;
	}
}

ColorDbl Triangle::getColor()
{
	return color;
}

