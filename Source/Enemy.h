#pragma once

#include "../Library/GameObject.h"
#include "global.h"

class Enemy : public GameObject
{
	Pointf position_;
	int hImage_;
	DIR currDir;
	DIR nextDir;
	std::string dir;
	float dirTimer_;
	float moveTimer_;
	float animTimer_;
	int* anim;

public:
	Enemy(Pointf _position);
	~Enemy();

	void Update() override;
	void Draw() override;

	void SetPosition(Pointf _position) { position_ = _position; }
};