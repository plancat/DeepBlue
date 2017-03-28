#pragma once
#include "pch.h"
#include "UnitBase.h"
#include "Bullet.h"

class MonsterBase : public UnitBase
{
private:
	// 공격 횟수
	int prevAttackCnt;
	int nextAttackCnt;
	// 공격당 딜레이
	float prevAttackDelay;
	float nextAttackDelay;
	// 다음 공격 시간
	float prevNextAttackDelay;
	float nextNextAttackDelay;

	bool isAttack = false;
	bool isAttackReady = false;
public:
	MonsterBase(int attackCnt, float attackDelay, float nextAttackDelay, int bulletCnt) :
		nextAttackCnt(attackCnt),
		nextAttackDelay(attackDelay),
		nextNextAttackDelay(nextAttackDelay) {
		prevAttackCnt = 0;
		prevAttackDelay = 0.0f;
		prevNextAttackDelay = 0.0f;

		for (int i = 0; i < bulletCnt; i++){
			auto bullet = new Bullet(BulletType::MONSTER, { 0, 1 });
			bullet->visible = false;
			bullet->enable = false;
			bullet->visible = false;
			bullet->enable = false;
			bullet->value.scale = { 0.3f, 0.3f };
			bullet->value.rectScale = { 0.2f, 0.2f };
			bullet->collision = [=](Sprite* bullet, UnitBase* target)
			{

			};
			bullets.push_back(bullet);
		}
	}

	void Attack(){
		if (isAttackReady){
			if (!isAttack){
				prevAttackCnt = 0;
				prevAttackDelay = 0.0f;
				prevNextAttackDelay = 0.0f;
				isAttackReady = false;
				isAttack = true;
			}
		}
	}

	void OnUpdate() override {
		UnitBase::OnUpdate();
		if (isAttack){
			prevAttackDelay += dt;
			if (prevAttackDelay >= nextAttackDelay){
				prevAttackCnt += 1;
				prevAttackDelay = 0.0f;

				cout << "Attack" << endl;

				auto bullet = getBullet();
				if (bullet != nullptr){
					bullet->texture = Texture::Load("Torpedo/Torpedo_1.png");
					bullet->value.angle = D3DXToRadian(180);
					bullet->dir = { 0, 1 };
					bullet->speed = 0.0f;
					bullet->value.position = this->value.position + Vector2(0, 5);
				}
			}
			if (prevAttackCnt >= nextAttackCnt){
				isAttack = false;
				prevAttackCnt = true;
			}
		}
		else
		{
			if (!isAttackReady){
				prevNextAttackDelay += dt;
				if (prevNextAttackDelay >= nextNextAttackDelay){
					prevNextAttackDelay = 0.0f;
					isAttackReady = true;
					Attack();
				}
			}
		}
	}
};