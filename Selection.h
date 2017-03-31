#pragma once
#include "pch.h"
#include "Node.h"
#include "Input.h"
#include "Sprite.h"
#include "SceneManager.h"

class Selection : public Node
{
public:
	Sprite* character;
public:
	Selection(){
		input = new Input();
		this->Attach(input);

		character = new Sprite("UI/UI_23.png");
		character->value.position = { 640, 360 };
		this->Attach(character);
	}

	void OnUpdate(){
		if (input->KeyDown(VK_LEFT)){
			if (player_sex == 0)
				return;
			player_sex = 0;
			character->texture = Texture::Load("UI/UI_23.png");
		}
		if (input->KeyDown(VK_RIGHT)){
			if (player_sex == 1)
				return;
			player_sex = 1;
			character->texture = Texture::Load("UI/UI_24.png");
		}
		if (input->KeyDown(VK_SPACE))
		{
			game_stage = 1;
			SceneManager::LoadScene("Game");
		}
	}
};