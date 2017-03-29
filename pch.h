#pragma once
#include "DXUT.h"
#include "resource.h"
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <Windows.h>
#include <functional>
#include <vector>
#include <queue>
#include <map>
#include <fstream>
#include <time.h>

using namespace std;

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXCOLOR Color;

extern float dt;
extern int game_score;
extern int game_stage;

// 백업 용도
extern int player_thirdBullet;
extern int player_finalBullet;
extern int player_followBullet;

class Input;
extern Input* input;

class RankingData
{
public:
	string name;
	int score;
	RankingData(){

	}
	RankingData(const string str[3], int score){
		this->score = score;
	}
private:
	static vector<RankingData> rankingDatas;
public:
	static vector<RankingData> Load(){
		vector<RankingData> tempRanking;
		auto is = ifstream("Resources/Ranking.txt");
		for (int i = 0; i < 4; i++){
			auto rankingData = RankingData();
			is >> rankingData.name >> rankingData.score;
			rankingDatas.push_back(rankingData);
			cout << "Ranking : " << rankingData.name << " " << rankingData.score << endl;
			tempRanking.push_back(rankingData);
		}
		is.close();

		return tempRanking;
	}
	static void Add(RankingData data){
		rankingDatas.push_back(data);
		sort(rankingDatas.begin(), rankingDatas.end(), [=](RankingData a, RankingData b){return a.score > b.score; });
	}
	static void Save(){
		auto of = ofstream("Resources/Ranking.txt");
		for (int i = 0; i < 4; i++){
			auto rankingData = rankingDatas[i];
			of << rankingData.name.c_str() << " " << rankingData.score << endl;
			cout << "Ranking : " << rankingData.name << " " << rankingData.score << endl;
		}
		of.close();
	}
};