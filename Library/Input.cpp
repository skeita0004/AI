#include "Input.h"
#include "DxLib.h"


namespace
{
	//�L�[�{�[�h�擾�֘A
	const int KEY_MAX = 255;
	char keyBuff[KEY_MAX];		//�L�[�o�b�t�@ (���t���[��)
	char keyBuffOld[KEY_MAX];	//1�O�̃L�[�o�b�t�@(�O�t���[��) 
	char key_down[KEY_MAX];		//�����ꂽ�u�� 
	char key_up[KEY_MAX];		//�����ꂽ�u�� 
	char Key_Keep[KEY_MAX];		//�������ςȂ�

	int mousePrev = 0;
	int mouseCurr = 0;
	int mouseDown;
	int mouseUp;
	int mouseHold;
}

void Input::KeyStateUpdate()
{
	memcpy_s(keyBuffOld, sizeof(char) * KEY_MAX, keyBuff, sizeof(char) * KEY_MAX); // �z��̃R�s�[

	GetHitKeyStateAll(keyBuff);//�S�ẴL�[�̏�Ԃ��擾 

	mousePrev = mouseCurr;
	mouseCurr = GetMouseInput();

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (keyBuff[i] && keyBuffOld[i]) // �������ςȂ�����iAND���Z�j
		{
			Key_Keep[i]++;
		}

		int key_xor = keyBuff[i] ^ keyBuffOld[i];	//�O�t���[���ƌ��t���[����xor
		if (key_xor)
		{
			Key_Keep[i] = 0;
		}
		key_down[i] = key_xor & keyBuff[i];		//�����ꂽ�u�� = (���t���[����key_xor��AND) 
		key_up[i] = key_xor & keyBuffOld[i];	//�����ꂽ�u�� = (�O�t���[����key_xor��AND) 
	}

}

bool Input::IsKeyUP(int keyCode)
{
	return(key_up[keyCode]); // �����ł͌v�Z�ς݂̔z��̒��g�����Ă���
}

bool Input::IsKeyDown(int keyCode)
{
	return(key_down[keyCode]);
}

bool Input::IsKeyHold(int keyCode)
{
	return(Key_Keep[keyCode]);
}

// �}�E�X�n�֐�
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
	return mouseHold;                  // true���Ԃ�͂�
}

// ���ǂł������ȂƂ���c
//		�z���vector��
//			memcopy�͂����Â