#pragma once

#include <vector>
#include "DX_Input.h"
#include "Level.h"
#include "TextWriter.h"
#include "TestButton.h"
#include "GameDefine.h"

class GameOverLevel : public Level
{
public:
	GameOverLevel(DX_Input* pInput);
	GameOverLevel(DX_Input* pInput, D2D1::ColorF pColor);
	~GameOverLevel();

private:
	virtual void Load()   override;
	virtual void Unload() override;
	virtual void Render() override;
	virtual void Update(float dt, HWND hWnd) override;

private:
	DX_Input * m_pInput;

	D2D1::ColorF m_screenColor;

	TextWriter m_gameOverTextLayout;

	std::vector<TestButton *> m_buttonList;
};