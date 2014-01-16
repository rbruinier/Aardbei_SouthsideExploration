/*
	
	Pyramid Tools - PostProcessor Class

	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __PostProcessor_H__
#define __PostProcessor_H__

#include <windows.h>

//#include <vector>
//using namespace std;

class Texture;
class PixelShader;

struct SamplerState
{
	Texture* texture;

	DWORD addressU;
	DWORD addressV;

	DWORD minFilter;
	DWORD magFilter;
	DWORD mipFilter;

	SamplerState();

	void Set(int stage);
};

class PostProcessorEffect
{
public: 
	bool useOriginal;

	SamplerState sampler1;
	SamplerState sampler2;

	float factor;

	virtual void Begin();
	virtual void End();

	virtual void SetFactor(float factor);

	virtual void PrepareRender();

protected:
	PixelShader* shader;

	PostProcessorEffect();

	virtual void SetDefaultSamplerStates();
};

struct PSChainEffect
{
public:
	PostProcessorEffect* effect;
	
	float scaleX;
	float scaleY;

	bool clearScreen;
	
	PSChainEffect(PostProcessorEffect* effect, float scaleX, float scaleY, bool clearScreen = false)
	{
		this->effect = effect;
		this->scaleX = scaleX;
		this->scaleY = scaleY;
		this->clearScreen = clearScreen;
	}
};

class PSChain
{
public:
	PSChain();

	void AddEffect(PSChainEffect* effect);
	void Render();

	//vector <PSChainEffect*> effectList;
	PSChainEffect* effectList[128];
	int effectListCount;
};

class PSUpScale4X : public PostProcessorEffect
{
public:
	PSUpScale4X();
};

class PSDownScale4X : public PostProcessorEffect
{
public:
	PSDownScale4X();

	void PrepareRender();
};

//class PSEdgeDetect : public PostProcessorEffect
//{
//public:
//	PSEdgeDetect();
//};

class PSBrightPass : public PostProcessorEffect
{
public:
	PSBrightPass();

	void PrepareRender();
	void SetLuminance(float luminance);

private:
	float luminance;
};

class PSAdd : public PostProcessorEffect
{
public:
	PSAdd();
};
//
//class PSDofCombine : public PostProcessorEffect
//{
//public:
//	PSDofCombine();
//
//	void PrepareRender();
//	void SetFocalPlane(float v1, float v2, float v3, float v4);
//
//private:
//	float v1;
//	float v2;
//	float v3;
//	float v4;
//};
//
//class PSBlurHorizontal : public PostProcessorEffect
//{
//public:
//	PSBlurHorizontal();
//
//	void PrepareRender();
//};
//
//class PSBlurVertical : public PostProcessorEffect
//{
//public:
//	PSBlurVertical();
//
//	void PrepareRender();
//};
//
//class PSBlur : public PostProcessorEffect
//{
//public:
//	PSBlur();
//
//	void PrepareRender();
//};
//
//
//class PSBloomHorizontal : public PostProcessorEffect
//{
//public:
//	PSBloomHorizontal();
//
//	void PrepareRender();
//	void SetBloomScale(float scale);
//
//private:
//	float bloomScale;
//};
//
//class PSBloomVertical : public PostProcessorEffect
//{
//public:
//	PSBloomVertical();
//
//	void PrepareRender();
//	void SetBloomScale(float scale);
//
//private:
//	float bloomScale;
//};

class PSBloom : public PostProcessorEffect
{
public:
	PSBloom();

	void PrepareRender();
	void SetBloomScale(float scale);

private:
	float bloomScale;
};

class PostProcessor
{
public:
	PostProcessor();
	~PostProcessor();

	PSUpScale4X* psUpScale4X;
	PSDownScale4X* psDownScale4X;

	//PSEdgeDetect* psEdgeDetect;
	PSBrightPass* psBrightPass;

	PSAdd* psAdd;

	//PSBlurHorizontal* psBlurHorizontal;
	//PSBlurVertical* psBlurVertical;
	//PSBlur* psBlur;

	//PSBloomHorizontal* psBloomHorizontal;
	//PSBloomVertical* psBloomVertical;
	PSBloom* psBloom;

	//PSChain* chainFastBlurHorizontal;
	//PSChain* chainFastBlurVertical;
	//PSChain* chainFastBlur;

	//PSChain* chainFastBloomHorizontal;
	//PSChain* chainFastBloomVertical;
	//PSChain* chainFastBloom;

	PSChain* chainGlow01;
	//PSChain* chainGlow02;

private:
};

#endif