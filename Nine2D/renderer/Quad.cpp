#include "pch.h"
#include "Components.h"
#include "Dx2DRenderer.h"
#include "Quad.h"

using namespace DirectX;

ID3D11InputLayout*  Quad::mVertexLayout = nullptr;

// VERTEX gVT[4*1000]; 

void RenderableToVertex(VERTEX* vt, Dx2DRenderable* rd)
{
	float ax = (rd->w * rd->ancherX);
	float ay = (rd->h * rd->ancherY);
	float lx = rd->position.x - ax;
	float ty = rd->position.y + ay;
	float rx = lx + rd->w;
	float by = ty - rd->h;

	float flx = (lx - g_Dx11.half_width) / g_Dx11.half_width;
	float frx = (rx - g_Dx11.half_width) / g_Dx11.half_width;
	float fty = (ty - g_Dx11.half_height) / g_Dx11.half_height;
	float fby = (by - g_Dx11.half_height) / g_Dx11.half_height;


    vt[0] = {flx, fby, 0.0f, 0.f, 1.f};
	vt[1] = {flx, fty, 0.0f, 0.f, 0.f};
	vt[2] = {frx, fby, 0.0f, 1.f, 1.f};
	vt[3] = {frx, fty, 0.0f, 1.f, 0.f};

}



void GetActorAnimVertexUV(Dx2DRenderable2* rd, VERTEX* Vt);
void GetActorAnimVertexUV_Farmer(Dx2DRenderable2* rd, VERTEX* Vt);
void GetActorAnimVertexUV_House(Dx2DRenderable2* rd, VERTEX* Vt);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


HRESULT Quad::create()
{
	HRESULT hr;

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
    bd.ByteWidth = sizeof(VERTEX) * mVertexCount;  // size is the VERTEX struct * 3
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

    hr = g_Dx11.device->CreateBuffer(&bd, NULL, &mVertexBuffer);       // create the buffer
	return hr;
}

HRESULT Quad::createInputLayout(ID3DBlob* mBlob)
{
	if(mVertexLayout) return S_OK;

	HRESULT hr;

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	hr = g_Dx11.device->CreateInputLayout(layout, 
										  numElements, 
										  mBlob->GetBufferPointer(),
										  mBlob->GetBufferSize(),
										  &mVertexLayout);

	return hr;
}

Quad::~Quad()
{
	SAFE_RELEASE(mVertexBuffer)
	SAFE_RELEASE(mVertexLayout)

}

void CalcVERTEX(Dx2DRenderable2* rd, VERTEX* vt)
{
	float lx = rd->position.x - (rd->w * rd->ancherX);
	float ty = rd->position.y + (rd->h * rd->ancherY);
	float rx = lx + rd->w;
	float by = ty - rd->h;

	float flx = (lx - g_Dx11.half_width) / g_Dx11.half_width;
	float frx = (rx - g_Dx11.half_width) / g_Dx11.half_width;
	float fty = (ty - g_Dx11.half_height) / g_Dx11.half_height;
	float fby = (by - g_Dx11.half_height) / g_Dx11.half_height;

	vt[0].X = flx;	vt[0].Y = fby; vt[0].Z = 0.f;
	vt[1].X = flx;	vt[1].Y = fty; vt[1].Z = 0.f;
	vt[2].X = frx;	vt[2].Y = fby; vt[2].Z = 0.f;
	vt[3].X = frx;	vt[3].Y = fty; vt[3].Z = 0.f;
}

void Quad::Update(Dx2DRenderable2* rd)
{
    VERTEX OurVertices[4] {
		{-0.5f, -0.5f, 0.0f, 0.f, 1.f},
		{-0.5f,  0.5f, 0.0f, 0.f, 0.f},
		{ 0.5f, -0.5f, 0.0f, 1.f, 1.f},
		{ 0.5f,  0.5f, 0.0f, 1.f, 0.f}	
	};

	if(rd->tex.mName == TOWNHALL_FILE_NAME ) GetActorAnimVertexUV_House(rd, OurVertices);
	else if(rd->tex.mName == FARMER_FILE_NAME ) GetActorAnimVertexUV_Farmer(rd, OurVertices);
	else if(rd->tex.mName == ULTRA_FILE_NAME ) GetActorAnimVertexUV(rd, OurVertices);

	// g_Dx11.context->UpdateSubresource( mVertexBuffer, 0, nullptr, OurVertices, 0, 0 );

    D3D11_MAPPED_SUBRESOURCE ms;
    g_Dx11.context->Map(mVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
    memcpy(ms.pData, OurVertices, sizeof(OurVertices) );
    g_Dx11.context->Unmap(mVertexBuffer, NULL);
	
}

void Quad::Apply(Dx2DRenderable2* sp)
{
	g_Dx11.context->IASetInputLayout(mVertexLayout);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	g_Dx11.context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	g_Dx11.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

