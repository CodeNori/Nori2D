#include "pch.h"
#include "DemoGame1.h"
#include "renderer\Dx2DRenderer.h"
#include "Actor.h"
#include "Components.h"

#include "DxImGui.h"




DemoGame1::DemoGame1() 
{
	g_CameraPos.x = g_Dx11.half_width;
	g_CameraPos.y = g_Dx11.half_height;
	register_components();
	register_systems();
}

DemoGame1::~DemoGame1() 
{



}

extern Dx2DRenderer* g_ECS_Renderer;

void DemoGame1::Draw(void* param)
{
	g_ECS_Renderer = mRD;
	Render_system_all(g_Time.deltaTime);
}

void DemoGame1::DrawGui(void* param)
{
    if (!ImGui::Begin("Game1"))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

    if (ImGui::CollapsingHeader("Actor"))
    {
        ImGui::SeparatorText("ABOUT THIS DEMO:");
        ImGui::BulletText("Sections below are demonstrating many aspects of the library.");
        ImGui::BulletText("The \"Examples\" menu above leads to more demo contents.");
        ImGui::BulletText("The \"Tools\" menu above gives access to: About Box, Style Editor,\n"
                          "and Metrics/Debugger (general purpose Dear ImGui debugging tool).");

        ImGui::SeparatorText("PROGRAMMER GUIDE:");
        ImGui::BulletText("See the ShowDemoWindow()");
        ImGui::BulletText("See comments in imgui.cpp.");
        ImGui::BulletText("See example applications in the examples/ folder.");
        ImGui::BulletText("Read the FAQ at https://www.dearimgui.com/faq/");
        ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
        ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");
    }

	ImGui::End();

	DxImGui::g->TextOutU8(DxImGui::g->m_korFont, 36, 10, 10, u8"±è´ë¿í");
}

void DemoGame1::Update(float delta)
{
	Update_system_all(delta);
}


void DemoGame1::sample()
{
	for(int i=0; i<1000; ++i)
		create_entity_Unit();

	create_entity_House();
	create_entity_House();
	create_entity_House();
	create_entity_House();
	create_entity_House();
	create_entity_House();

}

void DemoGame1::getMouse(int x, int y)
{
}


