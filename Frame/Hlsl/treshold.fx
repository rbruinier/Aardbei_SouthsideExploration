texture sourceTexture1;

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

//-----------------------------------------------------------------------------
// Pixel Shader: Combine
// Desc: Combine the source image with the original image.
//-----------------------------------------------------------------------------
float4 Treshold( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float3 ColorOrig = tex2D( g_samSrcColor1, Tex );
    
    
    float3 tresholdValue = float3( 0.7f, 0.7f, 0.7f );
    
    float temp1 = ColorOrig.x + ColorOrig.y + ColorOrig.z;
    float temp2 = tresholdValue.x + tresholdValue.y + tresholdValue.z;
    /*
    if (ColorOrig.x < tresholdValue.x)
		ColorOrig.x = 0;
      
	if (ColorOrig.y < tresholdValue.y)
		ColorOrig.y = 0;
      
	if (ColorOrig.z < tresholdValue.z)
		ColorOrig.z = 0;
	*/
	
	if (temp1 < temp2)
		ColorOrig = float3( 0, 0, 0 );	

    return float4( ColorOrig, 1.0f );
}

technique PostProcess
{
    pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 Treshold();
        ZEnable = false;
    }
}
  
