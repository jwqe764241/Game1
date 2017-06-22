#pragma once

#include <Sources/Levels/Level.h>
#include <Sources/Players/Player.h>
#include <Sources/Actors/Enemy.h>
#include <Sources/Interfaces/IActor.h>
#include <Sources/Actors/TestButton.h>
#include <vector>

class TestLevel : public Level
{
private:
	SpriteSheet		m_SpriteSheet;
	DX_Input*		m_pInput;
	PlayerHealthUI	m_playerHealthUI;
	D2D1_RENDER_TARGET_PROPERTIES m_renderProperties;
	bool m_bIsInitialized;

	//Render List
	Player * m_pPlayer;
	std::vector<Enemy>  m_RenderEnemy;
	std::vector<IActor> m_RenderEnvir;

public:
	TestLevel(DX_Input * pInput);
	TestLevel(DX_Input * pInput, Player * pPlayer);
	~TestLevel();

	virtual void Load()   override;
	virtual void Unload() override;
	virtual void Render() override;
	virtual void Update(float dt, HWND hwnd) override;
};

