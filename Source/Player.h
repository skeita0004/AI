#pragma once

#include "../Library/GameObject.h"
#include "global.h"

class Player : public GameObject
{
public:
	Player();
	Player(Point _position);
	~Player();

	void Update() override;
	void Draw() override;

	Point GetPosition() { return position_; }
	DIR   GetDir() { return currDir_; }
	void  IsNotWall(bool _isNotWall) { isNotWall_ = _isNotWall; }

private:
	Point position_;
	DIR currDir_;
	int hImage_;
	bool isNotWall_;
};