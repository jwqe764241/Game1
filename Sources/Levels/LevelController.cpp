#include <Sources/Levels/LevelController.h>

LevelController::LevelController()
{
}
LevelController::~LevelController()
{
	delete m_pCurrentLevel;
}


void LevelController::LoadLevel(Level * level)
{
	level->Load();
	m_pCurrentLevel = level;
}

void LevelController::CreateLevelDeviceResources()
{
	if (m_pCurrentLevel != nullptr)
	{
		m_pCurrentLevel->Load();
	}
}

void LevelController::ReleaseLevelDeviceResources()
{
	if (m_pCurrentLevel != nullptr)
	{
		m_pCurrentLevel->Unload();
	}
}

void LevelController::ChangeLevel(Level * level)
{
	if (m_pCurrentLevel != nullptr)
	{
		m_pCurrentLevel->Unload();
		level->Load();
		delete m_pCurrentLevel;
		m_pCurrentLevel = level;
	}
}

void LevelController::Update(float dt, HWND hwnd)
{
	if (m_pCurrentLevel != nullptr)
	{
		m_pCurrentLevel->Update(dt, hwnd);
	}
}

void LevelController::Render()
{
	if (m_pCurrentLevel != nullptr)
	{
		m_pCurrentLevel->Render();
	}
}