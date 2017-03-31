#pragma once
#include "pch.h"
#include "UnitBase.h"
#include "Bullet.h"
#include "Patern.h"

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
	Patern* patern;
public:
	MonsterBase(int attackCnt, float attackDelay, float nextAttackDelay, int bulletCnt) :
		nextAttackCnt(attackCnt),
		nextAttackDelay(attackDelay),
		nextNextAttackDelay(nextAttackDelay) {
		prevAttackCnt = 0;
		prevAttackDelay = 0.0f;
		prevNextAttackDelay = 0.0f;

		patern = new Patern();

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
				bullet->visible = false;
				bullet->enable = false;

				target->Damage(1);
			};
			bullets.push_back(bullet);
		}

		delayComment.push([=](){
			for (auto it : bullets)
				this->parent->Attach(it);
		});
	}

	~MonsterBase(){
		delete patern;
	}

	void Attack(){
		if (isAttackReady){
			if (!isAttack){
				prevAttackCnt = 0;
				prevAttackDelay = 0.0f;
				prevNextAttackDelay = 0.0f;
				isAttackReady = false;
				isAttack = true;

				int rd = rand() % 3;

				switch (rd){
				case 0:
					patern->paternType = PaternType::ONE_LINE;
					break;
				case 1: 
					patern->paternType = PaternType::PLAYER;
					break;
				case 2:
					patern->paternType = PaternType::BUTTERFLY;
					break;
				}
			}
		}
	}

	void OnUpdate() override {
		UnitBase::OnUpdate();
		DamageEffectUpdate();

		if (isAttack){
			prevAttackDelay += dt;
			if (prevAttackDelay >= nextAttackDelay){
				prevAttackCnt += 1;
				prevAttackDelay = 0.0f;
				// patern
				patern->PaternAttack(this);
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