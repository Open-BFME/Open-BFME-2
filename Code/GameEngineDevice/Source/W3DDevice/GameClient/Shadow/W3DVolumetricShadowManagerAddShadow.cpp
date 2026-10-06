// cl: /DNDEBUG /MD /EHsc
// ?addShadow@W3DVolumetricShadowManager@@QAEPAVW3DVolumetricShadow@@PAVRenderObjClass@@PAUShadowTypeInfo@Shadow@@PAVDrawable@@@Z @0x000F2BB9 323B.
// W3DVolumetricShadowManager::addShadow(RenderObjClass *robj,
// Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw): stencil + robj +
// shadow-volumes-enabled gate, Get_Geom cache lookup (Load_Geom on miss),
// NEW W3DVolumetricShadow, setRenderObject + SetGeometry, bounding-sphere
// extent, tan(sun-elevation) length scale, extrusion padding unless the draw
// is KINDOF_IMMOBILE, then push onto m_shadowList. Donor identity:
// Open-BFME-1 game/.../Shadow/W3DVolumetricShadow.cpp
// W3DVolumetricShadowManager::addShadow (same class, name, signature,
// behavior, +0/+8 manager view, 0x4904 shadow size). Target divergences from
// the donor: no redundant second !robj check, extent stored without the
// MAX_SHADOW_LENGTH_SCALE_FACTOR multiply, single-mul PI/180 degree factor,
// ShadowTypeInfo is smaller (m_sizeX at +0x1C), and the KINDOF test is an
// inline bit check (no isKindOf call in retail).

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

struct SphereClass
{
	Vector3 Center;
	float Radius;
};

class RenderObjClass
{
public:
	virtual void roPad00();
	virtual void roPad01();
	virtual void roPad02();
	virtual void roPad03();
	virtual void roPad04();
	virtual void roPad05();
	virtual const char *Get_Name() const;
	virtual void roPad07();
	virtual void roPad08();
	virtual void roPad09();
	virtual void roPad10();
	virtual void roPad11();
	virtual void roPad12();
	virtual void roPad13();
	virtual void roPad14();
	virtual void roPad15();
	virtual void roPad16();
	virtual void roPad17();
	virtual void roPad18();
	virtual void roPad19();
	virtual void roPad20();
	virtual void roPad21();
	virtual void roPad22();
	virtual void roPad23();
	virtual void roPad24();
	virtual void roPad25();
	virtual void roPad26();
	virtual void roPad27();
	virtual void roPad28();
	virtual void roPad29();
	virtual void roPad30();
	virtual void roPad31();
	virtual void roPad32();
	virtual void roPad33();
	virtual void roPad34();
	virtual void roPad35();
	virtual void roPad36();
	virtual void roPad37();
	virtual void roPad38();
	virtual void roPad39();
	virtual void roPad40();
	virtual void roPad41();
	virtual void roPad42();
	virtual void roPad43();
	virtual void roPad44();
	virtual void roPad45();
	virtual void roPad46();
	virtual void roPad47();
	virtual void roPad48();
	virtual void roPad49();
	virtual void roPad50();
	virtual void roPad51();
	virtual void roPad52();
	virtual void roPad53();
	virtual void roPad54();
	virtual void roPad55();
	virtual void roPad56();
	virtual void roPad57();
	virtual void roPad58();
	virtual void roPad59();
	virtual void roPad60();
	virtual void roPad61();
	virtual void roPad62();
	virtual void roPad63();
	virtual void roPad64();
	virtual void roPad65();
	virtual void roPad66();
	virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const;
};

class Shadow
{
public:
	struct ShadowTypeInfo
	{
		char m_pad00[8];
		void *m_unk08; // +0x08, unidentified; stored to shadow+0x34 by addShadow
		char m_pad0C[0x1C - 0x0C];
		float m_sizeX; // +0x1C
	};
};

// draw+4 points at a kind-flags block whose byte at +0x108 carries the
// KINDOF bitmask (bit 2 == KINDOF_IMMOBILE, matching KindOf enum order).
// Only this access pattern is verified; the field identities are unclaimed.
struct DrawableKindBits
{
	char m_pad00[0x108];
	unsigned char m_bits; // +0x108, bit 2 (0x04) == KINDOF_IMMOBILE
};

class Drawable
{
public:
	bool isImmobileKind() const
	{
		const DrawableKindBits *bits = *(const DrawableKindBits *const *)((const char *)this + 4);
		return (bits->m_bits & 4) != 0;
	}

private:
	void *m_vtable; // +0x00
	void *m_ref04; // +0x04, points at the kind-flags block
};

