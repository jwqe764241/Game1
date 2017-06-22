#pragma once

#include <Sources/Graphics.h>
#include <Sources/Keyboard.h>
#include <Sources/DX_Input.h>
#include <vector>

class IActor
{
public:

	virtual ~IActor() {};

	virtual void Draw() = 0;

	virtual void Update(DX_Input & input, float dt) = 0;

	virtual D2D1_RECT_F GetRect() = 0;

};

