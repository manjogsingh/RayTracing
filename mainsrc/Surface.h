//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Surface.h
// Defines the base class for surfaces
//-----------------------------------------------------------------------------

#ifndef _SURFACE_H
#define _SURFACE_H


#include "STVector3.h"
#include "Ray.h"
#include "Intersection.h"
#include "defs.h"
#include "Lists.h"




class Surface
{

    public:
                                    Surface                             ();
                                    ~Surface                            (void);
	bool                            IsTransparent						(void);
	float                           GetTranspValue                      (void);
    RGBR_f                          GetColor                            (void);
    virtual bool                    FindIntersection                    (Ray ray, Intersection *pIntersection){ return(false);}

protected:
    
    STVector3                       m_center;
	RGBR_f                          m_color;
	float                           m_transparent;


};


#endif //_SURFACE_H



