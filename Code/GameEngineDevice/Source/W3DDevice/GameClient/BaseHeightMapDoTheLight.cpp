// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?doTheLight@BaseHeightMapRenderObjClass@@QAEXPAUVertexFormatXYZDUV2@@PAVVector3@@1PAV?$RefMultiListIterator@VRenderObjClass@@@@E_N@Z,
// retail 0x000694A3..0x00069AF5 (1618B), thiscall ret 0x18.
//
// Zero Hour's BaseHeightMapRenderObjClass::doTheLight in its BFME 2 form: the
// terrain vertex colour is the first terrain ambient plus every scene light
// (point/spot with far attenuation, directional along the light's Z axis)
// plus the global terrain lights, clamped, faded under water, packed with the
// alpha into the vertex diffuse. BFME 2 adds a trailing flag that skips global
// light 0 when GlobalData +0x49 (UseTerrainNormalMap) is set, scales the
// global light colours by GlobalData +0x944 when the terrain rendering mode
// (vtable slot 147) is below 1, and dims them by one minus the cloud
// manager's slot-18 colour while its slot 15 reports it active.
//
// Evidence (target): WorldBuilder twin 0x752620 (vector3.h asserts) has the
// same statements; the only callers pass (vertex, light rays, normal,
// iterator, 1, flag), e.g. getStaticDiffuse 0x0006B4CC. Retail calls the
// matched RenderObjClass::Get_Position 0x0013B8A0, LightClass::Get_Diffuse
// 0x0006922E / Get_Ambient 0x0006920D and WWMath::Inv_Sqrt 0x0004233A.
// Semantic donor: BFME 1 game/.../BaseHeightMap.cpp doTheLight (ZH port).
// Field names follow the donor; the +0x944 scale's name is not recovered.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;

