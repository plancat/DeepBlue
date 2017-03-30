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
public:
	Player() {
		isDeath = false;
		instance = this;
		this->AddAnimation(new Animation("Unit/Player", 0.1f, true));
		this->animation->Play();
		this->tag = "Player";
		bulletTime = 0.0f;
		speed = { 0, 0 };
		weaponUpgrade = 0;

		bulletPosition[0] = Vector2(0, 5);
		bulletPosition[1] = Vector2(25, 25);
		bulletPosition[2] = Vector2(-25, 25);
		bulletPosition[3] = Vector2(55, 55);
		bulletPosition[4] = Vector2(-55, 55);

		isHuddle = false;
		for (int i = 0; i < 30; i++){
			auto bullet = new Bullet(BulletType::PLAYER, Vector2(0, -1));
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

		thirdBulletCnt = player_thirdBullet;
		hackBulletCnt = player_hackBullet;
		followBulletCnt = player_followBullet;

		delayComment.push([=](){
			for (auto it : bullets){
				this->parent->Attach(it);
			}
		});
	}

	void OnUpdate() override {
		Sprite::OnUpdate();
		KeyInput();
	}

	void KeyInput()
	{
		if (dt > 0)
		{
			if (input->KeyStay(VK_DOWN))
				speed.y += 1;
			else if (input->KeyStay(VK_UP))
				speed.y -= 1;

			if (input->KeyStay(VK_LEFT)){
				speed.x -= 1;
				texture = Texture::Load("Unit/Player_Left.png");
				animation->Stop();
			}
			else if (input->KeyStay(VK_RIGHT)){
				speed.x += 1;
				texture = Texture::Load("Unit/Player_Right.png");
				animation->Stop();
			}

			if (input->KeyUp(VK_LEFT) || input->KeyUp(VK_RIGHT))
			{
				animation->Play();
			}

			speed *= 0.9f;

			if (isHuddle){
				prevHuddleTime += dt;
				if (prevHuddleTime >= 2.0f){
					prevHuddleTime = 0.0f;
					isHuddle = false;
					speed *= 0.2;
				}
			}

			value.position += speed;

			if (value.position.x < 0)
				value.position.x = 0;
			if (value.position.x > 1280)
				value.position.x = 1280;
			if (value.position.y < 0)
				value.position.y = 0;
			if (value.position.y > 720)
				value.position.y = 720;

			// 기본 어뢰
			if (input->KeyStay('Z')){
				bulletTime += dt;
				if (bulletTime >= 0.1f){
					bulletTime = 0.0f;

					for (int i = 0; i <= weaponUpgrade; i++)
					{
						auto bullet = getBullet();
						if (bullet != nullptr){
							// bullet->texture = Texture::Load("Torpedo/Torpedo_0.png");
							bullet->AddAnimation(new Animation("Torpedo/Torpedo0", 0.05, true));
							bullet->animation->Play();
							bullet->Init();
							bullet->value.angle = 0.0f;
							bullet->dir = { 0, -1 };
							bullet->speed = -200;
							bullet->value.position = this->value.position + bulletPosition[i];
						}
					}
				}
			}

			// 3방향 어뢰
			if (input->KeyDown('X')){
				for (int i = 0; i < 3; i++){
					auto bullet = getBullet();
					if (bullet != nullptr){
						bullet->texture = Texture::Load("Torpedo/Torpedo_1.png");
						bullet->Init();
						bullet->value.angle = 0.0f;
						bullet->dir = { 0, -1 };
						bullet->speed = (rand() % 280 + 250)* -1;
						if (i == 0){
							bullet->value.position = this->value.position + Vector2(0, -5);
						}
						else if (i == 1){
							bullet->value.position = this->value.position + Vector2(-15, 15);
						}
						else if (i == 2)
						{
							bullet->value.position = this->value.position + Vector2(15, 15);
						}
					}
				}
			}

			// 핵탄두
			if (input->KeyDown('C')){
				auto bullet = getBullet();
				if (bullet != nullptr){
					bullet->texture = Texture::Load("Torpedo/Torpedo_3.png");
					bullet->Init();
					bullet->dir = { 0, -1 };
					bullet->value.angle = 0.0f;
					bullet->speed = -200;
					bullet->value.position = this->value.position + Vector2(0, -5);
				}
			}


			if (input->KeyDown(VK_LCONTROL)){
				auto bullet = getBullet();
				if (bullet != nullptr){
					bullet->texture = Texture::Load("Torpedo/Torpedo_3.png");
					bullet->Init();
					bullet->FindTarget();
					bullet->value.position = this->value.position + Vector2(0, -5);
					bullet->speed = 100;
				}
			}
		}
	}

	// 부딪쳤을 때
	void HuddleOn(){
		isHuddle = true;
		prevHuddleTime = 0.0f;
	}

	void WeaponUpgrade(){

	}

	// pch에 선언된 미사일 개수를 변경한다.
	void Save(){
		player_thirdBullet = thirdBulletCnt;
		player_hackBullet = hackBulletCnt;
		player_followBullet = followBulletCnt;
	}
};