#pragma once

#include "../Library/GameObject.h"
#include "global.h"

class Player;

class Enemy : public GameObject
{


public:
	Enemy(Point _position);
	~Enemy();

	void Update() override;
	void UpdateNormal();
	void UpdateChase();
	void UpdateEscape();

	void Draw() override;

	void TurnLeft();
	void TurnRight();
	void TurnBack();
	void Move();

	void  SetPosition(Point _position) { position_ = _position; }
	Point GetPosition()                { return position_; }
	DIR   GetDir()                     { return currDir_; }
	void  IsWall(bool _isWall)   { isWall_ = _isWall; }

	/// <summary>
	/// PlayerÇå©Ç¬ÇØÇΩÇ©
	/// </summary>
	/// <returns>å©Ç¬ÇØÇΩ = true, å©Ç¬ÇØÇƒÇ»Ç¢ = false</returns>
	bool IsFindPlayer(Player *_pPlayer);

private:
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
	bool isWall_;
	EState state_;
	Player* pPlayer_;
	float chaseTimer_;
	float escapeTimer_;
	//static float animTimer_; 
	//static int animIndex_;
	// Å™Ç±ÇÍÇÕÅAãñÇ≥ÇÍÇ»Ç¢ÅB
};