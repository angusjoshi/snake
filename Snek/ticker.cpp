#include "framework.h"
#include "ticker.h"

#include <time.h>
#include <stdio.h>
Ticker::Ticker()
	:m_TickDuration(0.05f),
	m_TimeDelta(0.f),
	m_Ticks(0),
	m_Ticked(false),
	m_NTicks(0)
{
	Reset();
}


void Ticker::Reset()
{
	m_TimeDelta = 0.f;
	m_Ticks = clock();
	m_Ticked = false;
	m_NTicks++;
}

void Ticker::Update()
{
	if (m_Ticked) return;

	long ticks = clock();

	m_TimeDelta += float((double)(ticks - m_Ticks) / CLOCKS_PER_SEC);
	m_Ticked = m_TimeDelta > m_TickDuration;

	m_Ticks = ticks;
}