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
	std::vector<Maze::MazeState> tmp;
	tmp = pMaze_->Load();

	mazeData_.resize(tmp.size());

	for (auto item : tmp)
	{
		static int i = 0;
		mazeData_[i].mzState = item;
		i++;
	}

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
		

		switch (mazeData_[i].mzState)
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
			case Maze::MazeState::FOUND:
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0xFF0000,
						TRUE);
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0x000000,
						FALSE);

				DrawFormatString(32 * x,
								 32 * y,
								 0x000000,
								 "%d", mazeData_[i].stepCount);
				break;
			default:
				break;
		}
	}
	for (int x = 0; x < MAZE_WIDTH; x++)
	{
		for (int y = 0; y < MAZE_HEIGHT; y++)
		{
			// 横線
			DrawLine(0, y * 32, MAZE_WIDTH * 32, y * 32, 0);

			// 縦線
			DrawLine(x * 32, 0, x * 32, MAZE_HEIGHT * 32, 0);
		}
	}
}

void Stage::SetMazeState(Point _pos, Maze::MazeState _state)
{
	int index = PointToIndex(_pos);
	mazeData_[index].mzState = _state;
}

void Stage::SetStepCount(Point _pos, int _stepCount)
{
	int index = PointToIndex(_pos);
	mazeData_[index].stepCount = _stepCount;
}

Maze::MazeState Stage::GetMazeState(Point _pos)
{
	int index = MAZE_WIDTH * _pos.y + _pos.x;
	return mazeData_[index].mzState;
}

Point Stage::IndexToPoint(int _index)
{
	return Point(_index % STAGE_WIDTH, _index / STAGE_WIDTH);
}

int Stage::PointToIndex(Point _pos)
{
	return MAZE_WIDTH * _pos.y + _pos.x;
}
