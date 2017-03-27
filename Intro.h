#pragma once
#include "pch.h"
#include "Node.h"
#include "Cheat.h"

class Intro : public Node
{
private:
	Sprite* background;
public:
	Intro(){
		background = new Sprite("Scenes/intro.png");
		background->value.position = Vector2(640, 360);
		this->Attach(background);
	}

	void OnUpdate() override {
		background->color.a -= dt * 0.1;
		if (background->color.a < 0){
			enable = false;
			SceneManager::LoadScene("MainMenu");
		}
	}
};