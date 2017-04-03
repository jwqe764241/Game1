#pragma once

#include <vector>
#include "DX_Input.h"
#include "Level.h"
#include "TestButton.h"


class MainLevel : public Level
{
private:
	SpriteSheet m_SpriteSheet;
	DX_Input*	m_pInput;
	bool m_bIsInitialized;

	std::vector<Button *> m_RenderEnvir;

public:
	MainLevel(DX_Input * pInput);
	~MainLevel();

	virtual void Load()   override;
	virtual void Unload() override;
	virtual void Render() override;
	virtual void Update(float dt, HWND hWnd) override;
};

