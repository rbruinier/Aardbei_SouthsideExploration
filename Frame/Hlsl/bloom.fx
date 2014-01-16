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

static const int g_cKernelSize = 26;

float bloomScale = 1.5f;

float2 PixelKernel[g_cKernelSize] =
{
    { -6,  0 },
    { -5,  0 },
    { -4,  0 },
    { -3,  0 },
    { -2,  0 },
    { -1,  0 },
    {  0,  0 },
    {  1,  0 },
    {  2,  0 },
    {  3,  0 },
    {  4,  0 },
    {  5,  0 },
    {  6,  0 },
    {  0, -6 },
    {  0, -5 },
    {  0, -4 },
    {  0, -3 },
    {  0, -2 },
    {  0, -1 },
    {  0,  0 },
    {  0,  1 },
    {  0,  2 },
    {  0,  3 },
    {  0,  4 },
    {  0,  5 },
    {  0,  6 },
};

float2 TexelKernel[g_cKernelSize]
<
    string ConvertPixelsToTexels = "PixelKernel";
>;

static const float BlurWeights[g_cKernelSize] = 
{
    0.001108,
    0.004382,
    0.0134975,
    0.0323795,
    0.0604925,
    0.0880165,
    0.0997355,
    0.0880165,
    0.0604925,
    0.0323795,
    0.0134975,
    0.004382,
    0.001108,
    0.001108,
    0.004382,
    0.0134975,
    0.0323795,
    0.0604925,
    0.0880165,
    0.0997355,
    0.0880165,
    0.0604925,
    0.0323795,
    0.0134975,
    0.004382,
    0.001108,
};

//-----------------------------------------------------------------------------
// Pixel Shader: HorizontalBlur
// Desc: Blurs the image horizontally
//-----------------------------------------------------------------------------
float4 PostProcessPS( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = 0;

	for (int i = 0; i < 26; i++)
	{    
		Color += tex2D( g_samSrcColor, Tex + TexelKernel[i].xy ) * BlurWeights[i];
	}
    
    return Color * bloomScale;
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
