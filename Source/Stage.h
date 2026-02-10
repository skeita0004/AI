#pragma once

#include "../Library/GameObject.h"
#include "Screen.h"
#include "global.h"
#include "Maze.hpp"

class Explorer;

class Stage : public GameObject
{
public:
	Stage();
	~Stage();

	void Update() override;
	void Draw() override;

	void SetMazeState(Point _pos, Maze::MazeState _state);
	void SetStepCount(Point _pos, int _stepCount);
	int  GetStepCount(Point _pos);

	Maze::MazeState GetMazeState(Point _pos);

	Point IndexToPoint(int _index);
	int   PointToIndex(Point _pos);

	Maze* GetMazeP()
	{
		return pMaze_;
	}

private:
	Explorer* pExplorer_;
	Maze*     pMaze_;

	struct TileInfo
	{
		Maze::MazeState mzState;
		int             stepCount;
	};

	std::vector<TileInfo> mazeData_;
};