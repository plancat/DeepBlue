#pragma once
#include "UnitBase.h"
#include "Input.h"

class Player : public UnitBase
{
private:
	bool isHuddle;
	float prevHuddleTime;
public:
	float bulletTime;
	int thirdBulletCnt;
	int hackBulletCnt;
	int followBulletCnt;
public:
	static Player* instance;
	Vector2 speed;
	int weaponUpgrade;
	Vector2 bulletPosition[5];
	Sprite* addons[4];
public:
	Player();

	void OnUpdate() override {
		Sprite::OnUpdate();
		KeyInput();
		DamageEffectUpdate();

		for (int i = 0; i < 4; i++){
			addons[i]->visible = false;
			addons[i]->enable = false;
		}
		if (weaponUpgrade > 0){
			if (weaponUpgrade > 4)
				weaponUpgrade = 4;
			for (int i = 0; i < weaponUpgrade; i++){
				addons[i]->visible = true;
				addons[i]->enable = true;
				addons[i]->value.position = this->value.position + bulletPosition[i + 1];
			}
		}
	}

	void KeyInput();

	// 부딪쳤을 때
	void HuddleOn(){
		isHuddle = true;
		prevHuddleTime = 0.0f;
		Damage(1);
	}

	void WeaponUpgrade(){
		weaponUpgrade += 1;
		if (weaponUpgrade > 4)
			weaponUpgrade = 4;
	}

	// pch에 선언된 미사일 개수를 변경한다.
	void Save(){
		player_thirdBullet = thirdBulletCnt;
		player_hackBullet = hackBulletCnt;
		player_followBullet = followBulletCnt;
	}

	void Damage(int power) override {
		UnitBase::Damage(power);
		player_combo = 0;
	}
};