#pragma once
#include "Node.h"
#include "pch.h"
#include "Sprite.h"

class SceneManager
{
public:
	static Node* curScene;
	static Node* nextScene;
public:
	static void LoadScene(const string& name);
	static void SceneUpdate(){
		if (nextScene != nullptr){
			if (curScene != nullptr)
				curScene->Destroy();
			curScene = nextScene;
			nextScene = nullptr;
		}

		Sprite::DrawStart();
		Node::RootUpdate();
		Node::RootDraw();
		Sprite::DrawEnd();
		Sprite::LineDraw();
	}
};