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
	Maze::MazeState GetMazeState(Point _pos);

private:
	Explorer* pExplorer_;
	Maze*     pMaze_;

	std::vector<Maze::MazeState> mazeData_;
};