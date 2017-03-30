#pragma once

class IDrawable
{
public:
	virtual void CreateDeviceResources() = 0;
	virtual void ReleaseDeviceResources() = 0;
	virtual void Draw() = 0;
};