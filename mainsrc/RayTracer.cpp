//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// RayTracer.h
// Shades the objects in the scene based on information gathered by bouncing
// a ray in the scene and computing ray/surface intersections
//------------------------------------------------------------------------------

#include "RayTracer.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "utilities.h"
#include "STImage.h"
#include "Shader.h"
#include "STColor4ub.h"
#include "Camera.h"
#include "Light.h"



RayTracer::RayTracer(void)
    : m_maxLevel            (20),
     m_intensityThreshold   (0.001)
{
    pShader = new Shader();
}


RayTracer::~RayTracer()
{

}


//------------------------------------------------
// Main raytracing algorithm
// Cast Ray, Compute Intersections, Shade pixel
//-----------------------------------------------
void RayTracer::Run(Scene *pScene, std::string fName, RenderMode mode, ProjectionType projectionType)
{
    // begin 
    std::cout << "Running... " << std::endl;

    // set the shader's render mode
    pShader->SetMode(mode);

	int width = 2048;
	int height = 2048;
	float imageAspectRatio = width / height;
	float l = -1, r = 1;
	float b = -1, t = 1;


	RGBR_f bkground = pScene->GetBackgroundColor();
	STImage *pImg = new STImage(width, height, STImage::Pixel(bkground.r , bkground.b , bkground.g , bkground.a));
	
	bool hit;
	Intersection intersection;

	// TO DO: Proj2 raytracer
	//  Implement the ray tracing algorithm.
	// 1. Cast a ray from the camera into the scene
	//    Be sure to check projectionType -  var that sets the projection type
	//    as parallel or perspective.
	// 2. For every object in the scene compute intersections
	// 3. Compute shading for the closest intersections
	//       - no interection means shade to the background color
	//       - one intersection - great compute shading
	//       - otherwise implement any special handling to resolve
	//         ambiguities (determine the best choice or throw an exception)
	// 4. Save the output image
	// NOTE: STImage stores colors in pixels in the range 0-255
	// If you compute color channels in a range 0-1 you must convert
	//------------------------------------------------

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			float u = l + (r - l) * (i + 0.5) / width;
			float v = b + (t - b) * (j + 0.5) / height;

			Ray ray;
			if (projectionType == PARALLEL)
			{
				ray.SetOrigin(STVector3(u, v, 1)-ray.Origin());
				ray.SetDirection(STVector3(0, 0, -1));
			}
			else if (projectionType == PERSPECTIVE)
			{
				ray.SetDirection(STVector3(u, v, -1) - ray.Origin());
			}
			
			ray.Direction().Normalize();

			hit = pScene->FindClosestIntersection(ray, &intersection);
			if (hit)
			{
				RGBR_f color = Shade(pScene, &intersection);
				pImg->SetPixel(i, j, STColor4ub(color.r, color.g, color.b, color.a));
			}
			else
			{
				pImg->SetPixel(i, j, STColor4ub(bkground.r,bkground.g,bkground.b,bkground.a));
			}
		}
	}
	//-----------------------------------------------------------------------------------



    // end
    std::cout << "DONE... " << std::endl;

    // save
    pImg->Save(fName);
    std::cout << "saved file " << fName.c_str() << std::endl;
}


// This function computes all of the shading
// Recursively bounce the ray from object to object
// Use the Shader class to compute the final shading
RGBR_f RayTracer::Shade(Scene *pScene, Intersection *pIntersection)
{
    RGBR_f color;
	RGBR_f finalColor;

	// TO DO: Proj2 raytracer
	// Calculate the shading.
	// 1. Bounce the ray from object to object
	// 2. Compute the shading using the functions in the
	//    Shader class, attributes in pIntersection, and information
	//    about your scene
	// 3. Remember to stop the recursion
	// 4. Remember you need to add ambient lighting
	//------------------------------------------------

	for each (Light L in pScene->GetLightList())
	{
		STVector3 lightDir =  pIntersection->point- L.GetPosition();
		lightDir.Normalize();
		//color = pIntersection->surface->GetColor();
	
		//pShader->addAmbientLight(pIntersection, &color);
		color = pShader->Run(pScene, pIntersection, &lightDir, 2);

		finalColor.r += color.r * L.GetIntensity();
		finalColor.g += color.g * L.GetIntensity();
		finalColor.b += color.b * L.GetIntensity();
		finalColor.a += color.a * L.GetIntensity();
	}
	//------------------------------------------------------
	//finalColor = color;
	int s = pScene->GetLightList().size();
	finalColor.r /= s;
	finalColor.g /= s;
	finalColor.b /= s;
	finalColor.a /= s;

	if (finalColor.r > 255) finalColor.r = 255;
	if (finalColor.g > 255) finalColor.g = 255;
	if (finalColor.b > 255) finalColor.b = 255;
	if (finalColor.a > 255) finalColor.a = 255;

	// return the color
	return(finalColor);
}

//------------------------------------------------------
// Always render with a minimum color so that the scene
// is not black
//------------------------------------------------------
bool RayTracer::MinimumColor(RGBR_f color)
{
    if((color.r  >= m_intensityThreshold) ||
       (color.g >= m_intensityThreshold) ||
       (color.b >= m_intensityThreshold)) {
        return(true);
    }

   
    return(false);
}

