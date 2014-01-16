/*
	
	Pyramid Tools - PostProcessor Class

	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Main.h"

#include "./Hlsl/psUpScale4X.h"
#include "./Hlsl/psDownScale4X.h"
//#include "./Hlsl/psEdgeDetect.h"
#include "./Hlsl/psBrightPass.h"
#include "./Hlsl/psAdd.h"
//#include "./Hlsl/psDofCombine.h"
//#include "./Hlsl/psBlurHorizontal.h"
//#include "./Hlsl/psBlurVertical.h"
//#include "./Hlsl/psBlur.h"
//#include "./Hlsl/psBloomHorizontal.h"
//#include "./Hlsl/psBloomVertical.h"
#include "./Hlsl/psBloom.h"

SamplerState::SamplerState()
{
	texture = NULL;

	addressU = D3DTADDRESS_CLAMP;
	addressV = D3DTADDRESS_CLAMP;

	minFilter = D3DTEXF_LINEAR;
	magFilter = D3DTEXF_LINEAR;
	mipFilter = D3DTEXF_LINEAR;
}

void SamplerState::Set(int stage)
{
	pyramid->SetTexture(texture, stage);

	pyramid->SetSamplerState(stage, D3DSAMP_ADDRESSU, addressU);
	pyramid->SetSamplerState(stage, D3DSAMP_ADDRESSV, addressV);

	pyramid->SetSamplerState(stage, D3DSAMP_MINFILTER, minFilter);
	pyramid->SetSamplerState(stage, D3DSAMP_MAGFILTER, magFilter);
	pyramid->SetSamplerState(stage, D3DSAMP_MIPFILTER, mipFilter);
}

PostProcessorEffect::PostProcessorEffect()
{
	shader = NULL;

	SetDefaultSamplerStates();
}

void PostProcessorEffect::SetDefaultSamplerStates()
{
	sampler1.texture = sampler2.texture = NULL;

	sampler1.addressU = sampler2.addressU = D3DTADDRESS_CLAMP;
	sampler1.addressV = sampler2.addressV = D3DTADDRESS_CLAMP;

	sampler1.minFilter = sampler2.minFilter = D3DTEXF_LINEAR;
	sampler1.magFilter = sampler2.magFilter = D3DTEXF_LINEAR;
	sampler1.mipFilter = sampler2.mipFilter = D3DTEXF_LINEAR;
}

void PostProcessorEffect::Begin()
{
	if (shader != NULL)
	{
		sampler1.Set(0);
		sampler2.Set(1);

		pyramid->SetPixelShader(shader);

		PrepareRender();
	}
}

void PostProcessorEffect::End()
{
	if (shader != NULL)
	{
		pyramid->SetPixelShader(NULL);
	}
}

void PostProcessorEffect::SetFactor(float factor)
{
	this->factor = factor;
}

void PostProcessorEffect::PrepareRender()
{
}

PSChain::PSChain()
{
	effectListCount = 0;
}

void PSChain::AddEffect(PSChainEffect* effect)
{
//	effectList.push_back(effect);
	effectList[effectListCount++] = effect;
}

void PSChain::Render()
{
	float u = 1.0f;
	float v = 1.0f;

	RECT r;

	pyramid->GetViewport(r);

	float w = (float)r.right - r.left;
	float h = (float)r.bottom - r.top;

	for (int i = 0; i < (int)effectListCount; i++)
	{
		w *= effectList[i]->scaleX;
		h *= effectList[i]->scaleY;

		if (i == 0)
		{
			effectList[i]->effect->sampler1.texture = renderChain->GetOriginal();
		}
		else
		{
			effectList[i]->effect->sampler1.texture = renderChain->GetSource();

			if (effectList[i]->effect->useOriginal)
			{
				effectList[i]->effect->sampler2.texture = renderChain->GetOriginal();
			}
		}

		drawer2D->BeginScene(BLEND_NONE);

		effectList[i]->effect->Begin();

		pyramid->SetRenderTarget(renderChain->GetTarget());

		if (effectList[i]->clearScreen)
		{
			pyramid->ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x00000000);
		}

		drawer2D->Draw(0, 0, 0, 0,
			           w, 0, u, 0,
			           0, h, 0, v,
			           w, h, u, v);

		effectList[i]->effect->End();

		drawer2D->EndScene();

		renderChain->Flip();

		u *= effectList[i]->scaleX;
		v *= effectList[i]->scaleY;
	}

	pyramid->ResetRenderTarget();
}

PSUpScale4X::PSUpScale4X()
{
	pyramid->CreatePixelShader((DWORD*)g_ps20_UpScale4X, &shader);
}

PSDownScale4X::PSDownScale4X()
{
	pyramid->CreatePixelShader((DWORD*)g_ps20_DownScale4X, &shader);
}

void PSDownScale4X::PrepareRender()
{
	RECT r;

	pyramid->GetViewport(r);

	float kernel[16][4];

	for (int i = 0; i < 16; i++)
	{
		kernel[i][0] = pkDownScale4X[i][0] / (float)(r.right - r.left);
		kernel[i][1] = pkDownScale4X[i][1] / (float)(r.bottom - r.top);
	}

	pyramid->SetPixelShaderConstantF(0, (float*)kernel, 16);
}

//PSEdgeDetect::PSEdgeDetect()
//{
//	pyramid->CreatePixelShader((DWORD*)g_ps20_EdgeDetect, &shader);
//}

PSBrightPass::PSBrightPass()
{
	pyramid->CreatePixelShader((DWORD*)g_ps20_BrightPass, &shader);

	SetLuminance(0.03f);
}

void PSBrightPass::SetLuminance(float luminance)
{
	this->luminance = luminance;
}

void PSBrightPass::PrepareRender()
{
	float lum[4] = {luminance, 0, 0, 0};

	pyramid->SetPixelShaderConstantF(0, (float*)lum, 1);
}

PSAdd::PSAdd()
{
	pyramid->CreatePixelShader((DWORD*)g_ps20_Add, &shader);

	useOriginal = true;
}
//
//PSDofCombine::PSDofCombine()
//{
//	pyramid->CreatePixelShader((DWORD*)g_ps20_DofCombine, &shader);
//
//	useOriginal = true;
//
//	SetFocalPlane(0, 0, 0.2f, -0.6f);
//}
//
//void PSDofCombine::SetFocalPlane(float v1, float v2, float v3, float v4)
//{
//	this->v1 = v1;
//	this->v2 = v2;
//	this->v3 = v3;
//	this->v4 = v4;
//}
//
//void PSDofCombine::PrepareRender()
//{
//	float focalPlane[4] = {v1, v2, v3, v4};
//
//	pyramid->SetPixelShaderConstantF(0, (float*)focalPlane, 1);
//}
//
//PSBlurHorizontal::PSBlurHorizontal()
//{
//	pyramid->CreatePixelShader((DWORD*)g_ps20_BlurHorizontal, &shader);
//
//	SetFactor(1.f);
//}
//
//void PSBlurHorizontal::PrepareRender()
//{
//	RECT r;
//
//	pyramid->GetViewport(r);
//
//	float kernel[13][4];
//
//	for (int i = 0; i < 13; i++)
//	{
//		kernel[i][0] = (pkBlurHorizontal[i][0] / (r.right - r.left)) * factor;
//		kernel[i][1] = (pkBlurHorizontal[i][1] / (r.bottom - r.top)) * factor;
//	}
//
//	pyramid->SetPixelShaderConstantF(0, (float*)kernel, 13);
//}
//
//PSBlurVertical::PSBlurVertical()
//{
//	pyramid->CreatePixelShader((DWORD*)g_ps20_BlurVertical, &shader);
//
//	SetFactor(1.f);
//}
//
//void PSBlurVertical::PrepareRender()
//{
//	RECT r;
//
//	pyramid->GetViewport(r);
//
//	float kernel[13][4];
//
//	for (int i = 0; i < 13; i++)
//	{
//		kernel[i][0] = (pkBlurVertical[i][0] / (r.right - r.left)) * factor;
//		kernel[i][1] = (pkBlurVertical[i][1] / (r.bottom - r.top)) * factor;
//	}
//
//	pyramid->SetPixelShaderConstantF(0, (float*)kernel, 13);
//}
//
//PSBlur::PSBlur()
//{
//	pyramid->CreatePixelShader((DWORD*)g_ps20_Blur, &shader);
//
//	SetFactor(1.f);
//}
//
//void PSBlur::PrepareRender()
//{
//	RECT r;
//
//	pyramid->GetViewport(r);
//
//	float kernel[26][4];
//
//	for (int i = 0; i < 26; i++)
//	{
//		kernel[i][0] = (pkBlur[i][0] / (r.right - r.left)) * factor;
//		kernel[i][1] = (pkBlur[i][1] / (r.bottom - r.top)) * factor;
//	}
//
//	pyramid->SetPixelShaderConstantF(0, (float*)kernel, 26);
//}
//
//PSBloomHorizontal::PSBloomHorizontal()
//{
//	pyramid->CreatePixelShader((DWORD*)g_ps20_BloomHorizontal, &shader);
//
//	SetFactor(1.f);
//	SetBloomScale(1.5f);
//}
//
//void PSBloomHorizontal::SetBloomScale(float scale)
//{
//	bloomScale = scale;
//}
//
//void PSBloomHorizontal::PrepareRender()
//{
//	RECT r;
//
//	pyramid->GetViewport(r);
//
//	float kernel[13][4];
//
//	for (int i = 0; i < 13; i++)
//	{
//		kernel[i][0] = (pkBloomHorizontal[i][0] / (r.right - r.left)) * factor;
//		kernel[i][1] = (pkBloomHorizontal[i][1] / (r.bottom - r.top)) * factor;
//	}
//
//	pyramid->SetPixelShaderConstantF(0, (float*)kernel, 13);
//
//	float bloom[4] = {bloomScale, 0, 0, 0};
//
//	pyramid->SetPixelShaderConstantF(13, (float*)bloom, 1);
//}
//
//PSBloomVertical::PSBloomVertical()
//{
//	pyramid->CreatePixelShader((DWORD*)g_ps20_BloomVertical, &shader);
//
//	SetFactor(1.f);
//	SetBloomScale(1.5f);
//}
//
//void PSBloomVertical::SetBloomScale(float scale)
//{
//	bloomScale = scale;
//}
//
//void PSBloomVertical::PrepareRender()
//{
//	RECT r;
//
//	pyramid->GetViewport(r);
//
//	float kernel[13][4];
//
//	for (int i = 0; i < 13; i++)
//	{
//		kernel[i][0] = (pkBloomVertical[i][0] / (r.right - r.left)) * factor;
//		kernel[i][1] = (pkBloomVertical[i][1] / (r.bottom - r.top)) * factor;
//	}
//
//	pyramid->SetPixelShaderConstantF(0, (float*)kernel, 13);
//
//	float bloom[4] = {bloomScale, 0, 0, 0};
//
//	pyramid->SetPixelShaderConstantF(13, (float*)bloom, 1);
//}

PSBloom::PSBloom()
{
	pyramid->CreatePixelShader((DWORD*)g_ps20_Bloom, &shader);

	SetFactor(1.f);
	SetBloomScale(1.5f);
}

void PSBloom::SetBloomScale(float scale)
{
	bloomScale = scale;
}

void PSBloom::PrepareRender()
{
	RECT r;

	pyramid->GetViewport(r);

	float kernel[26][4];

	for (int i = 0; i < 26; i++)
	{
		kernel[i][0] = (pkBloom[i][0] / (r.right - r.left)) * factor;
		kernel[i][1] = (pkBloom[i][1] / (r.bottom - r.top)) * factor;
	}

	pyramid->SetPixelShaderConstantF(0, (float*)kernel, 26);

	float bloom[4] = {bloomScale, 0, 0, 0};

	pyramid->SetPixelShaderConstantF(26, (float*)bloom, 1);
}

PostProcessor::PostProcessor()
{
	psUpScale4X = new PSUpScale4X();
	psDownScale4X = new PSDownScale4X();

	psBrightPass = new PSBrightPass();

	psAdd = new PSAdd();

	//psBlurHorizontal = new PSBlurHorizontal();
	//psBlurVertical = new PSBlurVertical();
	//psBlur = new PSBlur();

	//psBloomHorizontal = new PSBloomHorizontal();
	//psBloomVertical = new PSBloomVertical();
	psBloom = new PSBloom();

	// initialize some pixel shader chains

	// fast horizontal blur
	//chainFastBlurHorizontal = new PSChain();

	//chainFastBlurHorizontal->AddEffect(new PSChainEffect(psDownScale4X, 0.25f, 0.25f));
	//chainFastBlurHorizontal->AddEffect(new PSChainEffect(psBlurHorizontal, 1.f, 1.f));
	//chainFastBlurHorizontal->AddEffect(new PSChainEffect(psUpScale4X, 4.f, 4.f));

	// fast vertical blur
	//chainFastBlurVertical = new PSChain();

	//chainFastBlurVertical->AddEffect(new PSChainEffect(psDownScale4X, 0.25f, 0.25f));
	//chainFastBlurVertical->AddEffect(new PSChainEffect(psBlurVertical, 1.f, 1.f));
	//chainFastBlurVertical->AddEffect(new PSChainEffect(psUpScale4X, 4.f, 4.f));

	// fast blur
	//chainFastBlur = new PSChain();

	//chainFastBlur->AddEffect(new PSChainEffect(psDownScale4X, 0.25f, 0.25f));
	//chainFastBlur->AddEffect(new PSChainEffect(psBlur, 1.f, 1.f, true));
	//chainFastBlur->AddEffect(new PSChainEffect(psUpScale4X, 4.f, 4.f));

	// fast horizontal bloom
	//chainFastBloomHorizontal = new PSChain();

	//chainFastBloomHorizontal->AddEffect(new PSChainEffect(psDownScale4X, 0.25f, 0.25f));
	//chainFastBloomHorizontal->AddEffect(new PSChainEffect(psBloomHorizontal, 1.f, 1.f));
	//chainFastBloomHorizontal->AddEffect(new PSChainEffect(psUpScale4X, 4.f, 4.f));

	// fast vertical bloom
	//chainFastBloomVertical = new PSChain();

	//chainFastBloomVertical->AddEffect(new PSChainEffect(psDownScale4X, 0.25f, 0.25f));
	//chainFastBloomVertical->AddEffect(new PSChainEffect(psBloomVertical, 1.f, 1.f));
	//chainFastBloomVertical->AddEffect(new PSChainEffect(psUpScale4X, 4.f, 4.f));

	// fast bloom
	//chainFastBloom = new PSChain();

	//chainFastBloom->AddEffect(new PSChainEffect(psDownScale4X, 0.25f, 0.25f));
	//chainFastBloom->AddEffect(new PSChainEffect(psBloom, 1.f, 1.f));
	//chainFastBloom->AddEffect(new PSChainEffect(psUpScale4X, 4.f, 4.f));

	// glow 01
	chainGlow01 = new PSChain();

	chainGlow01->AddEffect(new PSChainEffect(psDownScale4X, 0.25f, 0.25f, false));
	chainGlow01->AddEffect(new PSChainEffect(psDownScale4X, 0.25f, 0.25f, true));
	chainGlow01->AddEffect(new PSChainEffect(psBrightPass, 1.f, 1.f, true));
	chainGlow01->AddEffect(new PSChainEffect(psBloom, 1.f, 1.f));
	chainGlow01->AddEffect(new PSChainEffect(psBloom, 1.f, 1.f));
	chainGlow01->AddEffect(new PSChainEffect(psBloom, 1.f, 1.f));
	chainGlow01->AddEffect(new PSChainEffect(psUpScale4X, 4.f, 4.f));
	chainGlow01->AddEffect(new PSChainEffect(psAdd, 4.f, 4.f));
}

PostProcessor::~PostProcessor()
{
}

