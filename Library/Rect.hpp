#pragma once

#include "Vector2D.hpp"

struct Rect
{
	Vector2D<int> position;
	Vector2D<int> imageSize;

	inline Vector2D<int> GetCenter() const
	{
		return { position.x + imageSize.x / 2,
				 position.y + imageSize.y / 2 };
	}
};