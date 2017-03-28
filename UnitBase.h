#pragma once
#include "pch.h"
#include "Sprite.h"
#include "Bullet.h"

class UnitBase : public Sprite
{
public:
	vector<Bullet*> bullets;
	static vector<UnitBase*> units;
public:
	UnitBase(){
		units.push_back(this);
	}

	int health;

	Bullet* getBullet(){
		for (auto it : bullets){
			if (!it->visible)
			{
				it->enable = true;
				it->visible = true;
				return it;
			}
		}
	}

	void Damage(int power){
		health -= power;
		if (health < 0){
			Death();
		}
	}

	virtual void Death(){
		this->visible = false;
		this->enable = false;
	}
};