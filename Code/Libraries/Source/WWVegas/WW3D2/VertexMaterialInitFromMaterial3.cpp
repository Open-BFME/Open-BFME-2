// cl: /DNDEBUG /MD /GX-
//
// ?Init_From_Material3@VertexMaterialClass@@QAEXABUW3dMaterial3Struct@@@Z,
// retail 0x0013CEA0 (398 bytes).
// BFME1 vertmaterial.cpp Init_From_Material3 port with BFME2 rewrites (all
// retail-measured from the 0x0013CEA0 body):
// - Call-free: the Convert_Color plus Set_* chain is fully inline.
//   Diffuse and Specular convert their color and coefficient bytes via
//   cvtsi2ss times the shared 1/255 float and store the pairwise products
//   (Diffuse at +0x0, Specular at +0x20). Emissive and Ambient convert
//   only their coefficient bytes (Emissive at +0x30, Ambient at +0x10).
//   Shininess and Opacity copy straight through (Power at +0x40,
//   Opacity into Diffuse.a at +0x0C).
// - Every property write first sets the byte flag at this+0x68 (kept in
//   dl across the body).
// Dedicated TU: vertmaterial.cpp carries the ZH original. No new pins
// (no REL32 calls at all).

#ifndef NULL
#define NULL 0
#endif

typedef unsigned int uint32;
typedef unsigned char uint8;

struct W3dRGBStruct
{
	uint8 R;
	uint8 G;
	uint8 B;
	uint8 Pad;
};

struct W3dMaterial3Struct
{
	uint32 Attributes;
	W3dRGBStruct DiffuseColor;
	W3dRGBStruct SpecularColor;
	W3dRGBStruct EmissiveCoefficients;
	W3dRGBStruct AmbientCoefficients;
	W3dRGBStruct DiffuseCoefficients;
	W3dRGBStruct SpecularCoefficients;
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
	void Init_From_Material3(const W3dMaterial3Struct &mat3);

	void Set_Diffuse(float r, float g, float b)
	{
		MaterialDirty = true;
		Material->Diffuse.r = r;
		Material->Diffuse.g = g;
		Material->Diffuse.b = b;
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

	void Set_Ambient(float r, float g, float b)
	{
		MaterialDirty = true;
		Material->Ambient.r = r;
		Material->Ambient.g = g;
		Material->Ambient.b = b;
	}

	void Set_Shininess(float s)
	{
		MaterialDirty = true;
		Material->Power = s;
	}

	void Set_Opacity(float o)
	{
		MaterialDirty = true;
		Material->Diffuse.a = o;
	}

private:
	int RefCount;
	D3DMaterial *Material;
	int Attributes;
	char m_pad[0x68 - 0x10];
	bool MaterialDirty;
};

// The temporaries below force left-to-right evaluation of the channel
// conversions; passing the expressions straight into the setter evaluates
// them right-to-left and reverses retail's order.
// ?Init_From_Material3@VertexMaterialClass@@QAEXABUW3dMaterial3Struct@@@Z
void VertexMaterialClass::Init_From_Material3(const W3dMaterial3Struct &mat3)
{
	float dr = (float)mat3.DiffuseColor.R / 255.0f;
	float dg = (float)mat3.DiffuseColor.G / 255.0f;
	float db = (float)mat3.DiffuseColor.B / 255.0f;
	float dcr = (float)mat3.DiffuseCoefficients.R / 255.0f;
	float dcg = (float)mat3.DiffuseCoefficients.G / 255.0f;
	float dcb = (float)mat3.DiffuseCoefficients.B / 255.0f;
	Set_Diffuse(dr * dcr, dg * dcg, db * dcb);
	float sr = (float)mat3.SpecularColor.R / 255.0f;
	float sg = (float)mat3.SpecularColor.G / 255.0f;
	float sb = (float)mat3.SpecularColor.B / 255.0f;
	float scr = (float)mat3.SpecularCoefficients.R / 255.0f;
	float scg = (float)mat3.SpecularCoefficients.G / 255.0f;
	float scb = (float)mat3.SpecularCoefficients.B / 255.0f;
	Set_Specular(sr * scr, sg * scg, sb * scb);
	float er = (float)mat3.EmissiveCoefficients.R / 255.0f;
	float eg = (float)mat3.EmissiveCoefficients.G / 255.0f;
	float eb = (float)mat3.EmissiveCoefficients.B / 255.0f;
	Set_Emissive(er, eg, eb);
	float ar = (float)mat3.AmbientCoefficients.R / 255.0f;
	float ag = (float)mat3.AmbientCoefficients.G / 255.0f;
	float ab = (float)mat3.AmbientCoefficients.B / 255.0f;
	Set_Ambient(ar, ag, ab);
	Set_Shininess(mat3.Shininess);
	Set_Opacity(mat3.Opacity);
}
