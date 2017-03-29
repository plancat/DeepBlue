#pragma once
#include "pch.h"
#include "Sprite.h"
#include "Bullet.h"

class UnitBase : public Sprite
{
public:
	vector<Bullet*> bullets;
	static vector<UnitBase*> units;
	bool lockOn;
public:
	UnitBase(){
		units.push_back(this);
		lockOn = false;
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

	virtual void Damage(int power){
		health -= power;
		if (health <= 0){
			Death();
		}
	}

	virtual void Death(){
		this->visible = false;
		this->enable = false;
		lockOn = false;
	}
};