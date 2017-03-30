#pragma once

#include <vector>
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "IActor.h"

class TestLevel : public Level
{
private:
	Graphics			  * m_pGraphics;

	SpriteSheet m_SpriteSheet;

	DX_Input * m_pInput;
	bool m_bIsInitialized;

	//·»´õ ¸®½ºÆ®
	Player * m_pPlayer;
	std::vector<Enemy> m_RenderEnemy;
	std::vector<IActor> m_RenderEnvir;

public:
	TestLevel() = delete;
	TestLevel(Graphics * gfx, DX_Input * pInput);
	TestLevel(Graphics * gfx, Player * player, DX_Input * pInput);
	~TestLevel();
	
	void Load()   override;
	void Unload() override;
	void Render() override;
	void Update(float dt) override;
};

