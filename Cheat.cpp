#include "Cheat.h"
#include "Input.h"
#include "SceneManager.h"

void Cheat::Update(){
	if (Input::KeyDown(VK_F1)){

	}
	if (Input::KeyDown(VK_F2)){

	}
	if (Input::KeyDown(VK_F3)){

	}
	if (Input::KeyDown(VK_F4)){
		SceneManager::LoadScene("MainMenu");
	}
	if (Input::KeyDown(VK_F5)){
		SceneManager::LoadScene("Game");
	}
	if (Input::KeyDown(VK_F6)){
		SceneManager::LoadScene("Game");
	}
}