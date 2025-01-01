#pragma once
#include "IGame.h"
#include "Actor1.h"

class DemoGame : public IGame
{
	std::vector<Actor1*>  mActorList;
	int count = 0;
	IRenderer* mRD = nullptr;

public:
	DemoGame();
	~DemoGame();
	void sample1();
	void sample();
	void getMouse(int x, int y) override;
	void spawnUltra(int x, int y);
	void Update(float delta) override;
	void Draw(void* param) override;


};

