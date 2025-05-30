#pragma once

#include "../Library/GameObject.h"
#include "global.h"

class Player : public GameObject
{
	Point position_;
	DIR currDir_;
	int hImage_;


public:
	Player();
	Player(Point _position);
	~Player();

	void Update() override;
	void Draw() override;
};