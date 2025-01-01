#pragma once
#include "base/Vec2.h"


struct TimeData
{
	// Timing related data
	double perfCounterSeconds;
	float totalTime;
	float deltaTime;
	__int64 startTime; 
	__int64 currentTime;
	__int64 previousTime;

	// FPS calculation
	int fpsFrameCount;
	float fpsTimeElapsed;
};


struct Dx11Vars
{
	int width;
	int height;

	float half_width;
	float half_height;

	HINSTANCE	hInstance;	
	std::string titleBarText;
	bool		titleBarStats;
	HWND		hWnd;

	//D3D_FEATURE_LEVEL		dxFeatureLevel;
	IDXGISwapChain* swapChain = 0;
	ID3D11Device* device = 0;
	ID3D11DeviceContext* context = 0;

	ID3D11RenderTargetView* backBufferRTV = 0;
	ID3D11DepthStencilView* depthStencilView = 0;

	D3D_FEATURE_LEVEL		dxFeatureLevel;
};


//-----------------------------------------------

struct Pos_t
{
    float x, y;
	float angle;
};

struct Velocity_t
{
    Vec2 dir;
	float speed;
};

struct Img_t
{
	short dir;
	short frameNo;
	float AnimTime;

	const WCHAR* texName; 
    void* tex;
};

struct Anchor_t
{
	float w, h;
	float anchorX, anchorY;
};

struct Vertex_t
{
    float x1, y1, x2, y2;
};

struct CollisionRect
{
    float left, top, right, bottom;
	ecs_id_t id;
};

struct CollisionEvent
{
	ecs_id_t l, r;
};

struct CollisionEvent1
{
	ecs_id_t l, r;
};

struct UnitState_t
{
	BYTE  isDead : 1;
	BYTE  isCollision : 1;
	BYTE  rest : 6;
};

struct Team_t
{
	BYTE  teamNo;
};

//-----------------------------------------------

extern Dx11Vars g_Dx11;
extern TimeData g_Time;
extern ecs_t* ecs1;

// component IDs
extern ecs_id_t PositionCompID;
extern ecs_id_t VelocityCompID;
extern ecs_id_t TextureCompID;
extern ecs_id_t HouseCompID;
extern ecs_id_t UnitCompID;
extern ecs_id_t RectCompID;
extern ecs_id_t AnchorCompID;
extern ecs_id_t CollisionEvent1CompID;

// System IDs
extern ecs_id_t MovementSysID;
extern ecs_id_t RenderHouse_SysID;
extern ecs_id_t RenderUnit_SysID;

//-----------------------------------------------



#include "Camera.h"
#include "Components_func.h"
#include "Components_tower.h"



void register_components();
void register_systems();
void Update_system_all(float dt);
void Render_system_all(float dt);

ecs_id_t create_entity_Unit();
ecs_id_t create_entity_House();






