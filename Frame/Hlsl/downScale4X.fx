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

float2 PixelKernel[16] =
{
    { 1.5,  -1.5 },
    { 1.5,  -0.5 },
    { 1.5,   0.5 },
    { 1.5,   1.5 },

    { 0.5,  -1.5 },
    { 0.5,  -0.5 },
    { 0.5,   0.5 },
    { 0.5,   1.5 },

    {-0.5,  -1.5 },
    {-0.5,  -0.5 },
    {-0.5,   0.5 },
    {-0.5,   1.5 },

    {-1.5,  -1.5 },
    {-1.5,  -0.5 },
    {-1.5,   0.5 },
    {-1.5,   1.5 },
};

float2 TexelCoordsDownFilter[16]
<
    string ConvertPixelsToTexels = "PixelCoordsDownFilter";
>;

//-----------------------------------------------------------------------------
// Pixel Shader: DownFilter
// Desc: Perform a high-pass filter and on the source texture and scale down.
//-----------------------------------------------------------------------------
float4 DownFilter( in float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = 0;

    for (int i = 0; i < 16; i++)
    {
        Color += tex2D( g_samSrcColor, Tex + TexelCoordsDownFilter[i].xy );
    }

    return Color / 16;
}

technique PostProcess
{
    pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 DownFilter();
        ZEnable = false;
    }
}
