#pragma once

class Ticker
{
public:
	Ticker();
	Ticker(float tickDuration);

	void Reset();
	void Update();

	bool Ticked() { return m_Ticked; }
private:
	float m_TickDuration;
	float m_TimeDelta;
	unsigned long m_Ticks;
	bool m_Ticked;
public:
	int m_NTicks;
};