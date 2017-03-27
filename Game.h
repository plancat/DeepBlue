#pragma once
#include "pch.h"
#include "Node.h"
#include "Sprite.h"
#include "UI.h"
#include "Input.h"
#include "Cheat.h"
#include "Editor.h"
#include "SceneManager.h"
#include "Player.h"

class Game : public Node
{
public:
	Editor* editor;
	static int stage;
public:
	Game(){
		editor = new Editor();
		this->Attach(editor);

		PlayerInit();

		cout << "Game" << endl;
	}

	void PlayerInit(){
		Player* player = new Player();
		player->value = Editor::GetValue("Unit/player");
		// editor->AddEditor(player, "Unit/player");
		this->Attach(player);
	}

	void BackgroundInit(){

	}

	void OnUpdate() override {
		Input::Update();
		Cheat::Update();
	}
};