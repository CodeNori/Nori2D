#include "pch.h"
#include "DemoGame1.h"
#include "renderer\Dx2DRenderer.h"
#include "Actor.h"
#include "Components.h"





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

extern IRenderer* g_ECS_Renderer;

void DemoGame1::Draw(IRenderer* rd)
{
	g_ECS_Renderer = rd;
	Render_system_all(g_Time.deltaTime);
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


