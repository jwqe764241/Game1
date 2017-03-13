#pragma once
#include "Level.h"
#include "Graphics.h"

class LevelController
{
private:
	Level * m_pCurrentLevel;

public:
	LevelController();
	~LevelController();

	void LoadLevel(Level * level);
	void ChangeLevel(Level * level);

	void Update();
	void Render();

};

