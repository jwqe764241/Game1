#pragma once

#include "Graphics.h"
#include "GameDefine.h"
#include "Gauge.h"
#include "TextWriter.h"

class Level
{
public:
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update(float dt, HWND hwnd) = 0;

	virtual void OnResize() = 0;

	virtual void UpdateUI(HWND hwnd) = 0;
};

