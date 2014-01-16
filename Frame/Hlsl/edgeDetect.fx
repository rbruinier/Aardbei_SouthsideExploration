texture sourceTexture1;

sampler2D g_samSrcColor =
sampler_state
{
    Texture = <sourceTexture1>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

float3 LuminanceConv = { 0.2125f, 0.7154f, 0.0721f };

float2 PixelKernel[4] =
{
    { 0,  1},
    { 1,  0},
    { 0, -1},
    {-1,  0}
};

float2 TexelKernel[4]
<
	string ConvertPixelsToTexels = "PixelKernel";
>;

//-----------------------------------------------------------------------------
// Pixel Shader: PostProcessPS
// Desc: Performs post-processing effect that detects and highlights edges.
//-----------------------------------------------------------------------------
float4 PostProcessPS( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Orig = tex2D( g_samSrcColor, Tex );

    float4 Sum = 0;

    for( int i = 0; i < 4; i++ )
        Sum += ( abs( Orig - tex2D( g_samSrcColor, Tex + TexelKernel[i] ) ) - 0.5f ) * 1.2 + 0.5f;

    return saturate( dot( LuminanceConv, Sum ) ) * 5;
}

technique PostProcess
{
    pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 PostProcessPS();
        ZEnable = false;
    }
}
