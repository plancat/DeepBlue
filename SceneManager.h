#pragma once
#include "Node.h"
#include "pch.h"
#include "Sprite.h"

#include "MainMenu.h"
#include "Intro.h"
#include "Initial.h"
#include "Game.h"
#include "Ending.h"

class SceneManager
{
public:
	static Node* curScene;
	static Node* nextScene;
public:
	static void LoadScene(const string& name)
	{
		Sprite::Clear();
		if (name.compare("MainMenu") == 0)
		{
			nextScene = new MainMenu();
		}
		else if (name.compare("Initial") == 0)
		{
			nextScene = new Initial();
		}
		else if (name.compare("Ending") == 0)
		{
			nextScene = new Ending();
		}
		else if (name.compare("Intro") == 0)
		{
			nextScene = new Intro();
		}
		else if (name.compare("Game") == 0)
		{
			nextScene = new Game();
		}
	}

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