#pragma once
#include "UnitBase.h"
#include "Input.h"

class Player : public UnitBase
{
private:
	float bulletTime;
	int thirdBulletCnt;
	int finalBulletCnt;
public:
	Vector2 speed;
public:
	Player() {
		this->AddAnimation(new Animation("Unit/Player", 0.1f, true));
		this->animation->Play();
		speed = { 0, 0 };
		this->tag = "Player";
		// this->debug = true;
		bulletTime = 0.0f;

		for (int i = 0; i < 10; i++){
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
	}

	~Player(){

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
			if (input->KeyStay(VK_UP))
				speed.y -= 1;
			if (input->KeyStay(VK_LEFT))
				speed.x -= 1;
			if (input->KeyStay(VK_RIGHT))
				speed.x += 1;

			speed *= 0.9f;

			value.position += speed;

			if (value.position.x < 0)
				value.position.x = 0;
			if (value.position.x > 1280)
				value.position.x = 1280;
			if (value.position.y < 0)
				value.position.y = 0;
			if (value.position.y > 720)
				value.position.y = 720;

			// ±âº» ¾î·Ú
			if (input->KeyStay('Z')){
				bulletTime += dt;
				if (bulletTime >= 0.1f){
					bulletTime = 0.0f;
					auto bullet = getBullet();
					if (bullet != nullptr){
						bullet->texture = Texture::Load("Torpedo/Torpedo_0.png");
						bullet->Init();
						bullet->value.angle = 0.0f;
						bullet->dir = { 0, -1 };
						bullet->speed = -200;
						bullet->value.position = this->value.position + Vector2(0, -5);
					}
				}
			}

			// 3¹æÇâ ¾î·Ú
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

			// ÇÙÅºµÎ
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
					bullet->FindTarget();
					bullet->Init();
					bullet->value.position = this->value.position + Vector2(0, -5);
					bullet->speed = 100;
				}
			}
		}
	}
};