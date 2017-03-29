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
	Node* backgroundLayer;

	Sprite* bossHealthBackground;
	FillSprite* bossHealthBar;

	Editor* editor;
	float prevMonsterCreate;
	float nextMonsterCreate;

	// Unit
	Player* player;
	HardMonster* hardMonster;
	vector<NormalMonster*> monsters;
	vector<Sprite*> backgrounds;

	Node* pauseLayer;
	Node* clearLayer;
	Node* failLayer;

	bool pause = false;
	bool boss1_clear;
public:
	Game(){
		editor = new Editor();
		this->Attach(editor);
		input = new Input();
		this->Attach(input);
		backgroundLayer = new Node();
		this->Attach(backgroundLayer);

		bossHealthBar = nullptr;

		if (game_stage == 1)
			backgrounds = Editor::GetBackgrounds("Scene/Game/Game1");
		else if (game_stage == 2)
			backgrounds = Editor::GetBackgrounds("Scene/Game/Game2");

		for (auto it : backgrounds){
			backgroundLayer->Attach(it);
		}

		hardMonster = new HardMonster();
		hardMonster->Hide();
		hardMonster->Init(1);
		hardMonster->value = Editor::GetValue("Unit/Hard");
		this->Attach(hardMonster);

		boss1_clear = false;
		prevMonsterCreate = 0.0f;
		nextMonsterCreate = 3;

		for (int i = 0; i < 10; i++){
			auto normal = new NormalMonster();
			normal->value = Editor::GetValue("Unit/Normal");
			normal->Init();
			normal->visible = false;
			normal->enable = false;
			this->Attach(normal);
			monsters.push_back(normal);
		}

		PlayerInit();
		HudInit();
		LayerInit();
	}

	void LayerInit(){
		pauseLayer = new Node();
		pauseLayer->visible = false;
		pauseLayer->enable = false;
		this->Attach(pauseLayer);
		Sprite* background = new Sprite("UI/UI_12.png");
		background->value.position = { 640, 360 };
		pauseLayer->Attach(background);

		auto button = new Button("UI/UI_9.png");
		button->value = Editor::GetValue("Scene/Game/P_RESUME");
		button->onClick = [=]()
		{
			dt = 0.016;
			pauseLayer->visible = false;
			pauseLayer->enable = false;
			pause = false;
		};
		pauseLayer->Attach(button);

		button = new Button("UI/UI_7.png");
		button->value = Editor::GetValue("Scene/Game/P_RETRY");
		button->onClick = [=]()
		{
			dt = 0.016;
			SceneManager::LoadScene("Game");
		};
		pauseLayer->Attach(button);

		button = new Button("UI/UI_8.png");
		button->value = Editor::GetValue("Scene/Game/P_EXIT");
		button->onClick = [=]()
		{
			dt = 0.016;
			SceneManager::LoadScene("MainMenu");
		};
		pauseLayer->Attach(button);

		// ====================================
		clearLayer = new Node();
		clearLayer->enable = false;
		clearLayer->visible = false;
		this->Attach(clearLayer);
		background = new Sprite("UI/UI_4.png");
		background->value.position = { 640, 360 };
		clearLayer->Attach(background);

		button = new Button("UI/UI_6.png");
		button->value = Editor::GetValue("Scene/Game/C_NEXT");
		button->onClick = [=]()
		{
			dt = 0.016;
			if (game_stage == 1){
				game_stage = 2;
				SceneManager::LoadScene("Game");
			}
			else{
				SceneManager::LoadScene("Ending");
			}

		};
		clearLayer->Attach(button);

		button = new Button("UI/UI_7.png");
		button->value = Editor::GetValue("Scene/Game/C_EXIT");
		button->onClick = [=]()
		{
			dt = 0.016;
			SceneManager::LoadScene("Game");
		};
		clearLayer->Attach(button);

		// ====================================
		failLayer = new Node();
		failLayer->enable = false;
		failLayer->visible = false;
		this->Attach(failLayer);
		background = new Sprite("UI/UI_5.png");
		background->value.position = { 640, 360 };
		failLayer->Attach(background);

		button = new Button("UI/UI_7.png");
		button->value = Editor::GetValue("Scene/Game/F_RETRY");
		button->onClick = [=]()
		{
			dt = 0.016;
			SceneManager::LoadScene("Game");
		};
		failLayer->Attach(button);

		button = new Button("UI/UI_8.png");
		button->value = Editor::GetValue("Scene/Game/F_EXIT");
		button->onClick = [=]()
		{
			dt = 0.016;
			game_stage = 1;
			SceneManager::LoadScene("MainMenu");
		};
		failLayer->Attach(button);
	}

	void PlayerInit(){
		player = new Player();
		player->health = 5;
		player->value = Editor::GetValue("Unit/player");
		this->Attach(player);
	}

	void BackgroundUpdate(){
		if (!backgroundLayer->enable)
			return;
		for (auto it : backgrounds){
			if (it->tag.compare("bg1") == 0){
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
		Sprite* background = new Sprite("UI/UI_1.png");
		background->value.position = { 640, 360 };
		this->Attach(background);

		playerHealthBar = new Node();
		this->Attach(playerHealthBar);
		playerHealthBar->value = Editor::GetValue("Scene/Game/playerHealthBar");
		for (int i = 0; i < 5; i++){
			hearts[i] = new Sprite("UI/UI_3.png");
			hearts[i]->value.position.y -= 30 * i;
			playerHealthBar->Attach(hearts[i]);
		}

		bossHealthBackground = new Sprite("UI/UI_13.png");
		bossHealthBackground->value.position = { 640, 360 };
		bossHealthBackground->visible = false;
		this->Attach(bossHealthBackground);
	}

	void HudUpdate(){
		for (int i = 0; i < 5; i++)
			hearts[i]->visible = false;

		for (int i = 0; i < player->health; i++)
			hearts[i]->visible = true;

		if (bossHealthBar != nullptr)
			bossHealthBar->SetValue(hardMonster->health);
	}

	void OnUpdate() override {
		if (input->KeyDown(VK_ESCAPE)){
			if (!pause){
				pause = true;
				dt = 0.0f;
				pauseLayer->visible = true;
				pauseLayer->enable = true;
			}
		}

		if (input->KeyDown(VK_SPACE)){
			ShowBossMonster();
		}

		if (input->KeyDown(VK_BACK)){
			player->Damage(5);
		}

		if (input->KeyDown('N')){
			hardMonster->Damage(50);
		}

		if (player->health <= 0){
			failLayer->visible = true;
			failLayer->enable = true;
			dt = 0.0f;
		}

		if (hardMonster->health <= 0){
			clearLayer->visible = true;
			clearLayer->enable = true;
			dt = 0.0f;
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

	void ShowBossMonster(){
		if (!boss1_clear)
			hardMonster->Init(1);
		else
			hardMonster->Init(2);

		if (bossHealthBar != nullptr)
			bossHealthBar->Destroy();

		hardMonster->Show();

		backgroundLayer->enable = false;
		bossHealthBackground->visible = true;
		bossHealthBar = new FillSprite("hp.png", 550, hardMonster->health);
		bossHealthBar->value = Editor::GetValue("Scene/Game/bossHealthBar");
		bossHealthBackground->Attach(bossHealthBar);
	}
};