class WWMath
{
public:
	static __forceinline Real Sqrt(Real val)
	{
		Real retval;
		__asm {
			fld [val]
			fsqrt
			fstp [retval]
		}
		return retval;
	}
	static Real __fastcall Inv_Sqrt(Real lhs);
	static __declspec(dllimport) __forceinline Real Clamp(Real val, Real lo, Real hi)
	{
		if (val < lo) return lo;
		if (val > hi) return hi;
		return val;
	}
};

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;

	__forceinline Vector3() {}
	__forceinline Vector3(const Vector3 &vec) { X = vec.X; Y = vec.Y; Z = vec.Z; }
	__forceinline Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	__forceinline Vector3 &operator=(const Vector3 &vec) { X = vec.X; Y = vec.Y; Z = vec.Z; return *this; }
	__forceinline Vector3 &operator-=(const Vector3 &vec) { X -= vec.X; Y -= vec.Y; Z -= vec.Z; return *this; }

	__forceinline Real Length2() const { return X * X + Y * Y + Z * Z; }
	__forceinline Real Length() const { return WWMath::Sqrt(Length2()); }
	__forceinline void Normalize()
	{
		Real len2 = Length2();
		if (len2 != 0.0f)
		{
			Real oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
	static __forceinline Real Dot_Product(const Vector3 &lhs, const Vector3 &rhs)
	{
		return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
	}
};

class Matrix3D
{
public:
	__declspec(dllimport) __forceinline Vector3 Get_Z_Vector() const { return Vector3(Row[0][2], Row[1][2], Row[2][2]); }
	Real Row[3][4];
};

#include "../../../../Libraries/Include/Lib/RGBColor.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/VertexFormatXYZDUV2.h"
typedef VertexFormatXYZDUV2 VERTEX_FORMAT;

// The render object's first 8 bytes (vptr, reference count) precede its
// multi-list link, so a list object converts back by -8 (target fact).
class RenderObjRefCountView
{
public:
	virtual void Delete_This();
	Int NumRefs;
};

#include "../../../../Libraries/Source/WWVegas/WWLib/MultiListObjectClass.h"

class RenderObjClass : public RenderObjRefCountView, public MultiListObjectClass
{
public:
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
	virtual void v17(); virtual void v18(); virtual void v19();
	virtual void Validate_Transform() const;	// slot 20
	__forceinline const Matrix3D &Get_Transform() const { Validate_Transform(); return Transform; }
	Vector3 Get_Position() const;
	char m_pad10[0x18 - 0x10];
	Matrix3D Transform;			// +0x18
};

class LightClass : public RenderObjClass
{
public:
	enum LightType { POINT = 0, DIRECTIONAL, SPOT };
	__forceinline LightType Get_Type() const { return Type; }
	__forceinline void Get_Far_Attenuation_Range(double &fstart, double &fend) const { fstart = FarAttenStart; fend = FarAttenEnd; }
	void Get_Ambient(Vector3 *set) const;
	void Get_Diffuse(Vector3 *set) const;
	char m_pad48[0xC4 - 0x48];
	LightType Type;				// +0xC4
	char m_padC8[0x100 - 0xC8];
	Real FarAttenStart;			// +0x100
	Real FarAttenEnd;			// +0x104
};

class MultiListNodeClass
{
public:
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();
	MultiListNodeClass Head;
};

class GenericMultiListIterator
{
public:
	__declspec(dllimport) __forceinline void First() { CurNode = List->Head.Next; }
	__declspec(dllimport) __forceinline void Next() { CurNode = CurNode->Next; }
	__forceinline Bool Is_Done() { return CurNode == &(List->Head); }

protected:
	__forceinline MultiListObjectClass *Generic_Peek_Obj() { return CurNode->Object; }

	GenericMultiListClass *List;
	MultiListNodeClass *CurNode;
};

// Peek_Obj goes through Generic_Peek_Obj as in WW3D; the separate inline is
// what gives retail's branch-free null-checked -8 conversion.
template <class ObjectType> class RefMultiListIterator : public GenericMultiListIterator
{
public:
	__declspec(dllimport) __forceinline ObjectType *Peek_Obj() { return static_cast<ObjectType *>(Generic_Peek_Obj()); }
};
typedef RefMultiListIterator<RenderObjClass> RefRenderObjListIterator;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct TerrainLightingGlobals
{
	char m_pad000[0x49];
	Bool m_useTerrainNormalMap;		// +0x49
	char m_pad04A[0x74 - 0x4A];
	Real m_waterPositionZ;			// +0x74
	char m_pad078[0x8D8 - 0x78];
	RGBColor m_terrainAmbient[3];		// +0x8D8
	RGBColor m_terrainDiffuse[3];		// +0x8FC
	Vector3 m_terrainLightPos[3];		// +0x920
	RGBColor m_terrainLightScale;		// +0x944
	char m_pad950[0x988 - 0x950];
	Int m_numGlobalLights;			// +0x988
};
#define TheGlobalLighting ((TerrainLightingGlobals *)TheWritableGlobalData)

// The cloud-effect manager: slot 15 reports it active, slot 18 returns the
// colour it takes away from the global terrain lights.
class Rva0027070CGlobal;
extern Rva0027070CGlobal *TheCloudEffectManager;

class CloudDimmingView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual Bool isActive();			// slot 15
	virtual void s16(); virtual void s17();
	virtual Vector3 getDimming();			// slot 18
};
#define TheCloudDimming ((CloudDimmingView *)TheCloudEffectManager)

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class BaseHeightMapRenderObjClass
{
public:
	PAD_VIRTUALS10(v0) PAD_VIRTUALS10(v1) PAD_VIRTUALS10(v2) PAD_VIRTUALS10(v3) PAD_VIRTUALS10(v4)
	PAD_VIRTUALS10(v5) PAD_VIRTUALS10(v6) PAD_VIRTUALS10(v7) PAD_VIRTUALS10(v8) PAD_VIRTUALS10(v9)
	PAD_VIRTUALS10(w0) PAD_VIRTUALS10(w1) PAD_VIRTUALS10(w2) PAD_VIRTUALS10(w3)
	virtual void s140(); virtual void s141(); virtual void s142(); virtual void s143(); virtual void s144();
	virtual void s145(); virtual void s146();
	virtual Int getRenderingMode();			// slot 147

	void doTheLight(VERTEX_FORMAT *vb, Vector3 *light, Vector3 *normal, RefRenderObjListIterator *pLightsIterator, UnsignedByte alpha, Bool skipFirstLight);

private:
	char m_pad0004[0x37C4 - 4];
	Bool m_useDepthFade;			// +0x37C4
	Vector3 m_depthFade;			// +0x37C8
};

