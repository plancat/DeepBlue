#pragma once
#include "pch.h"
#include "Node.h"
#include "Input.h"
#include "Editor.h"

class Initial : public Node
{
private:
	int strIdx = 0;
	string str[3];
	Text* str_text[3];
	string args = "ABCDEFGHIZKLMNOPQRSTUVWXYZ";
	Node* texts;
	Editor* editor;
public:
	Initial(){
		strIdx = 0;
		input = new Input();
		this->Attach(input);
		editor = new Editor();
		this->Attach(editor);

		Sprite* background = new Sprite("UI/UI_16.png");
		background->value.position = { 640, 360 };
		this->Attach(background);

		RankingData::Load();
		texts = new Node();
		texts->value = Editor::GetValue("Scene/Initial/texts");
		this->Attach(texts);
		editor->AddEditor(texts, "Scene/Initial/texts");

		for (int i = 0; i < 3; i++){
			str[i] = "";
			str_text[i] = new Text();
			str_text[i]->value.position.x = 230 * i;
			texts->Attach(str_text[i]);
		}

		Button* missionComplate = new Button("UI/UI_17.png");
		missionComplate->value = Editor::GetValue("Scene/Initial/mission");
		missionComplate->onClick = [=]()
		{
			RankingData::Add(RankingData(str, game_score));
			RankingData::Save();
			RankingData::Load();
			SceneManager::LoadScene("Credit");
		};
		this->Attach(missionComplate);
	}

	void OnUpdate() override {
		for (int i = 0; i < args.size(); i++){
			if (input->KeyDown(args[i])){
				if (strIdx > 2)
					return;
				str[strIdx] = args[i];
				strIdx += 1;
			}
		}

		if (input->KeyDown(VK_BACK)){
			str[strIdx - 1] = "";
			strIdx -= 1;
			if (strIdx < 0)
				strIdx = 0;
		}

		if (input->KeyDown(VK_RETURN)){
			RankingData::Add(RankingData(str, game_score));
			RankingData::Save();
			RankingData::Load();
			SceneManager::LoadScene("Credit");
		}

		for (int i = 0; i < 3; i++){
			if (str[i].compare("") == 0)
				str_text[i]->visible = false;
			else
				str_text[i]->visible = true;

			str_text[i]->SetString(str[i]);
		}
	}
};