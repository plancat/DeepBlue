#include "Player.h"
#include "Game.h"

Player* Player::instance = nullptr;

Player::Player() {
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

	for (int i = 0; i < 4; i++){
		addons[i] = new Sprite();
		addons[i]->AddAnimation(new Animation("Addon", 0.1, true));
		addons[i]->animation->Play();
		addons[i]->visible = false;
		addons[i]->enable = true;
		addons[i]->value.position = bulletPosition[i + 1];
		addons[i]->value.scale = { 0.32, 0.32 };
	}

	isHuddle = false;
	for (int i = 0; i < 30; i++){
		auto bullet = new Bullet(BulletType::PLAYER, Vector2(0, -1));
		bullet->visible = false;
		bullet->enable = false;
		bullet->value.scale = { 0.3f, 0.3f };
		bullet->value.rectScale = { 0.2f, 0.2f };
		bullet->collision = [=](Sprite* bullet, UnitBase* target)
		{
			player_combo += 1;
			Game::instance->ComboEnable();
			bullet->visible = false;
			bullet->enable = false;
			target->Damage(1);
		};
		bullets.push_back(bullet);
	}

	thirdBulletCnt = player_thirdBullet;
	hackBulletCnt = player_hackBullet;
	followBulletCnt = player_followBullet;
	weaponUpgrade = player_weaponUpgrade;

	delayComment.push([=](){
		for (auto it : bullets){
			this->parent->Attach(it);
		}
	});

	delayComment.push([=](){
		for (auto it : addons){
			this->parent->Attach(it);
		}
	});
}

void Player::KeyInput()
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
			}
			speed *= 0.2;
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

		// ±âº» ¾î·Ú
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

		// 3¹æÇâ ¾î·Ú
		if (input->KeyDown('X')){
			if (thirdBulletCnt > 0){
				thirdBulletCnt -= 1;
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
		}

		// ÇÙÅºµÎ
		if (input->KeyDown('C')){
			if (hackBulletCnt > 0){
				hackBulletCnt -= 1;
				auto bullet = getBullet();
				if (bullet != nullptr){
					Game::instance->Nuclear();
				}
			}
		}


		if (input->KeyDown(VK_LCONTROL)){
			if (followBulletCnt > 0){
				followBulletCnt -= 1;
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
}