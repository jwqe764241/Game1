#include "LevelController.h"



LevelController::LevelController()
{
}


LevelController::~LevelController()
{
	m_pCurrentLevel->Unload();
	delete m_pCurrentLevel;
}

void LevelController::LoadLevel(Level * level)
{
	level->Load();
	m_pCurrentLevel = level;
}

void LevelController::ChangeLevel(Level * level)
{
	m_pCurrentLevel->Unload();
	level->Load();
	delete m_pCurrentLevel;
	m_pCurrentLevel = level;
}

void LevelController::Update(float dt)
{
	m_pCurrentLevel->Update(dt);
}

void LevelController::Render()
{
	m_pCurrentLevel->Render();
}