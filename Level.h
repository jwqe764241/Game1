#pragma once

#include "Graphics.h"
#include "GameDefine.h"

class Level
{
public:
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
};

