#pragma once

#include "../Library/GameObject.h"
#include <vector>
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
	void Move(float _moveInterval);

	void  SetPosition(Point _position) { position_ = _position; }
	Point GetPosition()                { return position_; }
	DIR   GetDir()                     { return currDir_; }
	void  IsWall(bool _isWall)   { isWall_ = _isWall; }

	/// <summary>
	/// Playerを見つけたか
	/// </summary>
	/// <returns>見つけた = true, 見つけてない = false</returns>
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
	// ↑これは、許されない。
	//		↑20250715 なんで？

	/// <summary>
	/// 視界の取得
	/// </summary>
	/// <param name="_deg">視野角</param>
	/// <param name="_dist">見える距離</param>
	/// <returns></returns>
	std::vector<Point> GetVisibility(float _deg, float _dist);
};