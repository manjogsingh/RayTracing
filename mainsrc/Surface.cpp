//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Surface.cpp
// Base class for all Surfaces
//-------------------------------------------------------------------------------


#include "Surface.h"
#include <assert.h>
#include <stdio.h>
#include <string>



Surface::Surface()
{
}


Surface::~Surface()
{

}

float Surface::GetTranspValue(void)
{
	return m_transparent;
}

bool Surface::IsTransparent(void)
{
	return (m_transparent != 0);
}

RGBR_f Surface::GetColor(void)
{
	return m_color;
}


