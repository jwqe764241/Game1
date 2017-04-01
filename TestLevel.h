#pragma once

#include <vector>
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "IActor.h"
#include "PlayerHealthUI.h"

class TestLevel : public Level
{
private:
	SpriteSheet m_SpriteSheet;

	D2D1_RENDER_TARGET_PROPERTIES m_renderProperties;

	DX_Input * m_pInput;

	bool m_bIsInitialized;

	//Render List
	Player * m_pPlayer;
	std::vector<Enemy> m_RenderEnemy;
	std::vector<IActor> m_RenderEnvir;

	// player Health gui.
	PlayerHealthUI m_playerHealthUI;

public:
	TestLevel(DX_Input * pInput);
	TestLevel(Player * player, DX_Input * pInput);
	~TestLevel();
	
	virtual void Load()   override;
	virtual void Unload() override;
	virtual void Render() override;
	virtual void Update(float dt) override;

	virtual void OnResize() override;
};

