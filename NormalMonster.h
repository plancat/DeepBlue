#pragma once
#include "pch.h"
#include "MonsterBase.h"
#include "UI.h"

class NormalMonster : public MonsterBase
{
public:
	Animation* idle;
	Animation* death;
	FillSprite* healthBar;
public:
	NormalMonster() : MonsterBase(3, 0.1f, 2.5f, 10){
		healthBar = new FillSprite("hp.png", 80, health);
		healthBar->fillSprite->value.scale.y = 0.5f;
		healthBar->value.position = Vector2(0, -45);
		this->Attach(healthBar);
		isDeath = true;
	}

	void Init(){
		if (this == nullptr)
			return;

		isDeath = false;
		int random = rand() % 2;
		lockOn = false;
		if (game_stage == 1)
		{
			if (random == 0){
				idle = new Animation("Unit/Nimo/Idle", 0.1, true);
				death = new Animation("Unit/Nimo/Death", 0.1, false, false);
				this->AddAnimation(idle);
				this->animation->Play();
				this->tag = "Nimo";
				health = 2;
			}
			else {

				idle = new Animation("Unit/Dori/Idle", 0.1, true);
				death = new Animation("Unit/Dori/Death", 0.1, false, false);
				this->AddAnimation(idle);
				this->animation->Play();
				this->tag = "Dori";
				health = 2;
			}
		}
		else if (game_stage == 2)
		{
			if (random == 0){
				idle = new Animation("Unit/Blobfish/Idle", 0.1, true);
				death = new Animation("Unit/Blobfish/Death", 0.1, false, false);
				this->AddAnimation(idle);
				this->animation->Play();
				this->tag = "Football";
				health = 4;
			}
			else {
				idle = new Animation("Unit/Football/Idle", 0.1, true);
				death = new Animation("Unit/Football/Death", 0.1, false, false);
				this->AddAnimation(idle);
				this->animation->Play();
				this->tag = "Dori";
				health = 4;
			}
		}

		healthBar->maxValue = health;
		healthBar->SetValue(health);
	}

	void OnUpdate() override {
		if (!isDeath){
			D3DXColorLerp(&color, &color, &Color(1, 1, 1, 1), 0.1f);
			MonsterBase::OnUpdate();
			this->value.position.y += 100 * dt;
			if (this->value.position.y > 725){
				this->enable = false;
				this->visible = false;
			}
		}
		else
		{
			// UnitBase::OnUpdate();
			D3DXColorLerp(&color, &color, &Color(0, 0, 0, 0), 0.1f);
			if (this->color.a < 0.05f)
			{
				this->visible = false;
				this->enable = false;
			}
		}
	}

	void Damage(int power) override {
		health -= power;
		if (lockOn)
			lockOn = false;
		if (health <= 0){
			if (!isDeath){
				isDeath = true;
				Death();
			}
		}
		DamageEffect();
		healthBar->SetValue(health);
	}

	void Death() override {
		lockOn = false;
		this->animation->Stop();
		this->AddAnimation(death);
		this->animation->Play();
		game_score += 70;
	}
};