void BaseHeightMapRenderObjClass::doTheLight(VERTEX_FORMAT *vb, Vector3 *light, Vector3 *normal, RefRenderObjListIterator *pLightsIterator, UnsignedByte alpha, Bool skipFirstLight)
{
	Real shadeR, shadeG, shadeB;
	Real shade;
	shadeR = TheGlobalLighting->m_terrainAmbient[0].red;	// only the first terrain light contributes to ambient
	shadeG = TheGlobalLighting->m_terrainAmbient[0].green;
	shadeB = TheGlobalLighting->m_terrainAmbient[0].blue;

	if (pLightsIterator) {
		for (pLightsIterator->First(); !pLightsIterator->Is_Done(); pLightsIterator->Next())
		{
			LightClass *pLight = (LightClass *)pLightsIterator->Peek_Obj();
			Vector3 lightDirection(vb->x, vb->y, vb->z);
			Real factor = 1.0f;
			switch (pLight->Get_Type()) {
			case LightClass::POINT:
			case LightClass::SPOT: {
					Vector3 lightLoc = pLight->Get_Position();
					lightDirection -= lightLoc;
					double range, midRange;
					pLight->Get_Far_Attenuation_Range(midRange, range);
					if (vb->x < lightLoc.X - range) continue;
					if (vb->x > lightLoc.X + range) continue;
					if (vb->y < lightLoc.Y - range) continue;
					if (vb->y > lightLoc.Y + range) continue;
					Real dist = lightDirection.Length();
					if (dist >= range) continue;
					if (midRange < 0.1) continue;
					factor = 1.0f - (dist - midRange) / (range - midRange);
					factor = WWMath::Clamp(factor, 0.0f, 1.0f);
				}
				break;
			case LightClass::DIRECTIONAL:
				lightDirection = pLight->Get_Transform().Get_Z_Vector();
				factor = 1.0;
				break;
			};
			lightDirection.Normalize();
			Vector3 lightRay(-lightDirection.X, -lightDirection.Y, -lightDirection.Z);
			shade = Vector3::Dot_Product(lightRay, *normal);
			shade *= factor;
			Vector3 diffuse;
			pLight->Get_Diffuse(&diffuse);
			Vector3 ambient;
			pLight->Get_Ambient(&ambient);
			if (shade > 1.0) shade = 1.0;
			if (shade < 0.0f) shade = 0.0f;
			shadeR += shade * diffuse.X;
			shadeG += shade * diffuse.Y;
			shadeB += shade * diffuse.Z;
			shadeR += factor * ambient.X;
			shadeG += factor * ambient.Y;
			shadeB += factor * ambient.Z;
		}
	}

	// Add in global diffuse value; with the normal-mapped terrain shader the
	// first (sun) light is lit per pixel instead.
	Int lightIndex = 0;
	if (skipFirstLight && TheGlobalLighting->m_useTerrainNormalMap)
		lightIndex = 1;
	for (; lightIndex < TheGlobalLighting->m_numGlobalLights; lightIndex++)
	{
		shade = light[lightIndex].X * normal->X + light[lightIndex].Z * normal->Z + light[lightIndex].Y * normal->Y;
		if (shade > 1.0) shade = 1.0;
		if (shade < 0.0f) shade = 0.0f;
		RGBColor terrainDiffuse = TheGlobalLighting->m_terrainDiffuse[lightIndex];
		if (getRenderingMode() < 1) {
			terrainDiffuse.red *= TheGlobalLighting->m_terrainLightScale.red;
			terrainDiffuse.green *= TheGlobalLighting->m_terrainLightScale.green;
			terrainDiffuse.blue *= TheGlobalLighting->m_terrainLightScale.blue;
		}
		if (TheCloudDimming && TheCloudDimming->isActive()) {
			terrainDiffuse.red *= 1.0f - TheCloudDimming->getDimming().X;
			terrainDiffuse.green *= 1.0f - TheCloudDimming->getDimming().Y;
			terrainDiffuse.blue *= 1.0f - TheCloudDimming->getDimming().Z;
		}
		shadeR += shade * terrainDiffuse.red;
		shadeG += shade * terrainDiffuse.green;
		shadeB += shade * terrainDiffuse.blue;
	}

	if (shadeR > 1.0) shadeR = 1.0;
	if (shadeR < 0.0f) shadeR = 0.0f;
	if (shadeG > 1.0) shadeG = 1.0;
	if (shadeG < 0.0f) shadeG = 0.0f;
	if (shadeB > 1.0) shadeB = 1.0;
	if (shadeB < 0.0f) shadeB = 0.0f;

	if (m_useDepthFade && vb->z <= TheGlobalLighting->m_waterPositionZ)
	{	// height is below water level
		// reduce lighting values based on light fall off as it travels through water.
		float depthScale = (1.4f - vb->z) / TheGlobalLighting->m_waterPositionZ;
		shadeR *= 1.0f - depthScale * (1.0f - m_depthFade.X);
		shadeG *= 1.0f - depthScale * (1.0f - m_depthFade.Y);
		shadeB *= 1.0f - depthScale * (1.0f - m_depthFade.Z);
	}

	shadeR *= 255.0f;
	shadeG *= 255.0f;
	shadeB *= 255.0f;
	vb->diffuse = (((((Int)alpha << 8) | (Int)shadeR) << 8 | (Int)shadeG) << 8) | (Int)shadeB;
}
