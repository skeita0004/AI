#pragma once

#include "../Library/GameObject.h"
#include "global.h"

class Player : public GameObject
{
	Point position_;

public:
	Player();
	~Player();

	void Update() override;
	void Draw() override;
};