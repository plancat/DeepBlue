#pragma once
#include "pch.h"
#include "MonsterBase.h"
#include "UI.h"

class NormalMonster : public MonsterBase
{
public:
	FillSprite* healthBar;
public:
	NormalMonster() : MonsterBase(3, 0.1f, 2.5f, 5){
		healthBar = new FillSprite("hp.png");
		healthBar->value.position = Vector2(0, -45);
		this->Attach(healthBar);
	}

	void Init(){
		int random = rand() % 2;
		lockOn = false;
		if (game_stage == 1)
		{
			if (random == 0){
				this->AddAnimation(new Animation("Unit/Nimo/Idle", 0.1, true));
				this->animation->Play();
				this->tag = "Nimo";
				health = 2;
			}
			else {
				this->AddAnimation(new Animation("Unit/Dori/Idle", 0.1, true));
				this->animation->Play();
				this->tag = "Dori";
				health = 2;
			}
		}
		else if (game_stage == 2)
		{
			if (random == 0){

			}
			else {

			}
		}
		healthBar->SetValue(health * 2);
	}

	void OnUpdate() override {
		MonsterBase::OnUpdate();
		this->value.position.y += 100 * dt;
		if (this->value.position.y > 725){
			this->enable = false;
			this->visible = false;
		}
	}

	void Damage(int power) override {
		MonsterBase::Damage(power);
		healthBar->SetValue(health * 50);
	}

	void Death() override {
		MonsterBase::Death();
		game_score += 150;
	}
};