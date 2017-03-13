#pragma once

#include "Graphics.h"

class IActor
{
public:

	virtual ~IActor() {};

	virtual void Draw(Graphics * gfx)		 = NULL;

	virtual void Update()					 = NULL;
	virtual void Update(D2D1_POINT_2F point) = NULL;
	virtual void Update(float x, float y)	 = NULL;

};

