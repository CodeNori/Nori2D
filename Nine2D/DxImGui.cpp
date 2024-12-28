#include "pch.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_win32.h"
#include "imgui\imgui_impl_dx11.h"
#include "DxImGui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);





DxImGui* DxImGui::g = nullptr;

DxImGui::DxImGui(HWND hWnd, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	g = this;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\malgun.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesKorean());

	m_korFont = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\malgun.ttf", 36.0f, nullptr, io.Fonts->GetGlyphRangesKorean());
    
	// Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(pd3dDevice, pd3dDeviceContext);

}

DxImGui::~DxImGui()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();

}

LRESULT DxImGui::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ImGui_ImplWin32_WndProcHandler( hWnd, msg, wParam, lParam);
}



void DxImGui::Start()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void DxImGui::End()
{
	RenderTextAll();

	ImGui::Render();
}

void DxImGui::RenderToDX()
{
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void DxImGui::TextOutU8(ImFont* font, int font_size, int x, int y, std::string txt, UINT32 rgb)
{
	SCREEN_TEXT a;
	a.font = font;
	a.fontSize = font_size;
	a.position.x = x;
	a.position.y = y;
	a.color = rgb;
	a.str = txt;

	mTexts.push_back(a);
}

void DxImGui::RenderTextAll()
{
	if (mTexts.size() == 0) return;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowBgAlpha(0.0f);

	ImGui::Begin
	(
		"TextWindow", NULL,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus
	);

	for (SCREEN_TEXT text : mTexts)
	{
		ImGui::GetWindowDrawList()->AddText(text.font, text.fontSize, 
			text.position, text.color, text.str.c_str());
	}
	ImGui::End();

	mTexts.clear();
}


