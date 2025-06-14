#pragma once

#include "../Library/GameObject.h"
#include "global.h"

class Enemy : public GameObject
{
	enum struct EState
	{
		NORMAL,
		CHASE,
		ESCAPE,
		MAX_ESTATE
	};

	Point position_;
	int hImage_;
	DIR currDir_;
	DIR nextDir;
	std::string dir;
	float dirTimer_;
	float moveTimer_;
	int* anim;
	bool isNotWall_;
	EState state_;
	//static float animTimer_; 
	//static int animIndex_;
	// ↑これは、許されない。


public:
	Enemy(Point _position);
	~Enemy();

	void Update() override;
	void Draw() override;

	void TurnLeft();
	void TurnRight();
	void TurnBack();

	void  SetPosition(Point _position) { position_ = _position; }
	Point GetPosition()                { return position_; }
	DIR   GetDir()                     { return currDir_; }
	void  IsNotWall(bool _isNotWall)   { isNotWall_ = _isNotWall; }
};