#pragma once

#include "../Library/GameObject.h"
#include "Screen.h"
#include "global.h"
#include "Enemy.h"
#include "Player.h"
#include "Maze.hpp"
class Maze;

class Stage : public GameObject
{
public:
	Stage();
	~Stage();

	void Update() override;
	void Draw() override;

private:
	Point mousePosition_;
	Enemy* enemy;
	Player* player;
	Maze* maze_;

	std::vector<Maze::MazeState> mazeData_;
};