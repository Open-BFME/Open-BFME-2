// cl: /DNDEBUG /MD /GX-
// platformsdk
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

#include <windows.h>

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

// The canonical material pointer owns the same 0x44-byte D3D payload.
class DynD3DMATERIAL8
{
public:
	D3DMaterial Mat;
};

#include "VertexMaterialClass.h"

inline void VertexMaterialClass::Set_Diffuse(float r, float g, float b)
{
	CRCDirty = true;
	MaterialDyn->Mat.Diffuse.r = r;
	MaterialDyn->Mat.Diffuse.g = g;
	MaterialDyn->Mat.Diffuse.b = b;
}

inline void VertexMaterialClass::Set_Opacity(float o)
{
	CRCDirty = true;
	MaterialDyn->Mat.Diffuse.a = o;
}

inline void VertexMaterialClass::Set_Ambient(float r, float g, float b)
{
	CRCDirty = true;
	MaterialDyn->Mat.Ambient.r = r;
	MaterialDyn->Mat.Ambient.g = g;
	MaterialDyn->Mat.Ambient.b = b;
}

inline void VertexMaterialClass::Set_Specular(float r, float g, float b)
{
	CRCDirty = true;
	MaterialDyn->Mat.Specular.r = r;
	MaterialDyn->Mat.Specular.g = g;
	MaterialDyn->Mat.Specular.b = b;
}

inline void VertexMaterialClass::Set_Emissive(float r, float g, float b)
{
	CRCDirty = true;
	MaterialDyn->Mat.Emissive.r = r;
	MaterialDyn->Mat.Emissive.g = g;
	MaterialDyn->Mat.Emissive.b = b;
}

inline void VertexMaterialClass::Set_Shininess(float s)
{
	CRCDirty = true;
	MaterialDyn->Mat.Power = s;
}

// The temporaries below force left-to-right evaluation of the three
// channel conversions; passing the expressions straight into the setter
// evaluates them right-to-left and reverses retail's order.
// ?Parse_W3dVertexMaterialStruct@VertexMaterialClass@@QAEXABUW3dVertexMaterialStruct@@@Z
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void VertexMaterialClass::Parse_W3dVertexMaterialStruct(const W3dVertexMaterialStruct &vmat)
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
		Flags |= 0x1;
		CRCDirty = true;
	}
	if (vmat.Attributes & 0x4) {
		Flags |= 0x4;
		CRCDirty = true;
	}
}

// ?bfmeAnchorVertexMaterialClassParse_W3dVertexMaterialStruct absent-from-retail
void bfmeAnchorVertexMaterialClassParse_W3dVertexMaterialStruct(VertexMaterialClass *vertexMaterial, const W3dVertexMaterialStruct &vmat)
{
	vertexMaterial->Parse_W3dVertexMaterialStruct(vmat);
}
