#pragma once
#include "imgui\imgui.h"

	class DxImGui
	{
		struct SCREEN_TEXT {
			ImFont* font;
			int     fontSize;
			ImVec2  position;
			ImColor color;
			std::string str;
		};
		std::vector<SCREEN_TEXT> mTexts;

		void RenderTextAll();

	public:
		DxImGui(HWND hWnd, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);
		~DxImGui();
		LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		void Start();
		void End();
		void RenderToDX();
		void TextOutU8(ImFont* font, int font_size,
			int x, int y,
			std::string txt,
			UINT32 rgb = 0xFFFFFFFF
		);

	public:
		static DxImGui* g;

		ImFont* m_korFont;

	};



class IimGuiRenderer
{
public:
	virtual  void RenderGUI() = 0;
};

 // std::function<void(void* lparam)> mImGuiRenderFunc = nullptr;

// new callbacks based on C++11
#define AX_CALLBACK_0(__selector__, __target__, ...) std::bind(&__selector__, __target__, ##__VA_ARGS__)
#define AX_CALLBACK_1(__selector__, __target__, ...) \
    std::bind(&__selector__, __target__, std::placeholders::_1, ##__VA_ARGS__)
#define AX_CALLBACK_2(__selector__, __target__, ...) \
    std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define AX_CALLBACK_3(__selector__, __target__, ...)                                                          \
    std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, \
              ##__VA_ARGS__)

