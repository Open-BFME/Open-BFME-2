// cl: /DNDEBUG /MD /GX-
//
// ?Parse_W3dVertexMaterialStruct@VertexMaterialClass@@QAEXABUW3dVertexMaterialStruct@@@Z,
// retail 0x0013D030 (327 bytes).
// BFME1 vertmaterial.cpp Parse_W3dVertexMaterialStruct port with BFME2
// rewrites (all retail-measured from the 0x0013D030 body):
// - Call-free: the Convert_Color plus Set_* chain is fully inline.
//   Each color converts its 3 bytes via cvtsi2ss times the shared
//   1/255 float and stores straight into the D3D material (Diffuse at
//   +0x0, Opacity into Diffuse.a at +0x0C, Ambient at +0x10, Specular at
//   +0x20, Emissive at +0x30, Shininess into Power at +0x40).
// - Every property write first sets the byte flag at this+0x68 (kept in
//   dl across the body).
// - Trailing attribute-bit copy: bit0 and bit2 of vmat Attributes flow
//   into this+0x0C with the same flag set.
// Dedicated TU: vertmaterial.cpp carries the ZH original. No new pins
// (no REL32 calls at all).

#ifndef NULL
#define NULL 0
#endif

typedef unsigned int uint32;
typedef unsigned char uint8;

struct W3dRGBAStruct
{
	uint8 R;
	uint8 G;
	uint8 B;
	uint8 A;
};

struct W3dVertexMaterialStruct
{
	uint32 Attributes;
	W3dRGBAStruct Ambient;
	W3dRGBAStruct Diffuse;
	W3dRGBAStruct Specular;
	W3dRGBAStruct Emissive;
	float Shininess;
	float Opacity;
	float Translucency;
};

struct D3DColorValue
{
	float r;
	float g;
	float b;
	float a;
};

struct D3DMaterial
{
	D3DColorValue Diffuse;
	D3DColorValue Ambient;
	D3DColorValue Specular;
	D3DColorValue Emissive;
	float Power;
};

class VertexMaterialClass
{
public:
	virtual ~VertexMaterialClass();
	void Parse_W3dVertexMaterialStruct(const W3dVertexMaterialStruct &vmat);

	void Set_Diffuse(float r, float g, float b)
	{
		MaterialDirty = true;
		Material->Diffuse.r = r;
		Material->Diffuse.g = g;
		Material->Diffuse.b = b;
	}

	void Set_Opacity(float o)
	{
		MaterialDirty = true;
		Material->Diffuse.a = o;
	}

	void Set_Ambient(float r, float g, float b)
	{
		MaterialDirty = true;
		Material->Ambient.r = r;
		Material->Ambient.g = g;
		Material->Ambient.b = b;
	}

	void Set_Specular(float r, float g, float b)
	{
		MaterialDirty = true;
		Material->Specular.r = r;
		Material->Specular.g = g;
		Material->Specular.b = b;
	}

	void Set_Emissive(float r, float g, float b)
	{
		MaterialDirty = true;
		Material->Emissive.r = r;
		Material->Emissive.g = g;
		Material->Emissive.b = b;
	}

	void Set_Shininess(float s)
	{
		MaterialDirty = true;
		Material->Power = s;
	}

private:
	int RefCount;
	D3DMaterial *Material;
	int Attributes;
	char m_pad[0x68 - 0x10];
	bool MaterialDirty;
};

// The temporaries below force left-to-right evaluation of the three
// channel conversions; passing the expressions straight into the setter
// evaluates them right-to-left and reverses retail's order.
// ?Parse_W3dVertexMaterialStruct@VertexMaterialClass@@QAEXABUW3dVertexMaterialStruct@@@Z
void VertexMaterialClass::Parse_W3dVertexMaterialStruct(const W3dVertexMaterialStruct &vmat)
{
	float ar = (float)vmat.Ambient.R / 255.0f;
	float ag = (float)vmat.Ambient.G / 255.0f;
	float ab = (float)vmat.Ambient.B / 255.0f;
	Set_Ambient(ar, ag, ab);
	float dr = (float)vmat.Diffuse.R / 255.0f;
	float dg = (float)vmat.Diffuse.G / 255.0f;
	float db = (float)vmat.Diffuse.B / 255.0f;
	Set_Diffuse(dr, dg, db);
	float sr = (float)vmat.Specular.R / 255.0f;
	float sg = (float)vmat.Specular.G / 255.0f;
	float sb = (float)vmat.Specular.B / 255.0f;
	Set_Specular(sr, sg, sb);
	float er = (float)vmat.Emissive.R / 255.0f;
	float eg = (float)vmat.Emissive.G / 255.0f;
	float eb = (float)vmat.Emissive.B / 255.0f;
	Set_Emissive(er, eg, eb);
	Set_Shininess(vmat.Shininess);
	Set_Opacity(vmat.Opacity);

	if (vmat.Attributes & 0x1) {
		Attributes |= 0x1;
		MaterialDirty = true;
	}
	if (vmat.Attributes & 0x4) {
		Attributes |= 0x4;
		MaterialDirty = true;
	}
}