class HAnimClass;
class HAnimManagerClass
{
public:
	HAnimClass *Get_Anim(const char *name);
};

class W3DShadowGeometry;
class W3DShadowGeometryManager
{
public:
	int Load_Geom(RenderObjClass *robj, const char *name);
};

class W3DVolumetricShadowManager;

class W3DVolumetricShadow
{
public:
	W3DVolumetricShadow(void);
	void setRenderObject(RenderObjClass *robj) { m_robj = robj; }
	void setRenderObjExtent(float extent) { m_renderObjExtent = extent; }
	void setShadowLengthScale(float scale) { m_shadowLengthScale = scale; }
	void setOptimalExtrusionPadding(float pad) { m_optimalExtrusionPadding = pad; }

protected:
	void SetGeometry(W3DShadowGeometry *geometry);
	friend class W3DVolumetricShadowManager;

private:
	void *m_vtable; // +0x00
	char m_pad04[0x34 - 4];
	void *m_unk34; // +0x34, unidentified; filled from shadowInfo+0x08 by addShadow
	char m_pad38[0x68 - 0x38];
	W3DVolumetricShadow *m_next; // +0x68
	void *m_pad6C; // +0x6C, unidentified (only +0x68/+0x70 access-verified)
	RenderObjClass *m_robj; // +0x70
	float m_shadowLengthScale; // +0x74
	float m_renderObjExtent; // +0x78
	float m_optimalExtrusionPadding; // +0x7C
	char m_pad80[0x4904 - 0x80];
};

class W3DVolumetricShadowManager
{
public:
	W3DVolumetricShadow *addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);

private:
	W3DVolumetricShadow *m_shadowList; // +0x00
	void *m_pad04; // +0x04, unidentified (only +0x00/+0x08 access-verified)
	W3DShadowGeometryManager *m_W3DShadowGeometryManager; // +0x08
};

class DX8Wrapper
{
public:
	static bool Has_Stencil();
};

class GlobalData
{
public:
	char m_pad00[0x60];
	unsigned char m_useShadowVolumes; // +0x60
};
extern GlobalData *TheWritableGlobalData; // 0x00DFE758
#define TheGlobalData TheWritableGlobalData

#include <math.h>

#ifndef NULL
#define NULL 0
#endif

#define SHADOW_EXTRUSION_BUFFER 0.1f
#define DEG_TO_RAD (3.14159265358979323846f / 180.0f)

W3DVolumetricShadow *W3DVolumetricShadowManager::addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw)
{
	if (!DX8Wrapper::Has_Stencil() || !robj || !TheGlobalData->m_useShadowVolumes)
		return NULL;

	W3DShadowGeometry *sg = NULL;

	const char *name = robj->Get_Name();
	if (!name)
		return NULL;

	// Ledger names the 19B Find+AddRef body at 0x000F0B98
	// HAnimManagerClass::Get_Anim; the same bytes serve the geometry cache
	// lookup here, so call through the ledger name (cast: address is the proof).
	sg = (W3DShadowGeometry *)((HAnimManagerClass *)m_W3DShadowGeometryManager)->Get_Anim(name);
	if (sg == NULL) {
		m_W3DShadowGeometryManager->Load_Geom(robj, name);
		sg = (W3DShadowGeometry *)((HAnimManagerClass *)m_W3DShadowGeometryManager)->Get_Anim(name);
		if (sg == NULL)
			return NULL;
	}

	W3DVolumetricShadow *shadow = new W3DVolumetricShadow;
	if (shadow == NULL)
		return NULL;

	shadow->setRenderObject(robj);
	shadow->SetGeometry(sg);

	SphereClass sphere;
	robj->Get_Obj_Space_Bounding_Sphere(sphere);
	shadow->setRenderObjExtent(sphere.Radius);

	float sunElevationAngleTan = 0;
	if (shadowInfo->m_sizeX != 0.0f) {
		sunElevationAngleTan = (float)tan(shadowInfo->m_sizeX * DEG_TO_RAD);
	}
	shadow->setShadowLengthScale(sunElevationAngleTan);
	shadow->m_unk34 = shadowInfo->m_unk08;

	if (!draw || !draw->isImmobileKind())
		shadow->setOptimalExtrusionPadding(SHADOW_EXTRUSION_BUFFER);

	shadow->m_next = m_shadowList;
	m_shadowList = shadow;
	return shadow;
}
