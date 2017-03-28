#pragma once
#include "pch.h"
#include "Node.h"

class Intro : public Node
{
public:
	Sprite* prevScene;
	Sprite* nextScene;

	Sprite* background[3];
	int curIdx = 0;
public:
	Intro()
	{
		for (int i = 0; i < 3; i++){
			background[i] = new Sprite("Scenes/Ending/" + to_string(i + 1) + ".png");
			background[i]->value.position = { 640, 360 };
			background[i]->color.a = 0;
			this->Attach(background[i]);
		}
		curIdx = 0;
		prevScene = background[0];
		prevScene->color.a = 1.0f;
		nextScene = nullptr;
	}

	void OnUpdate() override {
		if (input->KeyDown(VK_SPACE)){
			curIdx += 1;
			if (curIdx > 2){
				prevScene = nullptr;
				nextScene = nullptr;
				SceneManager::LoadScene("MainMenu");
				return;
			}
			else
				nextScene = background[curIdx];
		}

		if (nextScene != nullptr){
			nextScene->color.a += dt;
			prevScene->color.a -= dt;
			if (nextScene->color > 1.0f && prevScene->color < 0.0f){
				prevScene = nextScene;
				nextScene = nullptr;
			}
		}
	}
};