//----------------------------------------------------------------
// Triangle.cpp
// Copyright: Corey Toler-Franklin, University of Florida
// 
// Triangle surface class
// This class is represented by the surface enclosed by 3 points:m_a, m_b, m_c
//----------------------------------------------------------------
#include "Triangle.h"
#include "LinearSolver.h"
#include "defs.h"



// contructor
Triangle::Triangle(STVector3 a, STVector3 b, STVector3 c, RGBR_f color)
        : Surface()
{
	m_a = a;
	m_b = b;
	m_c = c;
	m_color = color;
	m_transparent = 0;

}

Triangle::Triangle(STVector3 a, STVector3 b, STVector3 c, RGBR_f color, float transparent)
	: Surface()
{
	m_a = a;
	m_b = b;
	m_c = c;
	m_color = color;
	m_transparent = transparent;
}


// clean up
Triangle::~Triangle()
{

}

const double Tol = 1.0e-8;


//-----------------------------------------------------------------
// Uses barycentric coordinates to solve for the interscetion
// of the Ray ray with the surface in the plane of A, B, C
// Updates the variables u, v, and w with the solution if found
// Returns true if found, otherwise false
//-----------------------------------------------------------------
bool Triangle::IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, 
	                              double& beta, double& gamma, double& t)
{
	LinearSolver L;
	bool bFoundSolution = false;

	double u, v, w;
	// TO DO: Proj2 raytracer
	//          - Solve for intersections.
	// 1. Use barycentric coordinates and linear equations to solve for intersections
	// 2. If a solution is found return true, otherwise, return false
	// 3. If a solution is found, t, beta and gamma are updated; otherwise they are useless
	//------------------------------------------------

	double dx = STVector3::Dot(ComputeNormalVector(), A);
	double dy = STVector3::Dot(ComputeNormalVector(), B);
	double dz = STVector3::Dot(ComputeNormalVector(), C);
	
	if (L.Run_method2(
		A.x - B.x, A.y - B.y, A.z - B.z,
		A.x - C.x, A.y - C.y, A.z - C.z,
		dx, dy, dz,
		A.x - ray.Origin().x, A.y - ray.Origin().y, A.z - ray.Origin().z,
		beta, gamma, t))
	{
		bFoundSolution = true;
	}
	//------------------------------------------------------


    return(bFoundSolution);
}


//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// If an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Triangle::FindIntersection (Ray ray, Intersection *pIntersection)
{
    bool bFound = false;
	float hit, beta, gamma;
	double hit1,b,g;
	// TO DO: Proj2 raytracer
	//          - Find Intersections.
	// 1. Find intersections with this object along the Ray ray
	//    Use barycentric coordinates and linear equations
	// 2. Store the results of the intersection 
	// 3. If found return true, otherwise, return false
	// NOTE: The Intersection pIntersection should store:
	// hit point, surface normal, the time t of the ray at the hit point
	// and the surface being hit
	//------------------------------------------------

	/*bFound=IntersectionSolver(ray, m_a, m_b, m_c, b, g, hit1);

	//if (hit1 < 0) return false;
	if (b < 0 || b>1-g) return false;
	if (g < 0 || g>1) return false;
	*/
	
	STVector3 N = ComputeNormalVector();

	float denom = STVector3::Dot(N, N);
	float d = STVector3::Dot(N, m_a);
	float NdotRay = STVector3::Dot(N, ray.Direction());
	
	if (fabs(NdotRay) < Tol) return bFound;

	hit = STVector3::Dot(N, ray.Origin()) + d;
	if (hit < 0) return bFound;

	pIntersection->point = ray.Origin() + ray.Direction() * hit;
	pIntersection->normal = N;

	STVector3 Check;

	STVector3 edge0 = m_c - m_b;
	STVector3 eP0 = pIntersection->point - m_b;
	Check = STVector3::Cross(edge0, eP0);

	if (STVector3::Dot(N, Check) < 0) return bFound;

	STVector3 edge1 = m_a - m_c;
	STVector3 eP1 = pIntersection->point - m_c;
	Check = STVector3::Cross(edge1, eP1);

	if (beta = STVector3::Dot(N, Check) < 0) return bFound;

	STVector3 edge2 = m_b - m_a;
	STVector3 eP2 = pIntersection->point - m_a;
	Check = STVector3::Cross(edge2, eP2);

	if (gamma = STVector3::Dot(N, Check) < 0) return bFound;
	
	//------------------------------------------------------
	beta /= denom;
	gamma /= denom;

	bFound = true;
    return(bFound);
}

//-------------------------------------------------
// Computes the normal vector
//-------------------------------------------------
STVector3 Triangle::ComputeNormalVector(void)
{
    STVector3 normal;
	STVector3 V =  m_b - m_a;
	STVector3 W =  m_c - m_a;
    // TO DO: Proj2 raytracer
    // - Compute the surface normal.
    // 1. Compute the surface surface normal to the
    // plane whose points are m_a, m_b, and m_c
    //------------------------------------------------
	normal = STVector3::Cross(V, W);
	normal.Normalize();
	//---------------------------------------------------
    return(normal);
}


