#include "Input.h"
#include "DxLib.h"


namespace
{
	//キーボード取得関連
	const int KEY_MAX = 255;
	char keyBuff[KEY_MAX];		//キーバッファ (現フレーム)
	char keyBuffOld[KEY_MAX];	//1つ前のキーバッファ(前フレーム) 
	char key_down[KEY_MAX];		//押された瞬間 
	char key_up[KEY_MAX];		//離された瞬間 
	char Key_Keep[KEY_MAX];		//押しっぱなし

	int mousePrev = 0;
	int mouseCurr = 0;
	int mouseDown;
	int mouseUp;
	int mouseHold;
}

void Input::KeyStateUpdate()
{
	memcpy_s(keyBuffOld, sizeof(char) * KEY_MAX, keyBuff, sizeof(char) * KEY_MAX); // 配列のコピー

	GetHitKeyStateAll(keyBuff);//全てのキーの状態を取得 

	mousePrev = mouseCurr;
	mouseCurr = GetMouseInput();

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (keyBuff[i] && keyBuffOld[i]) // 押しっぱなし判定（AND演算）
		{
			Key_Keep[i]++;
		}

		int key_xor = keyBuff[i] ^ keyBuffOld[i];	//前フレームと現フレームのxor
		if (key_xor)
		{
			Key_Keep[i] = 0;
		}
		key_down[i] = key_xor & keyBuff[i];		//押された瞬間 = (現フレームとkey_xorのAND) 
		key_up[i] = key_xor & keyBuffOld[i];	//離された瞬間 = (前フレームとkey_xorのAND) 
	}

}

bool Input::IsKeyUP(int keyCode)
{
	return(key_up[keyCode]); // ここでは計算済みの配列の中身を見ている
}

bool Input::IsKeyDown(int keyCode)
{
	return(key_down[keyCode]);
}

bool Input::IsKeyHold(int keyCode)
{
	return(Key_Keep[keyCode]);
}

// マウス系関数
bool Input::IsMouseDown(int _mouseKeyCode)
{
	mouseDown = mouseCurr ^ mousePrev;
	return mouseDown = mouseDown & (mouseCurr & _mouseKeyCode);
}

bool Input::IsMouseUp(int _mouseKeyCode)
{
	mouseUp = mouseCurr ^ mousePrev; // 1100 xor 1011 = 0111
	return mouseUp = mouseUp & (mousePrev & _mouseKeyCode);     // 0111 and (1011 and 0001) = 0111 and 0001 = 0001
}

bool Input::IsMouseHold(int _mouseKeyCode)
{
	mouseHold = mouseCurr & mousePrev; // 1011 and 1001 = 1001
	mouseHold = mouseHold & _mouseKeyCode; // 1001 and 0001 = 0001
	return mouseHold;                  // trueが返るはず
}

// 改良できそうなところ…
//		配列をvectorに
//			memcopyはもう古い