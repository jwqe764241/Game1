#pragma once

#include "Level.h"

class TestLevel : Level
{
public:
	TestLevel();
	~TestLevel();
	
	void Load(Graphics * gfx) override;
	void Unload() override;
	void Render() override;
	void Update() override;
};

