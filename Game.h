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
#include "NormalMonster.h"

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
public:
	Game(){
		// 스테이지 지정
		game_stage = 1;
		editor = new Editor();
		this->Attach(editor);
		input = new Input();
		this->Attach(input);

		auto normal = new NormalMonster();
		normal->value = Editor::GetValue("Unit/Normal");
		normal->debug = true;
		// editor->AddEditor(normal, "Unit/Normal");
		this->Attach(normal);

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
		// editor->AddEditor(playerHealthBar, "Scene/Game/playerHealthBar");
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

		//if (input->KeyDown(VK_SPACE)){
		//	test->Attack();
		//}
	}
};