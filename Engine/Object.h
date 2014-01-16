/*
	
	Pyramid Engine - Object Class


	2003, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Object_H__
#define __Object_H__

#include "../System/Pyramid.h"
#include "../System/Vector.h"
#include "../System/Material.h"

struct OBJECT_VERTEX
{
	float x, y, z;
	float nx, ny, nz;
	float u, v;
	float l, m;
};

struct OBJECT_TANGENT
{
	float tx, ty, tz;
};

struct OBJECT_FACE
{
	unsigned short a, b, c;
};

#define OBJECT_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2)

extern D3DVERTEXELEMENT9 OBJECT_VERTEX_DECLARATION[];

class VertexBuffer;
class IndexBuffer;
class VertexShader;
class PixelShader;
class Texture;

class Object
{
public:
	Object();
	~Object();

	void Destroy();

	void Create(int iNrVertices, int iNrFaces);

	void Finish(bool bIsDynamic);

	void Render();

	void ScaleUV(float fScale);
	void ScaleUV(float fScaleU, float fScaleV);

	void FlipU(float fBase = 1.0f);
	void FlipV(float fBase = 1.0f);

	void SetLocation(float fX, float fY, float fZ);
	void SetRotation(float fX, float fY, float fZ);
	void SetScale(float fX, float fY, float fZ);

	void SetLocation(Vector &pLocation);
	void SetRotation(Vector &pRotation);
	void SetScale(Vector &pScale);

	//void SetVertexShader(VertexShader* pVertexShader);
	//void SetPixelShader(PixelShader* pPixelShader);

	//void SetPerPixelLighting(bool bPerPixelLighting);

	void SetDiffuse(float fR, float fG, float fB, float fA = 1.0f);
	void SetAmbient(float fR, float fG, float fB, float fA = 1.0f);
	void SetSpecular(float fR, float fG, float fB, float fA = 0.0f);
	void SetEmissive(float fR, float fG, float fB, float fA = 0.0f);
	void SetPower(float fPower);

	void SetEnvmapEnable(bool bIsEnvmapped);

	void SetCullMode(CULL_MODE uiCullMode);

	void SetTexture(Texture* pTexture);
	void SetLightmap(Texture* pTexture);

	void SetFlipNormals(bool bFlipNormals);
	void SetCalculateNormals(bool bCalculateNormals);

	void SetEnabled(bool bRenderEnable);

	void SetTransparency(BLEND_MODE iTransMode);

	void SetWriteZBuffer(bool bWriteZBuffer);

	void Optimize(float fDif);

	OBJECT_VERTEX* vertex;
	OBJECT_FACE*   face;

	int nrVertices;
	int nrFaces;

	Vector location;
	Vector rotation;
	Vector scale;

protected:

private:
	void CalculateNormals();
	void CalculateEnvmapUV();
	//void CalculateTangents();

	void Refresh();

	VertexBuffer* vertexBuffer;
	IndexBuffer*  indexBuffer;

	VertexBuffer* vertexBufferTangent;

	//VertexShader* vertexShader;
	//PixelShader* pixelShader;

	OBJECT_TANGENT* tangent;

	int* normalCounter;

	bool isCreated;
	bool isFinished;
	bool isDynamic;
	bool isEnvmapped;
	bool isEnabled;
	bool doFlipNormals;
	bool doCalculateNormals;
	bool writeZBuffer;
	//bool doPerPixelLighting;

	Material material;

	CULL_MODE cullMode;

	Texture* texture;
	Texture* lightmap;

	BLEND_MODE transMode;
};

#endif