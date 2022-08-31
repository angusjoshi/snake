#include "framework.h"
#include "Game.h"
#include "objects.h"
#include "ticker.h"
#include <iostream>

GameObject::GameObject(const Point& pos)
	:m_Pos(pos)
{
}

Snake::Snake()
{
	OutputDebugString(L"asdfasdf");
	m_Pos = Point(50, 50);
	m_Length = 1;
	m_Direction = Point(1, 0);
	m_Head = new SnakeBlock(m_Pos);
	m_End = m_Head;
	m_Dead = false;
	m_ChangedDirection = false;
	m_NGrow = 4;
}
void Snake::Update()
{
	bool ticked = g_Game.m_Ticker.Ticked();
	
	
	

	if (ticked && !m_Dead)
	{
		if (g_Game.ChangingDirection())
		{
			Point nextDirection = g_Game.NextDirection();
			if (m_Direction != (nextDirection * -1))
			{
				m_Direction = nextDirection;
			}	
			else
			{
				g_Game.ClearMoves();
			}
		}
		
		Point lastPos = m_Head->m_Pos;
		SnakeBlock* currBlock = m_Head->m_Tail;
		m_Head->m_Pos = m_Head->m_Pos + m_Direction * 10;
		while (currBlock)
		{
			Point nextLastPos = currBlock->m_Pos;
			currBlock->m_Pos = lastPos;
			lastPos = nextLastPos;
			currBlock = currBlock->m_Tail;
		}
		currBlock = m_Head->m_Tail;
		while (currBlock)
		{
			if (m_Head->m_Pos == currBlock->m_Pos) m_Dead = true;
			currBlock = currBlock->m_Tail;

		}
		if (m_NGrow > 0)
		{
			m_End->m_Tail = new SnakeBlock(m_End->m_Pos);
			m_End = m_End->m_Tail;
			m_NGrow--;
		}
		m_ChangedDirection = false;
	}
}
void Snake::Draw(HDC hdc)
{

	//OutputDebugString(L"hehe \n");
	auto curr = m_Head;
	while (curr)
	{
		curr->Draw(hdc);
		curr = curr->m_Tail;
	}
	
}
Point Snake::HeadPos()
{
	return m_Head->m_Pos;
}
SnakeBlock::SnakeBlock(const Point& pos)
	:GameObject(pos)
{
	m_Tail = nullptr;
}
void SnakeBlock::Draw(HDC hdc)
{
	Rectangle(hdc, m_Pos.x, m_Pos.y, m_Pos.x + 10, m_Pos.y + 10);
}
void SnakeBlock::Update()
{

}
Food::Food(const Point & pos)
	:GameObject(pos)
{
}
//TODO: Add logic to avoid placing food on snake blocks
void Food::Update()
{
	if (m_Eaten)
	{
		m_Pos = Point((rand() % 100) * 10, (rand() % 100) * 10);
		m_Eaten = false;
	}
}
void Food::Draw(HDC hdc)
{
	Rectangle(hdc, m_Pos.x, m_Pos.y, m_Pos.x + 10, m_Pos.y + 10);
}
void Food::Eat()
{
	m_Eaten = true;
}