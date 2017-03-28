#pragma once
#include "UnitBase.h"
#include "Input.h"
#include "Bullet.h"

class Player : public UnitBase
{
private:
	vector<Bullet*> bullets;
	float bulletTime;
public:
	Vector2 speed;
public:
	Player() {
		this->AddAnimation(new Animation("Unit/Player", 0.1f, true));
		this->animation->Play();
		speed = { 0, 0 };
		this->tag = "Player";
		this->debug = true;
		bulletTime = 0.0f;

		for (int i = 0; i < 10; i++){
			auto bullet = new Bullet(BulletType::PLAYER, Vector2(0, -1));
			bullet->visible = false;
			bullet->enable = false;
			bullet->collision = [=](Sprite* bullet)
			{

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
		if (dt >= 0){
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

			if (input->KeyStay('Z')){
				bulletTime += dt;
				if (bulletTime >= 0.1f){
					bulletTime = 0.0f;
					auto bullet = getBullet();
					if (bullet != nullptr){
						bullet->texture = Texture::Load("Torpedo/Torpedo_0.png");
						bullet->value.scale = { 0.3f, 0.3f };
						bullet->value.rectScale = { 0.2f, 0.2f };
						bullet->speed = -200;
						bullet->value.position = this->value.position + Vector2(0, -5);
					}
				}
			}
		}
	}

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
};