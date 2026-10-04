// ?setTerrainDecal@W3DModelDraw@@UAEXW4TerrainDecalType@@@Z
// partial score=0.7 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
//
// W3DModelDraw::setTerrainDecalSize (retail 0x000B314B, 32 bytes) and
// W3DModelDraw::setTerrainDecalOpacity (0x000B316B, 34 bytes), ported from
// Zero Hour's GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
// W3DModelDraw.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference).
// Identity: slots 21 and 22 of the W3DModelDraw-family vtable 0x00BCBFC0
// (installed at 0x000CACA8 and by the destructor 0x000CAEC6; slot-2 name
// getter returns "W3DSupplyDraw"; slot 35 is the rowed W3DModelDraw::setFullyObscuredByShroud).
// Zero Hour's DrawModule declares setTerrainDecal, setTerrainDecalSize and
// setTerrainDecalOpacity in that order, and both bodies are Zero Hour's
// shape: a null test of the terrain decal and setSize(x, y), resp. the rowed
// Shadow::setOpacity with (Int)(255 * o).
// BFME 2 differences (target evidence): Shadow::setSize only stores the two
// sizes (Shadow +0x58/+0x5C; Zero Hour also caches their reciprocals), and
// the decal sits at W3DModelDraw +0x5C. Retail is size-optimised here: the
// opacity setter pushes its argument and calls instead of reusing the
// argument slot for a tail call, which /O2 (W3DModelDraw.cpp's flags) does.
// W3DModelDraw::setTerrainDecal, retail 0x000B9CE8 (241 bytes), slot 20 (the
// one before setTerrainDecalSize, as in Zero Hour's DrawModule): Zero Hour's
// body with BFME 2's decal info: a 0x28-byte Shadow::ShadowTypeInfo with an
// AsciiString name (+0x00), m_type +0x08 (SHADOW_ALPHA_DECAL 0x20), the
// template's shadow size and offset (+0x0C..+0x18, from template
// +0x4E8..+0x4F4), allowUpdates +0x25 and allowWorldAlign +0x26; its
// constructor and destructor are the rowed 0x00079514/0x000793FA (rowed as
// AudioEventRTS's; pinned under the ShadowTypeInfo names). Only
// TERRAIN_DECAL_MAX (7) is rejected; the name always comes from
// TerrainDecalTextureName (pinned data 0x009B4E8C). TheProjectedShadowManager
// is the rowed global g_00DEC2D4 (an alias here), addDecal its vslot 3 with
// two extra zero arguments; the decal's render flag follows m_shadowEnabled
// unless the +0x4B flag is set (as in setShadowsEnabled).

typedef float Real;
typedef int Int;
typedef bool Bool;
#define TRUE true
#define FALSE false
#include "ascii_string.h"

enum TerrainDecalType
{
	TERRAIN_DECAL_DEMORALIZED = 0,
	TERRAIN_DECAL_MAX = 7
};
enum ShadowType
{
	SHADOW_ALPHA_DECAL = 0x20
};
extern const char *TerrainDecalTextureName[TERRAIN_DECAL_MAX];
class RenderObjClass;
class Shadow
{
public:
	struct ShadowTypeInfo
	{
		ShadowTypeInfo();
		~ShadowTypeInfo();
		AsciiString m_ShadowName; // +0x00
		AsciiString m_bfme04; // +0x04
		ShadowType m_type; // +0x08
		Real m_sizeX; // +0x0C
		Real m_sizeY; // +0x10
		Real m_offsetX; // +0x14
		Real m_offsetY; // +0x18
		Real m_bfme1C; // +0x1C
		Real m_bfme20; // +0x20
		Bool m_bfme24; // +0x24
		Bool allowUpdates; // +0x25
		Bool allowWorldAlign; // +0x26
	};
	virtual void slot00();
	virtual void slot01();
	virtual void release(void);
	void enableShadowRender(Bool isEnabled) { m_isEnabled = isEnabled; }
	void enableShadowInvisible(Bool isEnabled) { m_isInvisibleEnabled = isEnabled; }
	void setOpacity(Int value);
	void setSize(Real sizeX, Real sizeY)
	{
		m_decalSizeX = sizeX;
		m_decalSizeY = sizeY;
	}
private:
	Bool m_isEnabled; // +0x04
	Bool m_isInvisibleEnabled; // +0x05
	unsigned char m_pad06[0x58 - 0x06];
	Real m_decalSizeX; // +0x58
	Real m_decalSizeY; // +0x5C
};
class ProjectedShadowManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual Shadow *addDecal(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, int bfme2, int bfme3) = 0;
};
extern ProjectedShadowManager *TheProjectedShadowManager;
#pragma comment(linker, "/alternatename:?TheProjectedShadowManager@@3PAVProjectedShadowManager@@A=?g_00DEC2D4@@3PAVAudioManager0029E159@@A")
class ThingTemplate
{
public:
	Real getShadowSizeX() const { return m_shadowSizeX; }
	Real getShadowSizeY() const { return m_shadowSizeY; }
	Real getShadowOffsetX() const { return m_shadowOffsetX; }
	Real getShadowOffsetY() const { return m_shadowOffsetY; }
private:
	unsigned char m_pad00[0x4E8];
	Real m_shadowSizeX; // +0x4E8
	Real m_shadowSizeY; // +0x4EC
	Real m_shadowOffsetX; // +0x4F0
	Real m_shadowOffsetY; // +0x4F4
};
class Drawable
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
};

