#include "Stage.h"
#include "../Library/Input.h"
#include "../ImGui/imgui.h"
#include "Explorer.h"

namespace
{
	const int MAZE_WIDTH{39};
	const int MAZE_HEIGHT{21};
}

Stage::Stage() :
	pExplorer_(),
	pMaze_(),
	mazeData_()
{
	pMaze_ = new Maze(MAZE_WIDTH,
					 MAZE_HEIGHT);
	//mazeData_ = pMaze_->Generate();
	mazeData_ = pMaze_->Load();
	//pMaze_->Save();

	int x, y;
	x = pMaze_->GetStart() % MAZE_WIDTH;
	y = pMaze_->GetStart() / MAZE_WIDTH;

	pExplorer_ = new Explorer({x, y});
	SetDrawOrder(INT_MAX - 1);
}

Stage::~Stage()
{
}

void Stage::Update()
{
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
}

void Stage::SetMazeState(Point _pos, Maze::MazeState _state)
{
	int index = MAZE_WIDTH * _pos.y + _pos.x;
	mazeData_[index] = _state;
}

Maze::MazeState Stage::GetMazeState(Point _pos)
{
	int index = MAZE_WIDTH * _pos.y + _pos.x;
	return mazeData_[index];
}
