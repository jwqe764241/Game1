#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "DX_Input.h"

class IActor
{
public:

	virtual ~IActor() {};

	virtual void Draw(Graphics * gfx)		 = NULL;

	//virtual void Update(Keyboard & keyboard) = NULL;
	virtual void Update(DX_Input & input) = NULL;
	virtual void Update(D2D1_POINT_2F point) = NULL;
	virtual void Update(float x, float y)	 = NULL;

};

