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
#include "Item.h"

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
	bool isBoss = false;
	bool boss1_clear = false;
	bool isBossClear = false;
	float prevBossClearTime = 0.0f;

	TextString* gameScoreText;
	TextString* gameStageText;

	Sprite* game_stage_show;
	Sprite* game_stage_background;

	bool isWarning;
	int warningCount;
	bool warningColor;
	Sprite* warning;

	vector<Sprite*> bubbles;
	float prevBubbleDelay = 0.0f;
	float nextBubbleDelay = 0.0f;

	vector<Item*> items;
	float prevItemDelay = 0.0f;
	float nextItemDelay = 0.0f;

	Node* bulletCountLayer;
	Text* bulletCount[3];

	Sprite* comboLayer;
	Text* comboCount[4];
	Vector2 comboScale;
	Vector2 comboLayerScale;
	bool comboEnable = false;
	float prevComboEnalbe = 0.0f;

	Sprite* nuclearEffect;
	bool isNuclearEffect;

	float prevBossShowDelay = 0.0f;
	float nextBossShowDely = 0.0f;
public:
	static Game* instance;
	Game(){
		instance = this;

		editor = new Editor();
		this->Attach(editor);
		input = new Input();
		this->Attach(input);
		backgroundLayer = new Node();
		this->Attach(backgroundLayer);

		bossHealthBar = nullptr;
		hardMonster = nullptr;

		isBossClear = false;
		prevBossClearTime = 0.0f;

		if (game_stage == 1)
			backgrounds = Editor::GetBackgrounds("Scene/Game/Game1");
		else if (game_stage == 2)
			backgrounds = Editor::GetBackgrounds("Scene/Game/Game2");

		for (auto it : backgrounds){
			backgroundLayer->Attach(it);
		}

		for (int i = 0; i < 15; i++){
			Sprite* bubble = new Sprite("Scenes/Bub_0.png");
			bubble->visible = false;
			bubble->enable = false;
			this->Attach(bubble);
			bubbles.push_back(bubble);
		}

		for (int i = 0; i < 10; i++){
			Item* item = new Item();
			item->visible = false;
			item->enable = false;
			this->Attach(item);
			items.push_back(item);
		}

		nextBubbleDelay = rand() % 4 + 1;

		boss1_clear = false;
		prevMonsterCreate = 0.0f;
		nextMonsterCreate = 3;

		PlayerInit();

		for (int i = 0; i < 10; i++){
			auto normal = new NormalMonster();
			normal->value = Editor::GetValue("Unit/Normal");
			normal->Init();
			normal->visible = false;
			normal->enable = false;
			this->Attach(normal);
			monsters.push_back(normal);
		}

		hardMonster = new HardMonster();
		hardMonster->value = Editor::GetValue("Unit/Hard");
		hardMonster->Hide();
		this->Attach(hardMonster);

		HudInit();
		LayerInit();

		nuclearEffect = new Sprite();
		nuclearEffect->value.position = { 640, 360 };
		this->Attach(nuclearEffect);
		isNuclearEffect = false;

		nextBossShowDely = 40;
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
			player_combo = 0;
			if (game_stage == 1){
				game_stage = 2;
				player->Save();
				SceneManager::LoadScene("Game");
			}
			else{
				SceneManager::LoadScene("Credit");
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

		pauseLayer->zOrder = 6;
		clearLayer->zOrder = 6;
		failLayer->zOrder = 6;
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
		background->zOrder = 4;
		this->Attach(background);

		playerHealthBar = new Node();
		playerHealthBar->value = Editor::GetValue("Scene/Game/playerHealthBar");
		playerHealthBar->zOrder = 5;
		this->Attach(playerHealthBar);
		for (int i = 0; i < 5; i++){
			hearts[i] = new Sprite("UI/UI_3.png");
			hearts[i]->value.position.y -= 30 * i;
			playerHealthBar->Attach(hearts[i]);
		}

		bossHealthBackground = new Sprite("UI/UI_13.png");
		bossHealthBackground->value.position = { 640, 360 };
		bossHealthBackground->visible = false;
		bossHealthBackground->zOrder = 4;
		this->Attach(bossHealthBackground);

		gameScoreText = new TextString();
		gameScoreText->value = Editor::GetValue("Scene/Game/gameScore");
		gameScoreText->SetString(to_string(game_score));
		gameScoreText->zOrder = 4;
		// editor->AddEditor(gameScoreText, "Scene/Game/gameScore");
		this->Attach(gameScoreText);

		gameStageText = new TextString();
		gameStageText->SetString("STAGE");
		gameStageText->value = Editor::GetValue("Scene/Game/gameStage");
		gameStageText->zOrder = 4;
		editor->AddEditor(gameStageText, "Scene/Game/gameStage");
		this->Attach(gameStageText);

		bulletCountLayer = new Node();
		bulletCountLayer->value = Editor::GetValue("Scene/Game/bulletLayer");
		editor->AddEditor(bulletCountLayer, "Scene/Game/bulletLayer");
		bulletCountLayer->zOrder = 4;
		this->Attach(bulletCountLayer);

		// 총알 개수 표시하기;
		for (int i = 0; i < 3; i++){
			bulletCount[i] = new Text();
			bulletCount[i]->SetString("1");
			bulletCount[i]->value.position.x += 220 * i;
			bulletCountLayer->Attach(bulletCount[i]);
		}

		comboLayer = new Sprite("Combo/Combo.png");
		comboLayer->value.position = { 640, 260 };
		comboLayer->value.scale = { 0.8, 0.8 };
		this->Attach(comboLayer);

		for (int i = 0; i < 4; i++){
			comboCount[i] = new Text();
			comboCount[i]->SetString("0");
			comboCount[i]->value.scale = { 0.8, 0.8 };
			comboCount[i]->value.position.x -= 120;
			comboCount[i]->value.position.x += 80 * i;
			comboCount[i]->value.position.y = 100;
			comboLayer->Attach(comboCount[i]);
		}

		Sprite* character;
		if (player_sex == 0)
			character = new Sprite("UI/Boy.png");
		else
			character = new Sprite("UI/Girl.png");
		character->value = Editor::GetValue("Scene/Game/character");
		editor->AddEditor(character, "Scene/Game/character");
		character->zOrder = 4;
		this->Attach(character);


		if (game_stage == 1)
			game_stage_show = new Sprite("UI/UI_14.png");
		else
			game_stage_show = new Sprite("UI/UI_15.png");
		game_stage_show->value.position = { 640, 360 };
		this->Attach(game_stage_show);

		game_stage_background = new Sprite("UI/UI_0.png");
		game_stage_background->value.position = { 640, 360 };
		game_stage_background->zOrder = 4;
		this->Attach(game_stage_background);

		warning = new Sprite("UI/UI_18.png");
		warning->value.position = { 640, 360 };
		warning->zOrder = 5;
		warning->visible = false;
		this->Attach(warning);

		isWarning = false;
		warningCount = 0;
		warningColor = false;
	}

	void HudUpdate(){
		for (int i = 0; i < 5; i++)
			hearts[i]->visible = false;

		for (int i = 0; i < player->health; i++)
			hearts[i]->visible = true;

		if (game_stage_show != nullptr){
			D3DXColorLerp(&game_stage_show->color, &game_stage_show->color, &Color(0, 0, 0, 0), 0.02f);
			if (game_stage_show->color.a < 0.1)
				game_stage_show->visible = false;
		}

		if (game_stage_background != nullptr){
			D3DXColorLerp(&game_stage_background->color, &game_stage_background->color, &Color(0, 0, 0, 0), 0.02f);
			if (game_stage_background->color.a < 0.1)
				game_stage_background->visible = false;
		}


		if (bossHealthBar != nullptr && hardMonster != nullptr)
			bossHealthBar->SetValue(hardMonster->health);

		if (gameScoreText != nullptr)
			gameScoreText->SetString(to_string(game_score));

		if (gameStageText != nullptr){
			if (game_stage == 1){
				if (!boss1_clear){
					gameStageText->SetString("STAGE11");
				}
				else
				{
					gameStageText->SetString("STAGE12");
				}
			}
			else if (game_stage == 2){
				if (!boss1_clear){
					gameStageText->SetString("STAGE21");
				}
				else
				{
					gameStageText->SetString("STAGE22");
				}
			}
		}

		bulletCount[0]->SetString(to_string(player->followBulletCnt));
		bulletCount[1]->SetString(to_string(player->thirdBulletCnt));
		bulletCount[2]->SetString(to_string(player->hackBulletCnt));

		if (player_combo > 20){
			int one = (((player_combo % 1000) % 100) % 10);
			int ten = ((player_combo % 1000) % 100) / 10;
			int hundred = (player_combo % 1000) / 100;
			int thousand = player_combo / 1000;

			if (thousand < 10)
				comboCount[0]->SetString(to_string(thousand));
			if (hundred < 10)
				comboCount[1]->SetString(to_string(hundred));
			if (ten < 10)
				comboCount[2]->SetString(to_string(ten));
			if (one < 10)
				comboCount[3]->SetString(to_string(one));
			comboScale *= 0.9f;
			comboLayerScale *= 0.9f;

			if (comboScale.x < 0.8f || comboScale.y < 0.8f)
				comboScale = { 0.8f, 0.8f };

			if (comboLayerScale.x < 1.0f || comboLayerScale.y < 1.0f)
				comboLayerScale = { 1.0f, 1.0f };

			for (int i = 0; i < 4; i++){
				comboCount[i]->value.scale = comboScale;
			}
			comboLayer->value.scale = comboLayerScale;
		}
		if (comboEnable){
			D3DXColorLerp(&comboLayer->color, &comboLayer->color, &Color(1, 1, 1, 1), 0.1f);
			for (int i = 0; i < 4; i++){
				D3DXColorLerp(&comboCount[i]->text_sprite->color, &comboCount[i]->text_sprite->color, &Color(1, 1, 1, 1), 0.1f);
			}
			prevComboEnalbe += dt;
			if (prevComboEnalbe >= 1.0f){
				prevComboEnalbe = 0.0f;
				comboEnable = false;
			}
		}
		if (!comboEnable){
			D3DXColorLerp(&comboLayer->color, &comboLayer->color, &Color(1, 1, 1, 0), 0.1f);
			for (int i = 0; i < 4; i++){
				D3DXColorLerp(&comboCount[i]->text_sprite->color, &comboCount[i]->text_sprite->color, &Color(1, 1, 1, 0), 0.1f);
			}
		}
		// ===========================

		if (isWarning){
			if (!warningColor){
				D3DXColorLerp(&warning->color, &warning->color, &Color(1, 1, 1, 0), 0.1f);
				if (warning->color.a < 0.1f){
					warningColor = true;
					warningCount += 1;
				}
			}
			else{
				D3DXColorLerp(&warning->color, &warning->color, &Color(1, 1, 1, 1), 0.1f);
				if (warning->color.a > 0.9f){
					warningColor = false;
					warningCount += 1;
				}
			}
			if (warningCount > 4){
				isWarning = false;
				warning->visible = false;
				warning->color.a = 1.0f;
				warningCount = 0;
				ShowBossMonster();
			}
		}
		// ============================
		if (isNuclearEffect){
			D3DXColorLerp(&nuclearEffect->color, &nuclearEffect->color, &Color(1, 1, 1, 0), 0.05f);
			if (nuclearEffect->color.a < 0.1f){
				isNuclearEffect = false;
				nuclearEffect->visible = false;
			}
		}
	}

	void OnUpdate() override {
		Cheat::Update();

		HudUpdate();
		BackgroundUpdate();

		if (player->health <= 0){
			failLayer->visible = true;
			failLayer->enable = true;
			dt = 0.0f;
		}

		if (!isBoss){
			prevBossShowDelay += dt;
			if (prevBossShowDelay >= nextBossShowDely){
				prevBossShowDelay = 0.0f;
				ShowWarning();
			}
		}

		if (hardMonster != nullptr)
		{
			if (hardMonster->health <= 0)
			{
				if (isBoss)
				{
					isBoss = false;
					isBossClear = true;
					prevBossClearTime = 0.0f;
				}
			}
		}

		if (isBossClear)
		{
			hardMonster->Hide();
			prevBossClearTime += dt;
			if (prevBossClearTime >= 2.0f){
				prevBossClearTime = 0.0f;

				isBoss = false;
				isBossClear = false;

				if (!boss1_clear)
				{
					boss1_clear = true;
					bossHealthBackground->visible = false;
					backgroundLayer->enable = true;
				}
				else
				{
					clearLayer->visible = true;
					clearLayer->enable = true;
					dt = 0.0f;
				}
			}
		}


		prevMonsterCreate += dt;
		if (prevMonsterCreate >= nextMonsterCreate){
			prevMonsterCreate = 0.0f;
			nextMonsterCreate = rand() % 3 + 1;
			auto monster = getMonster();
			if (monster != nullptr){
				static_cast<NormalMonster*>(monster)->Init();
				monster->value.position = { (float)(rand() % 900 + 300), (float)-3 };
			}
		}

		// ============================
		prevBubbleDelay += dt;
		if (prevBubbleDelay >= nextBubbleDelay){
			prevBubbleDelay = 0.0f;
			nextBubbleDelay = rand() % 2 + 1;
			BubbleCreate();
		}
		BubbleUpdate();
		// ============================
		ItemUpdate();
		// ============================
		if (input->KeyDown(VK_ESCAPE)){
			if (!pause){
				pause = true;
				dt = 0.0f;
				pauseLayer->visible = true;
				pauseLayer->enable = true;
			}
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

	void ShowWarning(){
		isWarning = true;
		warning->visible = true;
		warning->color.a = 1.0f;
		warningCount = 0;
	}

	void ShowBossMonster(){
		if (!boss1_clear)
			hardMonster->Init(1);
		else
			hardMonster->Init(2);

		isBoss = true;
		hardMonster->Show();
		hardMonster->visible = true;
		hardMonster->enable = true;
		backgroundLayer->enable = false;
		bossHealthBackground->visible = true;
		bossHealthBar = new FillSprite("hp.png", 550, hardMonster->health);
		bossHealthBar->value = Editor::GetValue("Scene/Game/bossHealthBar");
		bossHealthBackground->Attach(bossHealthBar);
	}

	void BubbleCreate(){
		Sprite* bubble;
		for (auto it : bubbles){
			if (!it->visible || !it->enable){
				it->visible = true;
				it->enable = true;
				bubble = it;
				break;
			}
		}

		bubble->value.position = { (float)(rand() % 1000 + 200), 800 };
		bubble->color = Color(1, 1, 1, 0.5f);
		float scale = rand() % 3 + 1;
		bubble->value.scale = { scale, scale };
	}

	void BubbleUpdate(){
		for (auto it : bubbles){
			if (it->visible){
				if (it->value.scale.x >= 3){
					it->value.position.y -= 150 * dt;
				}
				else if (it->value.scale.x >= 2){
					it->value.position.y -= 200 * dt;
				}
				else
				{
					it->value.position.y -= 250 * dt;
				}

				if (it->value.position.y < -30){
					it->visible = false;
					it->enable = false;
				}
			}
		}
	}

	void ItemCreate(){
		Item* item = nullptr;
		for (auto it : items){
			if (!it->visible || !it->enable){
				it->visible = true;
				it->enable = true;
				it->zOrder = 2;
				item = it;
				break;
			}
		}
		if (item != nullptr){
			int rd = rand() % 2;
			// 장애물
			if (rd == 0){
				item->Init(ItemType::HUDDLE);
				item->value.scale = { 0.5, 0.5 };
				item->value.rectScale = { 0.3, 0.3 };
				item->value.position = { (float)(rand() % 1000 + 200), -20 };
			}
			else
			{
				item->Init(ItemType::ITEM);
				item->value.scale = { 0.3, 0.3 };
				item->value.rectScale = { 0.3, 0.3 };
				item->value.position = { (float)(rand() % 1000 + 200), 20 };
			}
		}
	}

	void ItemUpdate(){
		prevItemDelay += dt;
		if (prevItemDelay >= nextItemDelay){
			prevItemDelay = 0.0f;
			nextItemDelay = rand() % 5 + 3;
			ItemCreate();
		}
	}

	void ComboEnable(){
		if (player_combo > 50){
			comboLayerScale = { 1.3f, 1.3f };
			comboScale = { 1.2f, 1.2f };
			comboEnable = true;
			prevComboEnalbe = 0.0f;
		}
	}

	void Nuclear(){
		nuclearEffect->AddAnimation(new Animation("Nuclear", 0.1f, false, true, [=]()
		{
			isNuclearEffect = true;

			for (auto it : UnitBase::units){
				if (it->visible){
					if (it->tag.compare("Player") != 0){
						it->Damage(50);
					}
				}
			}
		}));
		nuclearEffect->visible = true;
		nuclearEffect->color.a = 1.0f;
		nuclearEffect->animation->Play();
	}
};