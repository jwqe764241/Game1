#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "DX_Input.h"

class IActor
{
public:

	virtual ~IActor() {};

	virtual void Draw(Graphics * gfx)		 = NULL;

	virtual void Update(DX_Input & input) = NULL;

};

