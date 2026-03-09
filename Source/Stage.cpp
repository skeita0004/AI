#include "Stage.h"
#include "../Library/Input.h"
#include "../ImGui/imgui.h"
#include "Explorer.h"

Stage::Stage() :
	pExplorer_(),
	pMaze_(),
	mazeData_()
{
	pMaze_ = new Maze(0, 0);


	std::vector<Maze::MazeState> tmp;
	//tmp = pMaze_->Load();
	tmp = pMaze_->Generate(21, 21);
	int mazeWidth = pMaze_->GetWidth();

	mazeData_.resize(tmp.size());

	int i = 0;
	for (auto item : tmp)
	{
		mazeData_[i].mzState = item;
		mazeData_[i].stepCount = INT32_MAX;
		i++;
	}

	int x, y;
	x = pMaze_->GetStart() % mazeWidth;
	y = pMaze_->GetStart() / mazeWidth;

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
	int mazeWidth = pMaze_->GetWidth();
	int mazeHeight = pMaze_->GetHeight();

	for (int i = 0; i < mazeData_.size(); i++)
	{
		int x = i % mazeWidth;
		int y = i / mazeWidth;
		

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

			case Maze::MazeState::ETCHING:
				DrawBox(32 * x,
						32 * y,
						32 * x + 32,
						32 * y + 32,
						0x00FFFF,
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
	for (int x = 0; x < mazeWidth; x++)
	{
		for (int y = 0; y < mazeHeight; y++)
		{
			// 横線
			DrawLine(0, y * 32, mazeWidth * 32, y * 32, 0);

			// 縦線
			DrawLine(x * 32, 0, x * 32, mazeHeight * 32, 0);
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

int Stage::GetStepCount(Point _pos)
{
	int index = PointToIndex(_pos);
	return mazeData_[index].stepCount;
}

Maze::MazeState Stage::GetMazeState(Point _pos)
{
	int index = pMaze_->GetWidth() * _pos.y + _pos.x;
	return mazeData_[index].mzState;
}

Point Stage::IndexToPoint(int _index)
{
	return Point(_index % pMaze_->GetWidth(), _index / pMaze_->GetWidth());
}

int Stage::PointToIndex(Point _pos)
{
	return pMaze_->GetWidth() * _pos.y + _pos.x;
}
