#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "DX_Input.h"
#include <vector>

class IActor
{
public:

	virtual ~IActor() {};

	virtual void Draw(Graphics * gfx) = 0;

	virtual void Update(DX_Input & input, float dt) = 0;

	virtual D2D1_RECT_F GetRect() = 0;

};

