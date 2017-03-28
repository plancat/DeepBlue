#include "Cheat.h"
#include "Input.h"
#include "SceneManager.h"

void Cheat::Update(){
	if (input->KeyDown(VK_F1)){

	}
	if (input->KeyDown(VK_F2)){

	}
	if (input->KeyDown(VK_F3)){

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
}