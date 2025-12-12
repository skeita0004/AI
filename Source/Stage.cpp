#include "Stage.h"
#include "../Library/Input.h"
#include "../ImGui/imgui.h"

namespace
{
	const int MAZE_WIDTH{39};
	const int MAZE_HEIGHT{21};
}

Stage::Stage() :
	mousePosition_()
{
	player = new Player({ 3, 3 });
	enemy = new Enemy({1 , 1 });

	maze_ = new Maze(MAZE_WIDTH,
					 MAZE_HEIGHT);
	//mazeData_ = maze_->Generate();
	mazeData_ = maze_->Load();
	//maze_->Save();
}

Stage::~Stage()
{
}

void Stage::Update()
{
	Point NextEnemyPos = enemy->GetPosition() + NEXT_POSITION[enemy->GetDir()];

	int x = NextEnemyPos.x;
	int y = NextEnemyPos.y;

	if (y == 0 || y == STAGE_HEIGHT - 1 || x == 0 || x == STAGE_WIDTH - 1)
	{
		enemy->IsWall(true);	// これで、Enemy側でnotを用いなくてもよくなる。
	}
	else
	{
		enemy->IsWall(false);
	}
}

void Stage::Draw()
{
	for (int i = 0; i < mazeData_.size(); i++)
	{
		int x = i % MAZE_WIDTH;
		int y = i / MAZE_WIDTH;
		
		switch (mazeData_[i])
		{
			case Maze::MazeState::WALL:
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0x0B1D51,
						TRUE);
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0x000000,
						FALSE);
				break;
			case Maze::MazeState::OUTER_WALL:
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0x725CAD,
						TRUE);
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0x000000,
						FALSE);
				break;
			case Maze::MazeState::WAY:
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0xffffff,
						TRUE);
				break;
			case Maze::MazeState::START:
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0xFFE3A9,
						TRUE);
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0x000000,
						FALSE);
				break;
			case Maze::MazeState::GOAL:
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0x8CCDEB,
						TRUE);
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0x000000,
						FALSE);
				break;
			default:
				break;
		}
	}


	//int x = 18 * CHARA_SIZE;
	//int y = 10 * CHARA_SIZE;
	//DrawBox(x, y, x + CHARA_SIZE, y + CHARA_SIZE, 0xffff00, TRUE);
}
