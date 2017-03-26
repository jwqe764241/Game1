#pragma once

#include <vector>
#include "Level.h"
#include "Player.h"
#include "IActor.h"

class TestLevel : public Level
{
private:
	Graphics			  * m_pGraphics;

	IWICBitmapDecoder	  * m_pDecoder;
	IWICBitmapFrameDecode * m_pFrameDecode;
	IWICFormatConverter	  * m_pConvertedBitmap;
	ID2D1Bitmap			  * m_pBitmap;

	D2D1_RENDER_TARGET_PROPERTIES m_renderProperties;

	DX_Input * m_pInput;

	wchar_t * m_lpszFilePath;
	bool m_bIsInitialized;

	//·»´õ ¸®½ºÆ®
	Player * m_pPlayer;
	std::vector<IActor *> m_RenderEnemy;
	std::vector<IActor *> m_RenderEnvir;

public:
	TestLevel(Graphics * gfx, DX_Input * pInput);
	TestLevel(Graphics * gfx, Player * player, DX_Input * pInput);
	~TestLevel();
	
	void Load()   override;
	void Unload() override;
	void Render() override;
	void Update() override;
};

