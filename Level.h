#pragma once

#include "Graphics.h"

class Level
{
private:
	Graphics * m_pGraphics;

public:
	virtual ~Level() {}

	void Initialize(Graphics * gfx) {

		m_pGraphics = gfx;
	}

	virtual void Load(Graphics * gfx) = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
};

