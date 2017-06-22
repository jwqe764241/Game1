#include <Sources/GameTimer.h>

GameTimer::GameTimer(){}
GameTimer::~GameTimer(){}

bool GameTimer::Initialize() {
	// check if timer system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if (m_frequency == 0) return false;

	// find out how many times the frequency counter ticks every millisecond * 10.
	m_ticksPerMs = (float)(m_frequency / 100);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}

void GameTimer::Frame() {
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (float)(currentTime - m_startTime);
	
	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;

	return;
}

float GameTimer::GetTime() {
	return m_frameTime;
}