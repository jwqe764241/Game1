#pragma once

#include "SpriteSheet.h"

class Button 
{
private:
	SpriteSheet	  m_SpriteSheet;
	D2D1_POINT_2F m_ObjectPoint;

public:

	Button(float x, float y);
	~Button();

	void Render();
	bool IsOnMouse(float x, float y);
};