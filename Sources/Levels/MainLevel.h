#pragma once

#include <Sources/DX_Input.h>
#include <Sources/Levels/Level.h>
#include <Sources/Actors/TestButton.h>
#include <Sources/GameDefine.h>
#include <vector>

class MainLevel : public Level
{
private:
	SpriteSheet m_SpriteSheet;
	DX_Input*   m_pInput;
	bool        m_bIsInitialized;

	std::vector<TestButton *> m_RenderEnvir;

public:
	MainLevel(DX_Input * pInput);
	~MainLevel();

	virtual void Load()   override;
	virtual void Unload() override;
	virtual void Render() override;
	virtual void Update(float dt, HWND hWnd) override;
};

