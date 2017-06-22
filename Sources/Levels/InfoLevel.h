#pragma once

#include <Sources/DX_Input.h>
#include <Sources/Levels/Level.h>
#include <Sources/Actors/TestButton.h>
#include <Sources/GameDefine.h>

class InfoLevel : public Level
{
private:
	SpriteSheet m_SpriteSheet;
	DX_Input * m_pInput;

	TestButton * m_pBackButton;

public:
	InfoLevel(DX_Input * pInput);
	~InfoLevel();

	virtual void Load()   override;
	virtual void Unload() override;
	virtual void Render() override;
	virtual void Update(float dt, HWND hWnd) override;
};

