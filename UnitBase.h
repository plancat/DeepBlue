#pragma once
#include "pch.h"
#include "Sprite.h"

class UnitBase : public Sprite
{
public:
	static vector<UnitBase*> units;
public:
	int health;

	void Damage(int power){
		health -= power;
		if (health < 0){
			this->visible = false;
			this->enable = false;
		}
	}
};

vector<UnitBase*> UnitBase::units;