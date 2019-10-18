//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Scene.cpp
// Stores all the objects - lights, camera and surfaces for setting up the scene.
//------------------------------------------------------------------------------


#include "Scene.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "Intersection.h"
#include "Surface.h"
#include "Light.h"
#include "Sphere.h"

// contructor
Scene::Scene(void)
    : m_background(RGBR_f(1, 1, 1, 1))
 {
    // init camera
    m_pCamera = new Camera();

}


// destructor
Scene::~Scene()
{

}

// set the background color
void Scene::SetBackgroundColor(RGBR_f color)
{
    m_background = color;
}

// return the background color
RGBR_f Scene::GetBackgroundColor(void)
{
    return(m_background);
}


// ass a light 
void Scene::AddLight(Light lightin)
{
    m_lights.push_back(lightin);
}


// returns the list of lights
LightList Scene::GetLightList(void)
{
	return(m_lights);
}

// add an object
void Scene::AddSurface(Surface *pSurfacein)
{
    m_surfaceList.push_back(pSurfacein);
}


// return the camera
Camera *Scene::GetCamera(void)
{
    return(m_pCamera);
}



//-----------------------------------------------------
// Find the intersection of the ray with objects in the scene
// Return the closest intersection
//-----------------------------------------------------
int Scene::FindClosestIntersection(Ray ray, Intersection *pIntersection)
{
    int numPoints = 0;

	//Must set it to false for further use
    numPoints = FindIntersection(ray, pIntersection);
    return(numPoints);
}


//-----------------------------------------------------
// Find the intersection of the ray with objects in the scene.
// Check for the closest intersections and retun the number
// of close intersections found.
// Returns the pIntersection  data for the closest intersection.
//------------------------------.-----------------------
int Scene::FindIntersection(Ray ray, Intersection *pIntersection)
{
    bool bFound = false; // true if an intersection is found
    int numPoints = 0;   // tracks the number of intersectiouns
	
	Intersection closestIntersection; // the closest intersection

    IntersectionList intersectionList; // a list of all intersections
    SurfaceList::const_iterator iter = m_surfaceList.begin();
    SurfaceList::const_iterator end  = m_surfaceList.end();

	// Evaluate this for each surface in the surface list
    for (; iter != end; ++iter)
	{
        // TO DO: Proj2 raytracer
        // 1. Check for intersections
        // 2. Update the list of intersections
		// 3. Set bFound to true if an intersection was found
        //---------------------------------------------------------
		if ((*iter)->FindIntersection(ray, pIntersection))
		{
			//delete index-^
			bFound = true;
			pIntersection->surface = *iter;
			numPoints++;
			//intersectionList.resize(numPoints);
			intersectionList.push_back(*pIntersection);
		}
		//----------------------------------------------------------------

    }

	//IntersectionList::const_iterator iter = intersectionList.begin();
	//IntersectionList::const_iterator end = intersectionList.end();

	if (bFound)
	{
		//for (;iter != end; ++iter)
		//{

		//}
		//closestIntersection.point = pIntersection->point;
		//closestIntersection.normal = pIntersection->normal;
		// TO DO: Proj2 raytracer
		// 1. bFound is true so find the closest intersection along the ray from the intersection list.
		// NOTE: you may have to resolve intersections that are too close within a margin of error.
		// You may choose to resolve this here and return 1 for numpoints or return the
		// number of close points and choose later (choosing later will require changing the code structure).
		// 2. set pIntersection to the closest intersection
		// 3. set the number of points and return
		//---------------------------------------------------------
		
		//---------------------------------------------------------
	}

	// return the number of close intersections found
    return(numPoints);
}
//Custom Find Interaction
bool Scene::FindIntersectionM(Ray ray, Intersection* pIntersection)
{
	bool bFound = false; // true if an intersection is found
	int numPoints = 0;   // tracks the number of intersectiouns

	Intersection closestIntersection; // the closest intersection

	IntersectionList intersectionList; // a list of all intersections
	SurfaceList::const_iterator iter = m_surfaceList.begin();
	SurfaceList::const_iterator end = m_surfaceList.end();

	// Evaluate this for each surface in the surface list
	for (; iter != end; ++iter)
	{
		if ((*iter)->IsTransparent()) continue;
		// TO DO: Proj2 raytracer
		// 1. Check for intersections
		// 2. Update the list of intersections
		// 3. Set bFound to true if an intersection was found
		//---------------------------------------------------------
		if ((*iter)->FindIntersection(ray, pIntersection))
		{
			bFound = true;
		}
		//----------------------------------------------------------------
	}
	return bFound;
}

//-----------------------------------------------------
// clear the scene by removing surfaces
//-----------------------------------------------------
void Scene::Clear(void)
{
    SurfaceList::iterator iter = m_surfaceList.begin();
    SurfaceList::iterator end  = m_surfaceList.end();

    // delete objects
    for (; iter != end; ++iter) {
        delete *iter;
        *iter = NULL;
    }

    // clean up
    m_surfaceList.clear();
}