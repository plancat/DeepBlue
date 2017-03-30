#pragma once
#include "pch.h"
#include "MonsterBase.h"

class HardMonster : public MonsterBase
{
public:
	bool show = false;
public:
	HardMonster() : MonsterBase(20, 0.1f, 6, 40){

	}

	void Init(int monster){
		isDeath = false;

		if (game_stage == 1){
			if (monster == 1){
				this->AddAnimation(new Animation("Unit/Shark/Young/Idle", 0.1f, true));
				this->animation->Play();
				this->health = 100;
			}
			else if (monster == 2){
				this->AddAnimation(new Animation("Unit/Shark/Adult/Idle", 0.1f, true));
				this->animation->Play();
				this->health = 100;
			}
		}
		else
		{
			if (monster == 1){
				this->AddAnimation(new Animation("Unit/Axolotl/Young/Idle", 0.1f, true));
				this->animation->Play();
				this->health = 100;
			}
			else if (monster == 2){
				this->AddAnimation(new Animation("Unit/Axolotl/Adult/Idle", 0.1f, true));
				this->animation->Play();
				this->health = 100;
			}
		}
	}

	void OnUpdate() override
	{
		MonsterBase::OnUpdate();

		if (!show)
		{
			D3DXVec2Lerp(&value.position, &value.position, &Vector2(640, -360), 0.1f);
		}
		else
		{
			D3DXVec2Lerp(&value.position, &value.position, &Vector2(640, 80), 0.1f);
		}
	}

	void Hide(){
		show = false;
	}

	void Show() {
		show = true;
	}
};