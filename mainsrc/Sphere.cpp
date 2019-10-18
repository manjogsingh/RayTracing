//----------------------------------------------------------------
// Sphere.cpp
//----------------------------------------------------------------
#include "Sphere.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "defs.h"

// constructor
Sphere::Sphere(float x, float y, float z, RGBR_f color, float radius)
	:Surface()
{
	m_center = STVector3(x,y,z);
	m_color = color;
	m_radius = radius;
	m_transparent = 0;
}

Sphere::Sphere(float x, float y, float z, RGBR_f color, float radius, float transparent)
	: Surface()
{
	m_center = STVector3(x, y, z);
	m_color = color;
	m_radius = radius;
	m_transparent = transparent;
}


// clean up here
Sphere::~Sphere()
{

}


//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// if it an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Sphere::FindIntersection(Ray ray, Intersection *pIntersection) 
{

    bool bFound = false;

	// TO DO: Proj2 raytracer
	// 1. Find intersections with this object along the Ray ray
	// 2. Store the results of the intersection 
	// 3. if found and return true, otherwise, return false
	// NOTE: The IntersectionPoint pIntersection should store:
	// hit point, surface normal, the time t of the ray at the hit point
	// and the surface being hit
	//------------------------------------------------
	//Solve t^2(d.d)+2d(o-p)t+(o-p).(o-p)-r^2=0

	STVector3 L = ray.Origin() - m_center;

	//det = b.b-4ac
	float a = STVector3::Dot(ray.Direction(), ray.Direction());
	float b = 2 * STVector3::Dot(L, ray.Direction());
	float c = STVector3::Dot(L, L) - m_radius * m_radius;
	float det = b * b - (4 * a * c);

	float hit1, hit2;

	if (det < 0)
	{
		bFound = false;
		return bFound;
	}
	else if (det == 0)
	{
		bFound = true;
		hit1 = hit2 = -0.5 * b / a;
	}
	else
	{
		bFound = true;
		hit1 = 0.5 * (-b + sqrt(det)) / a;
		hit2 = 0.5 * (-b - sqrt(det)) / a;
	}

	if (bFound)
	{
		if (hit1 > hit2) std::swap(hit1, hit2);
		if (hit1 < 0)
		{
			hit1 = hit2;
			if (hit1 < 0)
			{
				bFound = false;
				return bFound;
			}
		}
	}
	pIntersection->point = ray.Origin() + ray.Direction() * hit1;
	pIntersection->normal = pIntersection->point - m_center;
	pIntersection->normal.Normalize();
	pIntersection->surface = this;
	pIntersection->viewDirection = -ray.Direction();
	//-------------------------------------------------
   return bFound;
}


// Compare sphere
bool Sphere::CompareTo(Sphere sphere)
{
	// If spheres share the same center cooridnates and radius
	// We consider the the same
	return (this->m_center.x == sphere.m_center.x &&
			this->m_center.y == sphere.m_center.y &&
			this->m_center.z == sphere.m_center.z &&
			this->m_radius == sphere.m_radius);
}



