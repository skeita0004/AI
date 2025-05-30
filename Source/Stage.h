#pragma once

#include "../Library/GameObject.h"
#include "Screen.h"
#include "global.h"
#include "Enemy.h"
#include "Player.h"


class Stage : public GameObject
{
private:
	Point mousePosition_;
	Enemy* enemy;
	Player* player;

public:
	Stage();
	~Stage();

	void Update() override;
	void Draw() override;
};