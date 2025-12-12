#include "MyDxLib.hpp"
#include <DxLib.h>

int MyDxLib::DrawExtendGraph(Vector2D<float> _position, Vector2D<int> _imageSize, int _graphHandle, bool _isTrans)
{
    return DxLib::DrawExtendGraphF(_position.x, _position.y,
                                   _position.x + (float)_imageSize.x, _position.y + (float)_imageSize.y,
                                   _graphHandle, (int)_isTrans);
}

int MyDxLib::DrawBox(Rect _box, uint32_t _color, bool _isFill, int32_t _frameThickness)
{
    return DxLib::DrawBox(_box.position.x,  _box.position.y,
                          _box.position.x + _box.imageSize.x,
                          _box.position.y + _box.imageSize.y,
                          _color,
                          (int)_isFill,
                          _frameThickness);
}
