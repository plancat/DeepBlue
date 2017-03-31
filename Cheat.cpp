#include "Cheat.h"
#include "Input.h"
#include "SceneManager.h"
#include "Player.h"

bool Cheat::god = false;

void Cheat::Update(){
	if (input->KeyDown(VK_F1)){
		if (god)
			god = false;
		else
			god = true;
	}
	if (input->KeyDown(VK_F2)){
		Player::instance->WeaponUpgrade();
	}
	if (input->KeyDown(VK_F3)){
		Player::instance->hackBulletCnt += 1;
		if (Player::instance->hackBulletCnt > 9)
			Player::instance->hackBulletCnt = 9;
	}
	if (input->KeyDown(VK_F4)){
		SceneManager::LoadScene("MainMenu");
	}
	if (input->KeyDown(VK_F5)){
		SceneManager::LoadScene("Game");
	}
	if (input->KeyDown(VK_F6)){
		SceneManager::LoadScene("Game");
	}

	if (god)
		Player::instance->health = 5;
}