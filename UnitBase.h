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
	bool isDeath;

	bool isDamageEffect = false;
	int damageEffectCnt;
	float prevDamageDelay = 0.0f;
	bool isDamageColor = false;
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
		DamageEffect();
	}

	virtual void Death(){
		this->visible = false;
		this->enable = false;
		lockOn = false;
	}

	void DamageEffect(){
		isDamageEffect = true;
		damageEffectCnt = 0;
		prevDamageDelay = 0.0f;
	}

	void DamageEffectUpdate(){
		if (isDamageEffect){
			prevDamageDelay += dt;
			if (prevDamageDelay >= 0.1f){
				prevDamageDelay = 0.0f;
				if (!isDamageColor){
					isDamageColor = true;
					color.a = 0.5;
				}
				else
				{
					isDamageColor = false;
					color.a = 1;
				}

				damageEffectCnt += 1;
				if (damageEffectCnt > 6){
					isDamageEffect = false;
					color.a = 1;
				}
			}
		}
	}
};