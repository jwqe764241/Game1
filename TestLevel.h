#pragma once

#include <vector>
#include "Level.h"
#include "Player.h"
#include "IActor.h"
#include "PlayerHealthUI.h"

class TestLevel : public Level
{
private:
	SpriteSheet m_SpriteSheet;

	D2D1_RENDER_TARGET_PROPERTIES m_renderProperties;

	DX_Input * m_pInput;

	//wchar_t * m_lpszFilePath;
	bool m_bIsInitialized;

	D2D1_SIZE_F m_LevelSize;

	//·»´õ ¸®½ºÆ®
	Player * m_pPlayer;
	std::vector<IActor *> m_RenderEnemy;
	std::vector<IActor *> m_RenderEnvir;

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

