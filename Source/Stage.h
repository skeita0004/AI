#pragma once

#include "../Library/GameObject.h"
#include "Screen.h"
#include "global.h"
#include "Enemy.h"


class Stage : public GameObject
{
private:
	Point mousePosition_;
	Enemy* enemy;

public:
	Stage();
	~Stage();

	void Update() override;
	void Draw() override;
};