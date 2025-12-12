#pragma once

#include "Vector2D.hpp"
#include "Rect.hpp"
#include <cstdint>

namespace MyDxLib
{
	/// <summary>
	/// MyDxLibのDrawExtendGraph関数
	/// 引数をVector2で渡せるので、記述量を減らせる
	/// </summary>
	/// <param name="_position">対象の座標</param>
	/// <param name="_imageSize">対象の大きさ</param>
	/// <param name="_graphHandle">対象の画像ハンドル</param>
	/// <param name="_isTrans">透過させるか</param>
	/// <returns>エラーコード</returns>
	int DrawExtendGraph(Vector2D<float> _position, Vector2D<int> _imageSize, int _graphHandle, bool _isTrans);

	int DrawBox(Rect _box, uint32_t _color, bool _isFill, int32_t _frameThickness);
}