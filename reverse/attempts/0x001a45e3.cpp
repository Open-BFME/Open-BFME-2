// ?Convert_Shader@W3dUtilityClass@@SAXABVShaderClass@@PAUW3dShaderStruct@@@Z
// partial score=0.85 date=2026-09-10
// cl: /O2 /MD
//
// W3dUtilityClass::Convert_Shader(ShaderClass -> W3dShaderStruct),
// retail 0x001A45E3, 120 bytes. Dedicated TU so w3d_util.cpp keeps
// its matched helpers; Reset is a call, the rest is inlined bit copies.

struct W3dShaderStruct
{
	unsigned char DepthCompare;
	unsigned char DepthMask;
	unsigned char ColorMask;
	unsigned char DestBlend;
	unsigned char FogFunc;
	unsigned char PriGradient;
	unsigned char SecGradient;
	unsigned char SrcBlend;
	unsigned char Texturing;
	unsigned char DetailColorFunc;
	unsigned char DetailAlphaFunc;
	unsigned char Pad0B;
	unsigned char AlphaTest;
	unsigned char PostDetailColorFunc;
	unsigned char PostDetailAlphaFunc;
	unsigned char Pad0F;
};

void W3d_Shader_Reset(W3dShaderStruct *s);

class ShaderClass
{
public:
	unsigned char LowByte() const { return *(const unsigned char *)&ShaderBits; }
	int Get_Depth_Mask() const { return (ShaderBits >> 3) & 1; }
	int Get_Dst_Blend_Func() const { return ShaderBits >> 5; }
	int Get_Primary_Gradient() const { return ShaderBits >> 10; }
	int Get_Secondary_Gradient() const { return (ShaderBits >> 13) & 1; }
	int Get_Src_Blend_Func() const { return (ShaderBits >> 14) & 3; }
	int Get_Texturing() const { return ((unsigned char *)&ShaderBits)[2] & 1; }
	int Get_Alpha_Test() const { return (ShaderBits >> 18) & 3; }
	int Get_Post_Detail_Color_Func() const { return (ShaderBits >> 21) & 15; }
	int Get_Post_Detail_Alpha_Func() const { return ShaderBits >> 25; }

	unsigned ShaderBits;
};

class W3dUtilityClass
{
public:
	static void Convert_Shader(const ShaderClass &shader, W3dShaderStruct *set);
};

void W3dUtilityClass::Convert_Shader(const ShaderClass &shader, W3dShaderStruct *set)
{
	W3d_Shader_Reset(set);
	unsigned char seven = 7;
	set->DepthCompare = shader.LowByte() & seven;
	set->DepthMask = (unsigned char)shader.Get_Depth_Mask();
	set->DestBlend = (unsigned char)shader.Get_Dst_Blend_Func() & seven;
	set->PriGradient = (unsigned char)shader.Get_Primary_Gradient() & seven;
	set->SecGradient = (unsigned char)shader.Get_Secondary_Gradient();
	set->SrcBlend = (unsigned char)shader.Get_Src_Blend_Func();
	set->Texturing = (unsigned char)shader.Get_Texturing();
	set->AlphaTest = (unsigned char)shader.Get_Alpha_Test();
	set->PostDetailColorFunc = (unsigned char)shader.Get_Post_Detail_Color_Func();
	set->PostDetailAlphaFunc = (unsigned char)shader.Get_Post_Detail_Alpha_Func() & seven;
}
