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

//-----------------------------------------------------------------------------
// Pixel Shader: UpFilterPS
// Desc: Performs upfiltering to scale the image to the original size.
//-----------------------------------------------------------------------------
float4 UpFilter( float2 Tex : TEXCOORD0 ) : COLOR0
{
    return tex2D( g_samSrcColor, Tex );
}

technique PostProcess
{
    pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 UpFilter();
        ZEnable = false;
    }
}
