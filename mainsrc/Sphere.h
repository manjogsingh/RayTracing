//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Sphere.h
// Sphere surface object
//------------------------------------------------------------------------------


#ifndef __SPHERE_H__
#define __SPHERE_H__



#include "Surface.h"
#include "Ray.h"
#include "Intersection.h"
#include <math.h>


class Sphere  : public Surface 
{

public:

							
                                Sphere                              (float x, float y, float z, RGBR_f color, float radius);
								Sphere                              (float x, float y, float z, RGBR_f color, float radius,float transparent);
                                ~Sphere                             (void);



    bool                        FindIntersection                    (Ray ray, Intersection *pIntersection); // find ray sphere intersections
	bool                        CompareTo                           (Sphere sphere);                        // compare shere objects

private:

    float                       m_radius;



};


#endif //__SPHERE_H__

