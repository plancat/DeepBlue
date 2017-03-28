#pragma once
#include "pch.h"
#include "Node.h"

class Editor : public Node
{
private:
	vector<pair<Node*, string>> editors;
public:
	static NodeValue GetValue(const string& path){
		auto file = ifstream("Resources/Editor/" + path + ".txt");
		if (!file.is_open()){
			auto tempFile = ofstream("Resources/Editor/" + path + ".txt");
			tempFile << 0 << " " << 0 << endl;
			tempFile << 1 << " " << 1 << endl;
			tempFile << 0.5 << " " << 0.5 << endl;
			tempFile << 0 << endl;
			tempFile << 1 << " " << 1 << endl;
			tempFile.close();
		}

		auto nodeValue = NodeValue();
		file >> nodeValue.position.x >> nodeValue.position.y;
		file >> nodeValue.scale.x >> nodeValue.scale.y;
		file >> nodeValue.anchor.x >> nodeValue.anchor.y;
		file >> nodeValue.angle;
		file >> nodeValue.rectScale.x >> nodeValue.rectScale.y;
		file.close();
		return nodeValue;
	}

	void AddEditor(Node* node, const string& path){
		editors.push_back({ node, path });
	}

	void OnUpdate() override {
		for (auto it : editors){
			it.first->value = GetValue(it.second);
		}
	}
};