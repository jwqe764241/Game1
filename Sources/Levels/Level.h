#pragma once

#include <Sources/Graphics.h>
#include <Sources/GameDefine.h>
#include <Sources/Actors/Gauge.h>
#include <Sources/TextWriter.h>

class Level
{
public:
	virtual void Load()   = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update(float dt, HWND hwnd) = 0;
};

