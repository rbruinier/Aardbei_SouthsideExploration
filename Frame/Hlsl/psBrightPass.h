#if 0
//
// Generated by Microsoft (R) D3DX9 Shader Compiler 9.08.299.0000
//
//   fxc /EBrightPassFilter /Tps_2_0 /FhpsBrightPass.h BrightPass.fx
//
//
// Parameters:
//
//   sampler2D g_samSrcColor;
//   float luminance;
//
//
// Registers:
//
//   Name          Reg   Size
//   ------------- ----- ----
//   luminance     c0       1
//   g_samSrcColor s0       1
//
//
// Default values:
//
//   luminance
//     c0   = { 0.08, 0, 0, 0 };
//

    ps_2_0
    def c1, 0.00100000005, 0.180000007, 1.5625, 1
    def c2, -5, 0, 10, 0
    dcl t0.xy
    dcl_2d s0
    texld r0, t0, s0
    mov r0.w, c1.x
    add r0.w, r0.w, c0.x
    rcp r0.w, r0.w
    mul r0.w, r0.w, c1.y
    mul r0.xyz, r0, r0.w
    mad r1.xyz, r0, c1.z, c1.w
    mad r1.xyz, r0, r1, c2.x
    max r0.xyz, r1, c2.y
    add r1.xyz, r0, c2.z
    rcp r1.x, r1.x
    rcp r1.y, r1.y
    rcp r1.z, r1.z
    mul r0.xyz, r0, r1
    mov r0.w, c1.w
    mov oC0, r0

// approximately 16 instruction slots used (1 texture, 15 arithmetic)
#endif

const DWORD g_ps20_BrightPass[] =
{
    0xffff0200, 0x0034fffe, 0x42415443, 0x0000001c, 0x00000097, 0xffff0200, 
    0x00000002, 0x0000001c, 0x00000100, 0x00000090, 0x00000044, 0x00000003, 
    0x00000001, 0x00000054, 0x00000000, 0x00000064, 0x00000002, 0x00000001, 
    0x00000070, 0x00000080, 0x61735f67, 0x6372536d, 0x6f6c6f43, 0xabab0072, 
    0x000c0004, 0x00010001, 0x00000001, 0x00000000, 0x696d756c, 0x636e616e, 
    0xabab0065, 0x00030000, 0x00010001, 0x00000001, 0x00000000, 0x3da3d70a, 
    0x00000000, 0x00000000, 0x00000000, 0x325f7370, 0x4d00305f, 0x6f726369, 
    0x74666f73, 0x29522820, 0x44334420, 0x53203958, 0x65646168, 0x6f432072, 
    0x6c69706d, 0x39207265, 0x2e38302e, 0x2e393932, 0x30303030, 0xababab00, 
    0x05000051, 0xa00f0001, 0x3a83126f, 0x3e3851ec, 0x3fc80000, 0x3f800000, 
    0x05000051, 0xa00f0002, 0xc0a00000, 0x80000000, 0x41200000, 0x00000000, 
    0x0200001f, 0x80000000, 0xb0030000, 0x0200001f, 0x90000000, 0xa00f0800, 
    0x03000042, 0x800f0000, 0xb0e40000, 0xa0e40800, 0x02000001, 0x80080000, 
    0xa0000001, 0x03000002, 0x80080000, 0x80ff0000, 0xa0000000, 0x02000006, 
    0x80080000, 0x80ff0000, 0x03000005, 0x80080000, 0x80ff0000, 0xa0550001, 
    0x03000005, 0x80070000, 0x80e40000, 0x80ff0000, 0x04000004, 0x80070001, 
    0x80e40000, 0xa0aa0001, 0xa0ff0001, 0x04000004, 0x80070001, 0x80e40000, 
    0x80e40001, 0xa0000002, 0x0300000b, 0x80070000, 0x80e40001, 0xa0550002, 
    0x03000002, 0x80070001, 0x80e40000, 0xa0aa0002, 0x02000006, 0x80010001, 
    0x80000001, 0x02000006, 0x80020001, 0x80550001, 0x02000006, 0x80040001, 
    0x80aa0001, 0x03000005, 0x80070000, 0x80e40000, 0x80e40001, 0x02000001, 
    0x80080000, 0xa0ff0001, 0x02000001, 0x800f0800, 0x80e40000, 0x0000ffff
};