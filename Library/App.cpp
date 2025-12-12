#include "App.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "DeltaTime.h"
#include <DxLib.h>
#include "Input.h"

void AppInit()
{
	ObjectManager::Init();
	SceneManager::Init();
	DeltaTime::Init();
}

void AppUpdate()
{
	Input::KeyStateUpdate();
	SceneManager::Update();
	ObjectManager::Update();
}

void AppDraw()
{
	DeltaTime::Refresh();
	SceneManager::Draw();
	ObjectManager::Draw();
}

void AppRelease()
{
	ObjectManager::Release();
	SceneManager::Release();
}

bool AppIsExit()
{
	return SceneManager::IsExit();
}