#pragma once
#include "UnitBase.h"
#include "Input.h"
#include "Bullet.h"

class Player : public UnitBase
{
public:
	vector<Bullet*> bullets;
	float bulletTime;
public:
	Player() {
		this->AddAnimation(new Animation("Unit/Player", 0.1f, true));
		this->animation->Play();
		speed = { 0, 0 };
		this->tag = "Player";
		this->debug = true;
		bulletTime = 0.0f;

		for (int i = 0; i < 30; i++){
			auto bullet = new Bullet(BulletType::PLAYER, Vector2(0, -1), 700);
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
			if (Input::KeyPress(VK_DOWN)){
				speed.y += 1;
			}
			if (Input::KeyPress(VK_UP)){
				speed.y -= 1;
			}
			if (Input::KeyPress(VK_LEFT)){
				speed.x -= 1;
			}
			if (Input::KeyPress(VK_RIGHT)){
				speed.x += 1;
			}

			speed *= 0.9f;

			value.position += speed;

			if (Input::KeyPress('Z')){
				bulletTime += dt;
				if (bulletTime >= 0.1f){
					bulletTime = 0.0f;
					for (auto it : bullets){
						if (!it->visible)
						{
							it->enable = true;
							it->visible = true;
							it->value.position = this->value.position + Vector2(0, -5);
							break;
						}
					}
				}
			}
		}
	}
};