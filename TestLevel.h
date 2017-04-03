#pragma once

#include <vector>
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "IActor.h"
#include "TestButton.h"

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

