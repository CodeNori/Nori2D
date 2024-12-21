#pragma once
#include "Components.h"
#include <functional>
#include "IGame.h"

class IRenderer;

class DxWindow
{
public:
	DxWindow();
	~DxWindow();

	IGame* mGameObj = nullptr;
	IRenderer* mRenderer = nullptr;

	static DxWindow* g;

	static LRESULT CALLBACK WindowProc(
		HWND hWnd,		
		UINT uMsg,		
		WPARAM wParam,	
		LPARAM lParam	
		);

	HRESULT InitWindow();
	HRESULT InitDirectX();	
	HRESULT Run(IGame* game, IRenderer* rd);
	void Update();
	void Draw();
	void MessageLoop();

	LRESULT onMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Convenience methods for handling mouse input, since we
	// can easily grab mouse input from OS-level messages
	void OnMouseDown(WPARAM buttonState, int x, int y);
	void OnMouseUp(WPARAM buttonState, int x, int y);
	void OnMouseMove(WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta, int x, int y);

	void UpdateTimer();

	void UpdateTitleBarStats();

public:
	const float colorBackG[4] = { 0.392156899f, 0.584313750f, 0.929411829f, 1.f };
	bool isSpaceKey = false;
	float isSpaceKey_coolTime = 0.f;
};

