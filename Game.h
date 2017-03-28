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
#include "MonsterBase.h"

class Game : public Node
{
private:
	// Hud
	Node* playerHealthBar;
	Sprite* hearts[5];
public:
	Player* player;
	MonsterBase* test;
	Editor* editor;
	static int stage;
public:
	Game(){
		editor = new Editor();
		this->Attach(editor);
		input = new Input();
		this->Attach(input);

		test = new MonsterBase(4, 0.1f, 2, 20);
		this->Attach(test);

		PlayerInit();
		HudInit();

		cout << "Game" << endl;
	}

	void PlayerInit(){
		player = new Player();
		player->health = 5;
		player->value = Editor::GetValue("Unit/player");
		this->Attach(player);
	}

	void BackgroundInit(){

	}

	void HudInit(){
		playerHealthBar = new Node();
		this->Attach(playerHealthBar);
		playerHealthBar->value = Editor::GetValue("Scene/Game/playerHealthBar");
		editor->AddEditor(playerHealthBar, "Scene/Game/playerHealthBar");
		for (int i = 0; i < 5; i++){
			hearts[i] = new Sprite("heart.png");
			hearts[i]->value.position.y -= 40 * i;
			playerHealthBar->Attach(hearts[i]);
		}
	}

	void HudUpdate(){
		for (int i = 0; i < 5; i++){
			hearts[i]->visible = false;
		}
		for (int i = 0; i < player->health; i++){
			hearts[i]->visible = true;
		}
	}

	void OnUpdate() override {
		Cheat::Update();
		HudUpdate();

		if (input->KeyDown(VK_SPACE)){
			test->Attack();
		}
	}
};