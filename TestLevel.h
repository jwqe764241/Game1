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
	SpriteSheet m_SpriteSheet;

	D2D1_RENDER_TARGET_PROPERTIES m_renderProperties;

	DX_Input * m_pInput;

	bool m_bIsInitialized;

	//·»´õ ¸®½ºÆ®
	Player * m_pPlayer;
	std::vector<Enemy> m_RenderEnemy;
	std::vector<IActor> m_RenderEnvir;

	TestButton m_testButton;

public:
	TestLevel(DX_Input * pInput);
	TestLevel(Player * player, DX_Input * pInput);
	~TestLevel();
	
	virtual void Load()   override;
	virtual void Unload() override;
	virtual void Render() override;
	virtual void Update(float dt, HWND hwnd) override;

	virtual void OnResize() override;

	virtual void UpdateUI(HWND hwnd) override;
};

