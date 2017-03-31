#include "Patern.h"
#include "MonsterBase.h"
#include "Player.h"

void Patern::PaternAttack(MonsterBase* monsterbase){
	switch (paternType){
	case PaternType::ONE_LINE:
	{
		auto bullet = monsterbase->getBullet();
		if (bullet != nullptr){
			bullet->Init();
			bullet->texture = Texture::Load("Bullet/0_0.png");
			bullet->dir = { 0, 1 };
			bullet->value.rectScale = { 0.3, 0.3 };
			bullet->speed = 0.0f;
			bullet->value.angle = 0.0f;
			bullet->value.position = monsterbase->value.position + Vector2(0, 5);
		}
	}
		break;
	case PaternType::PLAYER:
	{
		auto bullet = monsterbase->getBullet();
		if (bullet != nullptr){
			bullet->Init();
			bullet->texture = Texture::Load("Bullet/0_0.png");
			auto dir = Player::instance->value.position - monsterbase->value.position;
			D3DXVec2Normalize(&dir, &dir);
			bullet->dir = dir;
			bullet->value.rectScale = { 0.3, 0.3 };
			bullet->speed = 0.0f;
			bullet->value.position = monsterbase->value.position + Vector2(0, 5);
		}
	}
		break;
	case PaternType::BUTTERFLY:
	{
		for (int i = 0; i < 360; i += 30){
			auto bullet = monsterbase->getBullet();
			if (bullet != nullptr){
				bullet->Init();
				bullet->texture = Texture::Load("Bullet/0_0.png");
				float posx = sinf(i);
				float posy = cosf(i);
				bullet->dir = { posx, posy };
				bullet->value.rectScale = { 0.3, 0.3 };
				bullet->speed = 0.0f;
				bullet->value.position = monsterbase->value.position + Vector2(0, 5);
			}
		}
	}
		break;
	}
}