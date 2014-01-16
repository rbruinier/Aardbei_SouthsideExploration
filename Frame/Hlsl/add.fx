texture sourceTexture1;
texture sourceTexture2;

sampler2D g_samSrcColor1 =
sampler_state
{
    Texture = <sourceTexture1>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

sampler2D g_samSrcColor2 =
sampler_state
{
    Texture = <sourceTexture2>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

//-----------------------------------------------------------------------------
// Pixel Shader: Combine
// Desc: Combine the source image with the original image.
//-----------------------------------------------------------------------------
float4 Combine( float2 Tex : TEXCOORD0, float2 Tex2 : TEXCOORD1 ) : COLOR0
{
    float3 ColorOrig = tex2D( g_samSrcColor1, Tex );

    ColorOrig += tex2D( g_samSrcColor2, Tex2 );

    return float4( ColorOrig, 1.0f );
}

technique PostProcess
{
    pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 Combine();
        ZEnable = false;
    }
}
