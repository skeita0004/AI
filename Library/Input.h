#pragma once

namespace Input 
{
	//�L�[�{�[�h�擾�֘A
	void KeyStateUpdate();
	bool IsKeyUP(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsKeyHold(int keyCode);

	bool IsMouseDown(int _mouceKeyCode);
	bool IsMouseUp(int _mouceKeyCode);
	bool IsMouseHold(int _mouceKeyCode);
}