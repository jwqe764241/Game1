#pragma once

#include "Graphics.h"
#include "GameDefine.h"
#include "Gauge.h"
#include "TextWriter.h"
#include <sstream>

class Level
{
public:
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update(float dt) = 0;

	virtual void OnResize() = 0;
};

