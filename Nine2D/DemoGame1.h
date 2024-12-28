#pragma once
#include "IGame.h"
#include "Actor1.h"

class DemoGame1
{
	std::vector<Actor1*>  mActorList;
	int count = 0;

public:
	DemoGame1();
	~DemoGame1();
	void sample();
	void getMouse(int x, int y);
	void Update(float delta);
	void Draw(void* param);
	void DrawGui(void* param);

public:
	class Dx2DRenderer* mRD = nullptr;
};