class W3DModelDraw
{
public:
	virtual void setTerrainDecal(TerrainDecalType type);
	virtual void setTerrainDecalSize(Real x, Real y);
	virtual void setTerrainDecalOpacity(Real o);
	Drawable *getDrawable() const { return m_drawable; }
private:
	unsigned char m_pad04[0x08 - 0x04];
	Drawable *m_drawable; // +0x08
	unsigned char m_pad0C[0x49 - 0x0C];
	Bool m_fullyObscuredByShroud; // +0x49
	Bool m_shadowEnabled; // +0x4A
	Bool m_bfme4B; // +0x4B
	unsigned char m_pad4C[0x50 - 0x4C];
	RenderObjClass *m_renderObject; // +0x50
	unsigned char m_pad54[0x5C - 0x54];
	Shadow *m_terrainDecal; // +0x5C
};

//-------------------------------------------------------------------------------------------------
void W3DModelDraw::setTerrainDecalSize(Real x, Real y)
{
	if (m_terrainDecal)
	{
		m_terrainDecal->setSize(x,y);
	}
}
//-------------------------------------------------------------------------------------------------
void W3DModelDraw::setTerrainDecalOpacity(Real o)
{
	if (m_terrainDecal)
	{
		m_terrainDecal->setOpacity((Int)(255.0f * o));
	}
}

//-------------------------------------------------------------------------------------------------
void W3DModelDraw::setTerrainDecal(TerrainDecalType type)
{
	if (m_terrainDecal)
		m_terrainDecal->release();

	m_terrainDecal = NULL;

	if (type >= TERRAIN_DECAL_MAX)
		//turning off decals on this object. (or bad value.)
		return;

	const ThingTemplate *tmplate=getDrawable()->getTemplate();

	//create a new terrain decal
	Shadow::ShadowTypeInfo decalInfo;
	decalInfo.allowUpdates = FALSE;	//shadow image will never update
	decalInfo.allowWorldAlign = TRUE;	//shadow image will wrap around world objects
	decalInfo.m_type = SHADOW_ALPHA_DECAL;

	decalInfo.m_ShadowName = TerrainDecalTextureName[type];
	decalInfo.m_sizeX = tmplate->getShadowSizeX();
	decalInfo.m_sizeY = tmplate->getShadowSizeY();
	decalInfo.m_offsetX = tmplate->getShadowOffsetX();
	decalInfo.m_offsetY = tmplate->getShadowOffsetY();
	if (TheProjectedShadowManager)
		m_terrainDecal = TheProjectedShadowManager->addDecal(m_renderObject,&decalInfo,0,0);
	if (m_terrainDecal)
	{	m_terrainDecal->enableShadowInvisible(m_fullyObscuredByShroud);
		m_terrainDecal->enableShadowRender(m_shadowEnabled && !m_bfme4B);
	}
}
