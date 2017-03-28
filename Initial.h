#pragma once
#include "pch.h"
#include "Node.h"
#include "Input.h"

class Initial : public Node
{
private:
	int strIdx = 0;
	char str[3];
	string args = "ABCDEFGHIZKLMNOPQRSTUVWXYZ";
public:
	Initial(){
		strIdx = 0;

		RankingData::Load();

		for (int i = 0; i < 3; i++)
			str[i] = ' ';
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
			str[strIdx - 1] = ' ';
			strIdx -= 1;
			if (strIdx < 0)
				strIdx = 0;
		}

		if (input->KeyDown(VK_RETURN)){
			RankingData::Add(RankingData(str, 1000));
			RankingData::Save();
			RankingData::Load();
		}

		// for (int i = 0; i < 3; i++){
		// 	cout << str[i];
		// }
		// cout << endl;

	}
};