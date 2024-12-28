#pragma once
#include "DxShader.h"
#include "IGame.h"
#include "ConstantBuffer.h"
#include "Dx2DRenderable.h"
#include "DxTexture.h"
#include "Quad.h"

struct VS_CONSTANT_BUFFER
{
	float color_R;
	float color_G;
	float color_B;

	float pos_X;
	float pos_Y;
};


struct VERTEX
{
      FLOAT X, Y, Z;
	  FLOAT U, V;
};


struct CBChangesEveryFrame
{
	XFloat4 vMeshColor;
};




class Dx2DRenderer : public IRenderer
{
	HRESULT create();
	ID3D11Buffer* creaVB();

	HRESULT createBS();
	HRESULT createSampler();
public:
	static Dx2DRenderer* g;

	Dx2DRenderer() { g=this; create(); }
	~Dx2DRenderer();
	void Draw2(Dx2DRenderable2* sprite, CollisionRect* rc) override;
	bool isMeshColor(XFloat4& c) { 
		return mMeshColor.x == c.x && 
				mMeshColor.y == c.y && 
				mMeshColor.z == c.z &&
				mMeshColor.w == c.w;
	} 

	void TogglePS() {
		if(mPS == mPS0 ) mPS = mPScolor;
		else mPS = mPS0;
	}

	void SetTexturedPS() { mPS = mPScolor; }
	void SetColoredPS() { mPS = mPS0; }

public:
	VsShader*	mVS = nullptr;
	PsShader*	mPS = nullptr;
	PsShader*	mPScolor = nullptr;
	PsShader*	mPS0 = nullptr;

	Quad*		mQuad = nullptr;
	ConstantBuffer<CBChangesEveryFrame> mCB;

	ID3D11SamplerState* mSamplerLinear = nullptr;
	ID3D11BlendState*	mBlendState = nullptr;
	XFloat4 mMeshColor;
};



