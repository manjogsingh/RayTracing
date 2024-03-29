//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Scene.h
// Stores all the objects - lights, camera and surfaces for setting up the scene.
//------------------------------------------------------------------------------


#ifndef __SCENE_H__
#define __SCENE_H__

#include "Camera.h"
#include "defs.h"
#include "Ray.h"
#include "Lists.h"
#include <string>
#include "RGBR_f.h"


class Scene
{

public:
                                Scene                                       (void);
                                ~Scene                                      (void);

    void                        SetBackgroundColor                          (RGBR_f color);
    RGBR_f                      GetBackgroundColor                          (void);

    void                        AddLight                                    (Light lightin);
	LightList					GetLightList(void);
	

    void                        AddSurface                                  (Surface *pSurfacein);


    Camera                      *GetCamera                                  (void);
 
    int                         FindIntersection                            (Ray ray, Intersection *pIntersection);
    int                         FindClosestIntersection                     (Ray ray, Intersection *pIntersection);

	bool Scene::FindIntersectionM(Ray ray, Intersection* pIntersection);

private:


    // surfaces
    SurfaceList                  m_surfaceList;


    // camera
    Camera                      *m_pCamera;

    // lights
    LightList                   m_lights;


    // background color
    RGBR_f                     m_background;

    // clear scene
    void                        Clear               (void);


};


#endif //__SCENE_H__


