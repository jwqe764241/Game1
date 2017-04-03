#pragma once

#include "DX_Input.h"
#include "Level.h"
#include "TestButton.h"
#include "GameDefine.h"

class HowLevel :public Level
{
private:
	SpriteSheet m_SpriteSheet;
	DX_Input * m_pInput;

	TestButton * m_pBackButton;
	
public:
	HowLevel(DX_Input * pInput);
	~HowLevel();

	virtual void Load()   override;
	virtual void Unload() override;
	virtual void Render() override;
	virtual void Update(float dt, HWND hWnd) override;

};

