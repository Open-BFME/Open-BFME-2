// cl: /O1 /MD
//
// W3d_Shader_Reset, retail 0x001A441F, 58 bytes.

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

void W3d_Shader_Reset(W3dShaderStruct *s)
{
	unsigned char *p = (unsigned char *)s;
	p[0] = 3;
	p[1] = 1;
	p[2] = 0;
	p[3] = 0;
	p[4] = 0;
	p[5] = 1;
	p[6] = 0;
	p[7] = 1;
	p[8] = 0;
	p[9] = 0;
	p[10] = 0;
	p[11] = 0;
	p[12] = 0;
	p[13] = 0;
	p[14] = 0;
	p[15] = 0;
}
