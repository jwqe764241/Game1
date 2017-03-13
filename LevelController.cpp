#include "LevelController.h"



LevelController::LevelController()
{
}


LevelController::~LevelController()
{
}

void LevelController::LoadLevel(Level * level)
{

}

void LevelController::ChangeLevel(Level * level)
{
	m_pCurrentLevel->Unload();
	//level->Load();
	delete m_pCurrentLevel;
	m_pCurrentLevel = level;
}

void LevelController::Update()
{
	m_pCurrentLevel->Render();
}

void LevelController::Render()
{
	m_pCurrentLevel->Render();
}