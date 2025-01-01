#pragma once


class GameRenderer
{
public:
	static GameRenderer* get();

	~GameRenderer();

	void Draw(Vec2 pos, const WCHAR* imgName, int fameNo);
};







