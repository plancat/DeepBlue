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
#include "HardMonster.h"
#include "NormalMonster.h"

class Game : public Node
{
private:
	// Hud
	Node* playerHealthBar;
	Sprite* hearts[5];

	Editor* editor;
	float prevMonsterCreate;
	float nextMonsterCreate;

	// Unit
	Player* player;
	HardMonster* hardMonster;
	vector<NormalMonster*> monsters;
	vector<Sprite*> backgrounds;

	bool pause = false;
	bool showBoss;
	bool boss1_clear;
	bool boss2_clear;
public:
	Game(){
		editor = new Editor();
		this->Attach(editor);
		input = new Input();
		this->Attach(input);
		// 스테이지 지정
		game_stage = 1;

		if (game_stage == 1){
			backgrounds = Editor::GetBackgrounds("Scene/Game/Game1");
		}
		else if (game_stage == 2){
			backgrounds = Editor::GetBackgrounds("Scene/Game/Game2");
		}
		for (auto it : backgrounds)
			this->Attach(it);

		hardMonster = new HardMonster();
		hardMonster->Hide();
		hardMonster->Init(1);
		// hardMonster->debug = true;
		hardMonster->value = Editor::GetValue("Unit/Hard");
		this->Attach(hardMonster);
		// editor->AddEditor(hardMonster, "Unit/Hard");s

		showBoss = false;
		boss1_clear = false;
		boss2_clear = false;

		prevMonsterCreate = 0.0f;
		nextMonsterCreate = 3;

		for (int i = 0; i < 10; i++){
			auto normal = new NormalMonster();
			normal->value = Editor::GetValue("Unit/Normal");
			// normal->debug = true;
			normal->Init();
			normal->visible = false;
			normal->enable = false;
			this->Attach(normal);
			monsters.push_back(normal);
		}

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

	void BackgroundUpdate(){
		for (auto it : backgrounds){
			if (it->tag.compare("bg0") == 0){
				it->value.position.y += 100 * dt;
			}
			else if (it->tag.compare("bg1") == 0){
				it->value.position.y += 200 * dt;
			}
			else if (it->tag.compare("bg2") == 0){
				it->value.position.y += 300 * dt;
			}
			else if (it->tag.compare("bg3") == 0){
				it->value.position.y += 400 * dt;
			}

			if (it->value.position.y >= (720 + 360)){
				it->value.position.y = -360;
			}
		}
	}

	void HudInit(){
		playerHealthBar = new Node();
		this->Attach(playerHealthBar);
		playerHealthBar->value = Editor::GetValue("Scene/Game/playerHealthBar");
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
		if (input->KeyDown(VK_ESCAPE)){
			if (!pause){
				pause = true;
				dt = 0.0f;
			}
		}

		Cheat::Update();

		HudUpdate();
		BackgroundUpdate();

		prevMonsterCreate += dt;
		if (prevMonsterCreate >= nextMonsterCreate){
			prevMonsterCreate = 0.0f;

			auto monster = getMonster();
			static_cast<NormalMonster*>(monster)->Init();
			monster->value.position = { (float)(rand() % 1180 + 100), (float)-3 };
		}
	}

	UnitBase* getMonster(){
		for (auto it : monsters){
			if (!it->visible || !it->enable){
				it->visible = true;
				it->enable = true;
				return it;
			}
		}
	}
};