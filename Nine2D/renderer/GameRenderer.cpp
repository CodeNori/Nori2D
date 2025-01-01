#include "pch.h"
#include "GameRenderer.h"


namespace {
	static GameRenderer* g = nullptr;
}


GameRenderer* GameRenderer::get()
{
	if(!g) g = new GameRenderer;
	return g;
}


GameRenderer::~GameRenderer()
{
	SAFE_DELETE(g);
}

void GameRenderer::Draw(Vec2 pos, const WCHAR* imgName, int fameNo)
{

}
