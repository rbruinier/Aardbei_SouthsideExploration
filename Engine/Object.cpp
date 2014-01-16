/*
	
	Pyramid Engine - Object Class


	2003, Robert Jan Bruinier (rob / aardbei)

*/

#include "Object.h"

#include <math.h>

#include "../System/VertexBuffer.h"
#include "../System/IndexBuffer.h"
#include "../System/VertexShader.h"
#include "../System/PixelShader.h"
#include "../System/Matrix.h"

D3DVERTEXELEMENT9 OBJECT_VERTEX_DECLARATION[] = 
{
	{0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
	{0, 24, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	{0, 32, D3DDECLTYPE_FLOAT2,	  D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
	{1, 40, D3DDECLTYPE_FLOAT3,	  D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,	0},
	D3DDECL_END()
};

extern Pyramid *pyramid;

Object::Object()
{
	vertexBuffer = NULL;
	indexBuffer  = NULL;

	vertexBufferTangent = NULL;

	//vertexShader = NULL;
	//pixelShader  = NULL;

	vertex  = NULL;
	face    = NULL;
	tangent = NULL;

	isCreated  = false;
	isFinished = false;

	SetEnvmapEnable(false);
	SetCullMode(CULL_CW);
	SetTexture(NULL);
	SetLightmap(NULL);
	SetFlipNormals(false);
	SetCalculateNormals(true);
	SetEnabled(true);
	SetTransparency(BLEND_NONE);
	SetWriteZBuffer(true);
	//SetPerPixelLighting(false);

	SetScale(1, 1, 1);
	SetLocation(0, 0, 0);
	SetRotation(0, 0, 0);
}

Object::~Object()
{
} 

void Object::Create(int iNrVertices, int iNrFaces)
{
	if (isCreated)
	{
		return;
	}

	nrVertices = iNrVertices;
	nrFaces    = iNrFaces;

	vertex = new OBJECT_VERTEX[nrVertices];
	face   = new OBJECT_FACE[nrFaces];

	normalCounter = new int[nrVertices];

	isCreated = true;
}

void Object::Finish(bool bIsDynamic)
{
	if (isFinished || !isCreated)
	{
		return;
	}

	isDynamic = bIsDynamic;

	if (isEnvmapped)
	{
		isDynamic = true;
	}

	pyramid->CreateVertexBuffer(nrVertices, sizeof(OBJECT_VERTEX), OBJECT_VERTEX_FVF, 
		                        isDynamic, false, &vertexBuffer);

	pyramid->CreateIndexBuffer(nrFaces, false, false, &indexBuffer);

	if (doCalculateNormals)
	{
		CalculateNormals();
	}


	/*if (doPerPixelLighting)
	{
		if (tangent == NULL)
		{
			tangent = new OBJECT_TANGENT[nrVertices];
		}

		if (vertexBufferTangent == NULL)
		{
			pyramid->CreateVertexBuffer(nrVertices, sizeof(OBJECT_TANGENT), 0, 
				                        isDynamic, false, &vertexBufferTangent);
		}

		CalculateTangents();

		vertexBufferTangent->Update(tangent);
	}*/


	vertexBuffer->Update(vertex);
	indexBuffer->Update(face);

	isFinished = true;
}

void Object::Refresh()
{
	if (doCalculateNormals)
	{
		CalculateNormals();
	}

	//if (doPerPixelLighting)
	//{
	//	CalculateTangents();

	//	vertexBufferTangent->Update(tangent);
	//}

	vertexBuffer->Update(vertex, 0, nrVertices * sizeof(OBJECT_VERTEX));
	indexBuffer->Update(face, 0, nrFaces * sizeof(OBJECT_FACE));
}

void Object::Destroy()
{
	if (isCreated)
	{
		delete [] vertex;
		delete [] face;

		delete [] normalCounter;
	}

	if (tangent != NULL)
	{
		delete [] tangent;
	}
}

void Object::CalculateNormals()
{
	int i;

	for (i = 0; i < nrVertices; i++) 
	{
		vertex[i].nx = vertex[i].ny = vertex[i].nz = 0;
		
		normalCounter[i]   = 0;
	}

    for (i = 0; i < nrFaces; i++) 
	{
        int a = face[i].a;
        int b = face[i].b;
        int c = face[i].c;

        float relx1 = vertex[b].x - vertex[a].x;
        float rely1 = vertex[b].y - vertex[a].y;
        float relz1 = vertex[b].z - vertex[a].z;

        float relx2 = vertex[c].x - vertex[a].x;
        float rely2 = vertex[c].y - vertex[a].y;
        float relz2 = vertex[c].z - vertex[a].z;

        float nx = (rely1 * relz2) - (relz1 * rely2);
        float ny = (relz1 * relx2) - (relx1 * relz2);
        float nz = (relx1 * rely2) - (rely1 * relx2);

		vertex[a].nx += nx;
		vertex[a].ny += ny;
		vertex[a].nz += nz;

		normalCounter[a]++;

		vertex[b].nx += nx;
		vertex[b].ny += ny;
		vertex[b].nz += nz;

		normalCounter[b]++;

		vertex[c].nx += nx;
		vertex[c].ny += ny;
		vertex[c].nz += nz;

		normalCounter[c]++;
    }

	for (i = 0; i < nrVertices; i++) 
	{
		float nx = vertex[i].nx / normalCounter[i];
		float ny = vertex[i].ny / normalCounter[i];
		float nz = vertex[i].nz / normalCounter[i];

		float magnitude = (float) sqrt((nx * nx) + (ny * ny) + (nz * nz));

		vertex[i].nx = -nx / magnitude; 
		vertex[i].ny = -ny / magnitude; 
		vertex[i].nz = -nz / magnitude; 
	}

	if (doFlipNormals)
	{
		for (i = 0; i < nrVertices; i++) 
		{
			vertex[i].nx = -vertex[i].nx;
			vertex[i].ny = -vertex[i].ny;
			vertex[i].nz = -vertex[i].nz;
		}
	}
}

//void Object::CalculateTangents()
//{
//	//int i;
//
//	//Vector *binormal = new Vector[nrVertices];
//
//	//for (i = 0; i < nrVertices; i++) 
//	//{
//	//	tangent[i].tx = tangent[i].ty = tangent[i].tz = 0;
//	//	binormal[i].x = binormal[i].y = binormal[i].z = 0;
//	//	
//	//	normalCounter[i]   = 0;
//	//}
//
// //   for (i = 0; i < nrFaces; i++) 
//	//{
// //       int a = face[i].a;
// //       int b = face[i].b;
// //       int c = face[i].c;
//	//	
//	//	Vector t1, t2, t;
//
//	//	// x
//	//	t1.x = vertex[b].x - vertex[a].x;
//	//	t1.y = vertex[b].u - vertex[a].u;
//	//	t1.z = vertex[b].v - vertex[a].v;
//
//	//	t2.x = vertex[c].x - vertex[a].x;
//	//	t2.y = vertex[c].u - vertex[a].u;
//	//	t2.z = vertex[c].v - vertex[a].v;
//
//	//	t = t1.CrossProduct(t2);
//
//	//	if (t.x != 0)
//	//	{
//	//		tangent[a].tx += -t.y / t.x;
//	//		tangent[b].tx += -t.y / t.x;
//	//		tangent[c].tx += -t.y / t.x;
//
//	//		binormal[a].x += -t.z / t.x;
//	//		binormal[b].x += -t.z / t.x;
//	//		binormal[c].x += -t.z / t.x;
//	//	
//	//		normalCounter[a]++;
//	//	}
//	//	
//	//	// y
//	//	t1.x = vertex[b].y - vertex[a].y;
//	//	t2.x = vertex[c].y - vertex[a].y;
//
//	//	t = t1.CrossProduct(t2);
//
//	//	if (t.x != 0)
//	//	{
//	//		tangent[a].ty += -t.y / t.x;
//	//		tangent[b].ty += -t.y / t.x;
//	//		tangent[c].ty += -t.y / t.x;
//
//	//		binormal[a].y += -t.z / t.x;
//	//		binormal[b].y += -t.z / t.x;
//	//		binormal[c].y += -t.z / t.x;
//
//	//		normalCounter[b]++;
//	//	}
//
//	//	// z
//	//	t1.x = vertex[b].z - vertex[a].z;
//	//	t2.x = vertex[c].z - vertex[a].z;
//
//	//	t = t1.CrossProduct(t2);
//
//	//	if (t.x != 0)
//	//	{
//	//		tangent[a].tz += -t.y / t.x;
//	//		tangent[b].tz += -t.y / t.x;
//	//		tangent[c].tz += -t.y / t.x;
//
//	//		binormal[a].z += -t.z / t.x;
//	//		binormal[b].z += -t.z / t.x;
//	//		binormal[c].z += -t.z / t.x;
//
//	//		normalCounter[c]++;
//	//	}
// //   }
//
//	//for (i = 0; i < nrVertices; i++) 
//	//{
//	//	Vector t1, t2, t, n;
//
//	//	t1.x = tangent[i].tx;
//	//	t1.y = tangent[i].ty;
//	//	t1.z = tangent[i].tz;
//
//	//	t2.x = binormal[i].x;
//	//	t2.y = binormal[i].y;
//	//	t2.z = binormal[i].z;
//
//	//	n.x = vertex[i].nx;
//	//	n.y = vertex[i].ny;
//	//	n.z = vertex[i].nz;
//
//	//	t1 = t1.Normalize();
//	//	t2 = t2.Normalize();
//
//	//	tangent[i].tx = t1.x;
//	//	tangent[i].ty = t1.y;
//	//	tangent[i].tz = t1.z;
//
//	//	t = t1.CrossProduct(t2);
//
//	//	t = t.Normalize();
//
//	//	if (t.DotProduct(n) < 0.0f)
//	//	{
//	//		t.x = -t.x;
//	//		t.y = -t.y;
//	//		t.z = -t.z;
//	//	}
//
//	//	vertex[i].nx = t.x;
//	//	vertex[i].ny = t.y;
//	//	vertex[i].nz = t.z;
//	//}
//
//	//delete [] binormal;
//}

//void Object::SetPerPixelLighting(bool bPerPixelLighting)
//{
//	doPerPixelLighting = bPerPixelLighting;
//}

void Object::CalculateEnvmapUV()
{
    Matrix matWorld, matView, matWV;

	pyramid->GetViewMatrix(matView);
	pyramid->GetWorldMatrix(matWorld);

	matWV = matWorld * matView;

	for (int i = 0; i < nrVertices; i++)
	{
		vertex[i].u = 0.5f + (0.5f * (vertex[i].nx  * matWV._11 + vertex[i].ny  * matWV._21 + vertex[i].nz  * matWV._31));
		vertex[i].v = 0.5f - (0.5f * (vertex[i].nx  * matWV._12 + vertex[i].ny  * matWV._22 + vertex[i].nz  * matWV._32));
	}
}

void Object::Render()
{
	if (!isCreated || !isEnabled)
	{
		return;
	}

	if (!isFinished)
	{
		Finish(false);
	}

	Matrix matRot, matLoc, matScl;
	
	matRot = Matrix::RotateY(rotation.y) * Matrix::RotateZ(rotation.z)  * Matrix::RotateX(rotation.x);
	matLoc = Matrix::Translation(location.x, location.y, location.z);
	matScl = Matrix::Scale(scale.x, scale.y, scale.z);

	pyramid->SetWorldMatrix(matScl * matRot * matLoc);

	if (isDynamic || isEnvmapped)
	{
		if (doCalculateNormals)
		{
			CalculateNormals();
		}
		
		if (isEnvmapped)
		{
			CalculateEnvmapUV();
		}

		Refresh();
	}

	pyramid->SetMaterial(material);

	if (material.power > 0.0f)
	{
		pyramid->SetRenderState(D3DRS_SPECULARENABLE, true);		
	}
	else
	{
		pyramid->SetRenderState(D3DRS_SPECULARENABLE, false);
	}

	pyramid->SetCullMode(cullMode);

	if (texture != NULL)
	{
		pyramid->SetTexture(texture);
	}
	else
	{
		pyramid->SetTexture(NULL);
	}

	if (lightmap != NULL)
	{
		pyramid->SetTexture(lightmap, 1);

		pyramid->SetTextureStageState(1,	D3DTSS_COLOROP,			D3DTOP_MODULATE); 
		pyramid->SetTextureStageState(1,	D3DTSS_TEXCOORDINDEX,	1); 
	}
	else
	{
		pyramid->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	}

	if (writeZBuffer)
	{
		pyramid->SetWriteZBufferEnable(true);
	}
	else
	{
		pyramid->SetWriteZBufferEnable(false);
	}

	pyramid->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pyramid->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	pyramid->SetTransparency(transMode);
	
	pyramid->SetVertexStream(vertexBuffer);
	pyramid->SetIndexStream(indexBuffer);

	//if (vertexShader != NULL)
	//{
	//	Matrix matView, matProj, matWorld, matTransform, matWorldInverse;

	//	pyramid->GetWorldMatrix(matWorld);
	//	pyramid->GetViewMatrix(matView);
	//	pyramid->GetProjectionMatrix(matProj);

	//	matTransform    = (matWorld * matView * matProj).Transpose();

	//	matWorldInverse = (matWorld.Inverse()).Transpose();

	//	matWorld = matWorld.Transpose();

	//	matView = matView.Transpose();

	//	pyramid->SetVertexShaderConstantF( 0, (float*)&matTransform, 4);
	//	pyramid->SetVertexShaderConstantF( 4, (float*)&matWorld, 4);
	//	pyramid->SetVertexShaderConstantF( 8, (float*)&matWorldInverse, 4);
	//	pyramid->SetVertexShaderConstantF(12, (float*)&matView, 4);

	//	float power[] = {material.power, 0, 0, 0};

	//	pyramid->SetVertexShaderConstantF(40, (float*)&material.diffuse, 4);
	//	pyramid->SetVertexShaderConstantF(41, (float*)&material.specular, 4);
	//	pyramid->SetVertexShaderConstantF(42, (float*)&material.emissive, 4);
	//	pyramid->SetVertexShaderConstantF(43, (float*)&power, 4);

	//	pyramid->SetVertexShader(vertexShader);
	//}

	//if (pixelShader != NULL)
	//{
	//	pyramid->SetPixelShader(pixelShader);
	//}

	//if (doPerPixelLighting)
	//{
	//	pyramid->SetVertexStream(vertexBufferTangent, 1);
	//}

	pyramid->DrawIndexedPrimitiveList(0, nrVertices, 0, nrFaces);

	pyramid->SetPixelShader(NULL);
//	pyramid->SetVertexShader(NULL);

	pyramid->SetVertexStream(NULL, 1);
}


void Object::ScaleUV(float fScale)
{
	ScaleUV(fScale, fScale);
}

void Object::ScaleUV(float fScaleU, float fScaleV)
{
	for (int i = 0; i < nrVertices; i++)
	{
		vertex[i].u *= fScaleU;
		vertex[i].v *= fScaleV;
	}
}

void Object::FlipU(float fBase)
{
	for (int i = 0; i < nrVertices; i++)
	{
		vertex[i].u = fBase - vertex[i].u;
	}
}

void Object::FlipV(float fBase)
{
	for (int i = 0; i < nrVertices; i++)
	{
		vertex[i].v = fBase - vertex[i].v;
	}
}

void Object::SetLocation(float fX, float fY, float fZ)
{
	location.x = fX;
	location.y = fY;
	location.z = fZ;
}

void Object::SetRotation(float fX, float fY, float fZ)
{
	rotation.x = fX * _PI / 180.f;
	rotation.y = fY * _PI / 180.f;
	rotation.z = fZ * _PI / 180.f;
}

void Object::SetScale(float fX, float fY, float fZ)
{
	scale.x = fX;
	scale.y = fY;
	scale.z = fZ;
}

void Object::SetLocation(Vector &pLocation)
{
	location = pLocation;
}

void Object::SetRotation(Vector &pRotation)
{
	rotation = pRotation;
}

void Object::SetScale(Vector &pScale)
{
	scale = pScale;
}

//void Object::SetVertexShader(VertexShader* pVertexShader)
//{
//	vertexShader = pVertexShader;
//}
//
//void Object::SetPixelShader(PixelShader* pPixelShader)
//{
//	pixelShader = pPixelShader;
//}

void Object::SetDiffuse(float fR, float fG, float fB, float fA)
{
	material.SetDiffuse(fR, fG, fB, fA);
}

void Object::SetAmbient(float fR, float fG, float fB, float fA)
{
	material.SetAmbient(fR, fG, fB, fA);
}

void Object::SetSpecular(float fR, float fG, float fB, float fA)
{
	material.SetSpecular(fR, fG, fB, fA);
}

void Object::SetEmissive(float fR, float fG, float fB, float fA)
{
	material.SetEmissive(fR, fG, fB, fA);
}

void Object::SetPower(float fPower)
{
	material.SetPower(fPower);
}

void Object::SetCullMode(CULL_MODE uiCullMode)
{
	cullMode = uiCullMode;
}

void Object::SetEnvmapEnable(bool bIsEnvmapped)
{
	isEnvmapped = bIsEnvmapped;
}

void Object::SetTexture(Texture* pTexture)
{
	texture = pTexture;
}

void Object::SetLightmap(Texture* pTexture)
{
	lightmap = pTexture;
}

void Object::SetFlipNormals(bool bFlipNormals)
{
	doFlipNormals = bFlipNormals;
}

void Object::SetCalculateNormals(bool bCalculateNormals)
{
	doCalculateNormals = bCalculateNormals;
}


void Object::SetWriteZBuffer(bool bWriteZBuffer)
{
	writeZBuffer = bWriteZBuffer;
}

void Object::SetEnabled(bool bRenderEnable)
{
	isEnabled = bRenderEnable;
}

void Object::SetTransparency(BLEND_MODE iTransMode)
{
	transMode = iTransMode;
}

//void Object::Optimize(float fDif) {
//	/*for (int i = 0; i < nrFaces; i++) 
//	{
//		int a = face[i].a;
//		int b = face[i].b;
//		int c = face[i].c;
//
//		OBJECT_VERTEX v1 = vertex[a];
//		OBJECT_VERTEX v2 = vertex[b];
//		OBJECT_VERTEX v3 = vertex[c];
//
//		for (int j = 0; j < nrVertices; j++) 
//		{
//			OBJECT_VERTEX v = vertex[j];
//			if (a != j) 
//			{
//				if ((v1.x >= (v.x - fDif)) && (v1.x <= (v.x + fDif)) &&
//					(v1.y >= (v.y - fDif)) && (v1.y <= (v.y + fDif)) &&
//					(v1.z >= (v.z - fDif)) && (v1.z <= (v.z + fDif)))
//					a = j;
//			}
//			if (b != j) 
//			{
//				if ((v2.x >= (v.x - fDif)) && (v2.x <= (v.x + fDif)) &&
//					(v2.y >= (v.y - fDif)) && (v2.y <= (v.y + fDif)) &&
//					(v2.z >= (v.z - fDif)) && (v2.z <= (v.z + fDif)))
//					b = j;
//			}
//			if (c != j) 
//			{
//				if ((v3.x >= (v.x - fDif)) && (v3.x <= (v.x + fDif)) &&
//					(v3.y >= (v.y - fDif)) && (v3.y <= (v.y + fDif)) &&
//					(v3.z >= (v.z - fDif)) && (v3.z <= (v.z + fDif)))
//					c = j;
//			}
//		}
//
//		face[i].a = a;
//		face[i].b = b;
//		face[i].c = c;
//	}*/
//}







