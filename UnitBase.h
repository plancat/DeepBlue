#pragma once
#include "pch.h"
#include "Sprite.h"

class UnitBase : public Sprite
{
public:
	static vector<UnitBase*> units;
public:
	int health;
	int power;
	Vector2 speed;
};

vector<UnitBase*> UnitBase::units;