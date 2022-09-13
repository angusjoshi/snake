#include "framework.h"
#include "Game.h"
#include "objects.h"

const int Game::X_DIMENSION = 60;
const int Game::Y_DIMENSION = 40;
//TODO: Add game menu
//TODO: Add pause functionality
bool Game::Initialise()
{
	if (m_Snake) delete m_Snake;
	if (m_Food) delete m_Food;
	srand(time(NULL));
	m_Snake = new Snake();
	m_Food = new Food(Point((rand() % Game::X_DIMENSION) * 10, (rand() % Game::Y_DIMENSION) * 10));
	return true;
}
void Game::Update(bool& needRedraw)
{
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		if (!m_DownPressed)
		{
			m_DownPressed = true;
			if (m_Moves.empty() || m_Moves.back() != Point(0, 1)) m_Moves.push(Point(0, 1));
		}
	}
	else
	{
		m_DownPressed = false;
	}

	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		if (!m_RightPressed)
		{
			m_RightPressed = true;
			if (m_Moves.empty() || m_Moves.back() != Point(1, 0)) m_Moves.push(Point(1, 0));
		}
	}
	else
	{
		m_RightPressed = false;
	}

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		if (!m_LeftPressed)
		{
			m_LeftPressed = true;
			if (m_Moves.empty() || m_Moves.back() != Point(-1, 0)) m_Moves.push(Point(-1, 0));
		}
	}
	else 
	{
		m_LeftPressed = false;
	}

	if (GetKeyState(VK_UP) & 0x8000)
	{	
		if (!m_UpPressed)
		{
			m_UpPressed = true;
			if (m_Moves.empty() || m_Moves.back() != Point(0, -1)) m_Moves.push(Point(0, -1));
		}
	}
	else
	{
		m_UpPressed = false;
	}
	if (m_Snake->HeadPos() == m_Food->m_Pos)
	{
		m_Food->Eat();
		m_Snake->m_NGrow += 3;
	}
	m_Ticker.Update();
	m_Food->Update();
	m_Snake->Update();
	

	needRedraw = m_Ticker.Ticked();
	if (m_Ticker.Ticked())
	{
		m_Ticker.Reset();
		
	}
}
Point Game::NextDirection()
{
	Point next = m_Moves.front();
	m_Moves.pop();
	return next;

}
bool Game::ChangingDirection()
{
	return !m_Moves.empty();
}
void Game::ClearMoves()
{
	std::queue<Point> empty;
	std::swap(m_Moves, empty);
}
void Game::Draw(HDC hdc, PAINTSTRUCT* ps)
{
	HBRUSH brushRed = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH brushGreen = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH brushBlue = CreateSolidBrush(RGB(0, 0, 255));

	SelectObject(hdc, brushBlue);
	if (m_Snake)
	{
		m_Snake->Draw(hdc);
		if (m_Snake->m_Dead)
		{
			SelectObject(hdc, brushRed);
			m_Snake->m_Head->Draw(hdc);
		}
	}
	SelectObject(hdc, brushGreen);
	if (m_Food)
	{
		m_Food->Draw(hdc);
	}
	
	
	DeleteObject(brushBlue);
	DeleteObject(brushRed);
	DeleteObject(brushGreen);
}
Game::~Game()
{
	delete m_Food;
	auto curr = m_Snake->m_Head;
	while (curr)
	{
		auto next = curr->m_Tail;
		delete curr;
		curr = next;
	}
	delete m_Snake;
}
