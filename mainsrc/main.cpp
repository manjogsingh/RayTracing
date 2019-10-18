//--------------------------------------------------------
// Computer Graphics
// University of Florida
// Copyright 2015 Corey Toler-Franklin
//--------------------------------------------------------



// System
#include <string>
#include <algorithm>
using namespace std;

// GLEW
#ifndef GLEW_STATIC
    #define GLEW_STATIC 1
#endif
#include "stglew.h"
#include <stdio.h>
#include <string.h>
#include <map>
#include "Scene.h"
#include "RayTracer.h"
#include "Light.h"
#include "Sphere.h"
#include "Triangle.h"
#include "defs.h"


// globals
//---------------------------------
// scene
Scene       *pScene = NULL;     // scene geometry and lights
RayTracer   *pRayTracer = NULL; // runs ray tracing algorithm
ProjectionType m_projectionType = ProjectionType::PERSPECTIVE; // parallel or perspective

void Setup(void);

// mouse
int gPreviousMouseX = -1;
int gPreviousMouseY = -1;
int gMouseButton = -1;

// Window size, kept for screenshots
static int gWindowSizeX = 500;
static int gWindowSizeY = 500;


//---------------------------------------------------------------------
// Scene functions
//---------------------------------------------------------------------
// Creates the scene
//
void Setup(void)
{

	// init the scene
	pScene = new Scene();

	// TO DO: Proj2 raytracer
	// Set up your scene.
	// Use the variable pScene to set parameters
	// 1. change background color
	// 2. add lights
	// 3. add objects
	// 4. add translation and rotation operations to place objects
	//------------------------------------------------
	pScene->SetBackgroundColor(RGBR_f(47, 53, 66, 255));
	
	pScene->AddLight(Light(STVector3(4, 0, 1), RGBR_f(255, 255, 255, 255),2, "pointLight1"));
	pScene->AddLight(Light(STVector3(-4, 0, 1), RGBR_f(255, 255, 255, 255), 3, "pointLight2"));
	pScene->AddLight(Light(STVector3(0, 4, -3), RGBR_f(255, 255, 255, 255), 1.5, "pointLight3"));
	pScene->AddLight(Light(STVector3(-5, 1, 5), RGBR_f(255, 255, 255, 255), 1, "pointLight4"));
	//pScene->AddLight(Light(STVector3(0, 0, 4), RGBR_f(255, 255, 255, 255), 1, "pointLight5"));

	Sphere* sphere = new Sphere(0, -110, -10, RGBR_f(255, 255, 255, 255), 100);
	pScene->AddSurface(sphere);
	sphere = new Sphere(0,0,-10,RGBR_f(231, 76, 60,255),4);
	pScene->AddSurface(sphere);
	sphere = new Sphere(-2.5,0, -5, RGBR_f(242, 121, 15, 255), 0.5);
	pScene->AddSurface(sphere);
	sphere = new Sphere(2, 0, -4, RGBR_f(99, 110, 114, 255), 1);
	pScene->AddSurface(sphere);
	sphere = new Sphere(1, -2, -5, RGBR_f(15, 95, 166, 255), 1);
	pScene->AddSurface(sphere);
	sphere = new Sphere(-1, -2, -5, RGBR_f(242, 189, 29, 255), 1,1);
	pScene->AddSurface(sphere);
	sphere = new Sphere(1.5, -1, -3, RGBR_f(46, 213, 115, 255), 0.5, 1);
	pScene->AddSurface(sphere);

	//Triangle* triangle = new Triangle(
	//	STVector3(5, -6, -15),
	//	STVector3(-5, -6, -15), 
	//	STVector3(2, 6, -15),
	//	RGBR_f(31, 146, 160, 255));
	//pScene->AddSurface(triangle);
	//------------------------------------------------

    // init a ray tracer object
    pRayTracer = new RayTracer();
	
}





// If the commandline input is incorrect, notifies the user.
void usage(const char *myname) 
{
	fprintf(stderr, "Usage: %s\n rendermode (1-4), projectiontype (1-2)\n\n\n", myname);
    fprintf(stderr, "rendermodes:\n1 Lambertian\n2 Phong\n3 Mirror\n4 Shadows\n5 Transparency\n\n");
	fprintf(stderr, "projectiontypes:\n1 Parallel\n2 Perspective\n\n");
	exit(0);
}


// Parses the input arguments
// The input to the program is a single
// integer value to specify the render mode
RenderMode parseArgs(int argc, char **argv)
{
    if(!(argc == 3))
        usage(argv[0]);

	// get the render mode from the input
    RenderMode mode = (RenderMode)(atoi(argv[1]));

	// determine the current mode
    if(! ((mode == LAMBERTIAN) ||
          (mode == PHONG) ||
          (mode == MIRROR) ||
          (mode == SHADOWS) ||
          (mode == TRANSPARENCY))) {
		usage(argv[0]);        
    }


	// get the viewing mode from the input
	m_projectionType = (ProjectionType)(atoi(argv[2]));


	if (!((m_projectionType == PARALLEL) || (m_projectionType == PERSPECTIVE))) {
		usage(argv[0]);
	}


	// return the current mode
    return(mode);
}



//-----------------------------------------------
// Proj2 Ray Tracer
// This function follows the main
// logic of your rendering program.
// The commandline input is two integers that specify 
// the render mode (see RenderMode) and projection type (see ProjectionType).
// The render modes and projection types are defined in enums in file Defs.h
// Example
// >> proj2_raytracer 1 2
//
//-----------------------------------------------
int main(int argc, char** argv)
{
	RenderMode mode;
	ProjectionType pType;
    // TO DO: Proj2 raytracer
    // Set the render mode.
    // 1. Here, we read in the render mode from the commandline.
    //    The render modes are defined in the RenderMode enum in file Defs.h
    //    If you make any changes to RenderMode or input parameters, you have to 
    //    update parseArgs(int argc, char **argv).
    //------------------------------------------------
	mode=parseArgs(argc, argv);
    //------------------------------------------------

    // Initializes the scene
    Setup();

    // run the ray tracer
    pRayTracer->Run(pScene, "output.png", mode, m_projectionType);


    return 0;
}


#pragma endregion
