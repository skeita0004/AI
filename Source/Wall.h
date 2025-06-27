#pragma once

#include "../Library/GameObject.h"
#include "global.h"

class Wall : public GameObject
{
public:
	Point position_;
	Rect wallSize_;
private:

};