#pragma once

#include <Sources/DX_Input.h>
#include <Sources/Levels/Level.h>
#include <Sources/Actors/TestButton.h>
#include <Sources/GameDefine.h>

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

