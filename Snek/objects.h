#pragma once
#include "point.h"

class GameObject 
{
public:
	GameObject() {}
	GameObject(const Point& pos);

	virtual void Update() = 0;
	virtual void Draw(HDC hdc) = 0;
	Point m_Pos;
};

class Snake : public GameObject
{
public:
	Snake();

	virtual void Update(); 
	virtual void Draw(HDC hdc);

	virtual Point HeadPos();
	int m_Length;
	Point m_Direction;
	SnakeBlock* m_Head;
	SnakeBlock* m_End;
	bool m_Dead;
	bool m_ChangedDirection;
	int m_NGrow;

};
class SnakeBlock : public GameObject
{
public:
	SnakeBlock(const Point& pos);
	virtual void Update();
	virtual void Draw(HDC hdc);

	SnakeBlock* m_Tail;

};

class Food : public GameObject
{
public:
	bool m_Eaten;
	Food(const Point& pos);

	virtual void Update();
	virtual void Draw(HDC hdc);

	virtual void Eat();
};
