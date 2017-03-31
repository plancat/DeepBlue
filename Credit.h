#pragma once
#include "pch.h"
#include "Node.h"
#include "Input.h"
#include "SceneManager.h"

class Credit : public Node
{
public:
	Sprite* background;
	Sprite* credit[2];
	bool isRedayCredit = false;
public:
	Credit(){
		input = new Input();
		this->Attach(input);
		isRedayCredit = false;
		if (player_sex == 0)
			background = new Sprite("Scenes/Credit/End_0.png");
		else
			background = new Sprite("Scenes/Credit/End_1.png");
		background->value.position = { 640, 360 };
		this->Attach(background);

		/* credit Á¦ÀÛ */
		credit[0] = new Sprite("Scenes/Credit/Credit_3.png");
		credit[0]->value.position = { 640, 360 + 300 };
		credit[0]->visible = false;
		this->Attach(credit[0]);

		credit[1] = new Sprite("Scenes/Credit/Credit_4.png");
		credit[1]->value.position = { 640, 360 + 720 + 300 };
		credit[1]->visible = false;
		this->Attach(credit[1]);
	}
	
	void OnUpdate() override
	{
		if (input->KeyDown(VK_SPACE)){
			if (!isRedayCredit){
				isRedayCredit = true;
				if (player_sex == 0)
					background->texture = Texture::Load("Scenes/Credit/Credit_0.png");
				else
					background->texture = Texture::Load("Scenes/Credit/Credit_1.png");
			}
		}

		if (isRedayCredit){
			for (int i = 0; i < 2; i++){
				credit[i]->visible = true;
				credit[i]->value.position.y -= 100 * dt;
				if (credit[1]->value.position.y < -360){
					SceneManager::LoadScene("Initial");
				}
			}
		}
	}
};