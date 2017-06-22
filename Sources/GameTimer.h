#pragma once

#include <Sources/GameDefine.h>

class GameTimer
{
public:
	GameTimer();
	//GameTimer(const GameTimer&);
	~GameTimer();

	bool Initialize();
	void Frame();

	float GetTime();

private:
	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime; // deltatime
};
