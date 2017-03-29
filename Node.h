#pragma once
#include "pch.h"

class NodeRect
{
public:
	Vector2 lefttop = {};
	Vector2 leftbottom = {};
	Vector2 righttop = {};
	Vector2 rightbottom = {};
};

class NodeValue
{
public:
	Vector2 position = { 0, 0 };
	Vector2 scale = { 1, 1 };
	Vector2 anchor = { 0.5, 0.5 };
	float angle = 0;
	NodeRect rect = NodeRect();
	Vector2 rectScale = { 1, 1 };
};

class Node
{
public:
	static vector<Node*> roots;
	static std::queue<function<void()>> delayComment;
	vector<Node*> children;
	Node* parent;
	NodeValue value;
	bool visible = false;
	bool enable = false;
	int zOrder = -1;
	string tag = "";

	Node(bool visible = true, bool enable = true) : visible(visible), enable(enable) {
		value = NodeValue();
		parent = nullptr;
		delayComment.push([=](){
			roots.push_back(this);
		});
	}

	~Node(){
		for (auto it : children)
			delete it;
	}

	virtual void OnUpdate(){}
	virtual void OnDraw(){};

	void Update(){
		if (enable){
			OnUpdate();
			for (auto it : children)
				it->Update();
		}
	}

	void Draw(){
		if (visible){
			OnDraw();
			for (auto it : children)
				it->Draw();
		}
	}

	static void RootUpdate(){
		for (auto it : roots){
			it->Update();
		}

		while (delayComment.empty() == false){
			delayComment.front()();
			delayComment.pop();
		}
	}

	static void RootDraw(){
		for (auto it : roots)
			it->Draw();
	}

	void Attach(Node* node){
		delayComment.push([this, node](){
			children.push_back(node);
			auto iter = remove(roots.begin(), roots.end(), node);
			if (iter != roots.end())
				roots.erase(iter);
		});
		node->parent = this;
	}

	void DeAttach(Node* node){
		node->parent = nullptr;
		delayComment.push([this, node](){
			roots.push_back(node);
			auto iter = remove(children.begin(), children.end(), node);
			if (iter != children.end())
				children.erase(iter);
		});
	}

	void Destroy(){
		visible = false;
		enable = false;
		if (parent != nullptr){
			parent->DeAttach(this);
			Destroy();
		}
		else
		{
			delayComment.push([=](){
				auto iter = remove(roots.begin(), roots.end(), this);
				if (iter != roots.end()){
					roots.erase(iter);
					delete this;
				}
			});
		}
	}

	D3DXMATRIX GetMatrix(){
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixTransformation2D(&mat, nullptr, 0, &value.scale, nullptr, value.angle, &value.position);
		if (parent != nullptr)
			mat *= parent->GetMatrix();
		return mat;
	}
};