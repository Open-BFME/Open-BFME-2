// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?rva0028449F@TerrainLogic@@QAEXPBUCoord3D@@ABVGeometryInfo@@M@Z retail
// 0x0028449F..0x0028458F (240 bytes) RET 0xC. Called from DozerAIUpdate
// 0x0048A15A. Builds a local cylinder GeometryInfo (rowed ctor 0x00050B74:
// height 35 and radii 14) then walks the record pointers at +0x578/+0x57C
// (same range as the rowed TerrainLogic::rva00283CE7). Every record with a
// key at +0xC whose position the argument shape overlaps (rowed
// GeometryInfo::CollidesWith 0x006BEB80 against the local shape at the
// record with angle 0) is reported to TheTriggerManager (rowed 0x0028641F)
// then reset (rowed 0x0027D098) and its key passed to TheTerrainVisual slot +0x58
// while +0x1910 takes TheGameLogic's frame. Finally TheTerrainVisual slot +0x48
// gets the position shape and angle. The local shape dies through the rowed
// GeometryInfo destructor 0x00050B2A. WB twin 0x00C483E0 (callgraph 3.1)
// has the same order with GeometryInfo::CollidesWith.
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "ascii_string.h"
#include <math.h>

typedef float Real;

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, bool isSmall, Real height, Real majorRadius, Real minorRadius);
	virtual ~GeometryInfo();
	bool CollidesWith(const Coord3D &pos, Real angle, const GeometryInfo &other,
		const Coord3D &otherPos, Real otherAngle) const;
	bool terrainShapeIsSmall() const { return m_isSmall; }

private:
	bool m_isSmall;
	char m_data[0x5C - 5];
};

class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva0028449FFrameView
{
	char unknown00[0x40];
	unsigned int frame;
};

class ThingTemplate;
class Rva0027D098
{
public:
	void rva0027D098();
	float m_00; // +0x00
	float m_04; // +0x04
	float m_08; // +0x08
	int m_0C; // +0x0C
	int m_10; // +0x10
	const ThingTemplate *m_14; // +0x14
	unsigned char m_18; // +0x18
	char m_pad19[0x3];
	float m_1C; // +0x1C
	float m_20; // +0x20
	float m_24; // +0x24
	int m_28; // +0x28
	unsigned char m_2C; // +0x2C
	unsigned char m_2D; // +0x2D
	char m_pad2E[0x2];
};

struct Rva0028449FRecordView
{
	Coord3D pos;
	unsigned int key;
};

class Rva002872BA
{
public:
	void rva0028641F(unsigned int key, Rva0027D098 *record);
};
extern Rva002872BA *TheTriggerManager;

// 0x0028641F is rowed as a FireLogicSystem member taking the record's Coord3D.
struct Coord3D;
class FireLogicSystem
{
public:
	void rva00286373(int drawableID, const Coord3D *pos, const ThingTemplate *tmpl);
	void rva0028641F(unsigned int key, const Coord3D *pos);
};

class G00DFF080Obj;
extern G00DFF080Obj *TheTerrainVisual;

template<int N> class Rva0028449FSlots : public Rva0028449FSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template<> class Rva0028449FSlots<0> {};

class Rva0028449FGlobalView : public Rva0028449FSlots<18>
{
public:
	virtual void slot48(const Coord3D *pos, const GeometryInfo &geom, Real angle) = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58(unsigned int key) = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void setRawMapHeight(const ICoord2D *gridPos, int height) = 0;
};

class Object;

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
	void rva0028449F(const Coord3D *pos, const GeometryInfo &geom, Real angle);
	void flattenTerrain(Object *obj);

private:
	char unknown04[0x578 - 4];
	Rva0027D098 **first;
	Rva0027D098 **last;
	char unknown580[0x1910 - 0x580];
	unsigned int stamp;
};

void TerrainLogic::rva0028449F(const Coord3D *pos, const GeometryInfo &geom, Real angle)
{
	GeometryInfo shape(GEOMETRY_CYLINDER, false, 35.0f, 14.0f, 14.0f);
	for (Rva0027D098 **i = first; i != last; ++i)
	{
		Rva0028449FRecordView *record = reinterpret_cast<Rva0028449FRecordView *>(*i);
		if (record->key == 0)
			continue;
		if (geom.CollidesWith(*pos, angle, shape, record->pos, 0.0f))
		{
			unsigned int key = reinterpret_cast<Rva0028449FRecordView *>(*i)->key;
			if (TheTriggerManager)
				((FireLogicSystem *)TheTriggerManager)->rva0028641F(key, (const Coord3D *)*i);
			(*i)->rva0027D098();
			reinterpret_cast<Rva0028449FGlobalView *>(TheTerrainVisual)->slot58(key);
			stamp = reinterpret_cast<Rva0028449FFrameView *>(TheGameLogic)->frame;
		}
	}
	reinterpret_cast<Rva0028449FGlobalView *>(TheTerrainVisual)->slot48(pos, geom, angle);
}

// ?flattenTerrain@TerrainLogic@@QAEXPAVObject@@@Z retail 0x0028458F..0x00284AC6
// (1335 bytes) RET 4. Pinned ZH/BFME1 flattenTerrain twin (WorkerAIUpdate and
// DozerAIUpdate construct callers). BFME1 TerrainLogicFlattenTerrain.cpp
// (b1 0x001AE610) guides the order: skip small geometry, average the ground
// height over the footprint, clamp to the centre height and write it to nine
// neighbouring raw map cells per footprint point. BFME2 target differences:
// the object's GeometryInfo sits at +0xA8 and takes a TERRAIN_BOUNDS flag
// (rowed setFlag 0x006BF3C0) around the walk; the footprint sampler is the
// rowed Rva004DC1BF ctor 0x004DC1BF with next 0x004DC096 and reset 0x004DC082;
// grid cells are REAL_TO_INT_FLOOR(p * 0.1f) and TheTerrainVisual is the
// TheTerrainVisual slot +0x88 receiver. The floor import goes through math.h's
// inline floorf: the float floor overload or a double floor reorders the
// unrolled cell stores.
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(floorf(x)))

class BfmeStrF9;
class BfmeObjF9
{
public:
	void setFlag(const BfmeStrF9 &name, char flag);
};

class Vector3;

class Rva004DC1BF
{
public:
	Rva004DC1BF(const GeometryInfo &geometry, float angle, const Vector3 &position);
	bool rva004DC096(Coord2D *out);

private:
	GeometryInfo m_geometry;
	char m_data[0xB4 - 0x5C];
};

class Rva004DC082
{
public:
	void rva004DC082();
};

struct Rva0028458FObjectView
{
	char unknown00[0x38];
	Coord3D pos;
	Real angle;
	char unknown48[0xA8 - 0x48];
	GeometryInfo geometry;
};

extern TerrainLogic *TheTerrainLogic;

__forceinline const BfmeStrF9 &flagName(const AsciiString &name)
{
	return reinterpret_cast<const BfmeStrF9 &>(name);
}

void TerrainLogic::flattenTerrain(Object *obj)
{
	Rva0028458FObjectView *view = reinterpret_cast<Rva0028458FObjectView *>(obj);
	if (view->geometry.terrainShapeIsSmall())
		return;
	Coord3D pos;
	pos.x = view->pos.x;
	pos.y = view->pos.y;
	pos.z = view->pos.z;
	BfmeObjF9 *geom = reinterpret_cast<BfmeObjF9 *>(&view->geometry);
	geom->setFlag(flagName(AsciiString("TERRAIN_BOUNDS")), true);
	Rva004DC1BF iter(view->geometry, view->angle, reinterpret_cast<const Vector3 &>(pos));
	Real totalHeight = 0.0f;
	int count = 0;
	Coord2D pt;
	while (iter.rva004DC096(&pt))
	{
		totalHeight += getGroundHeight(pt.x, pt.y);
		++count;
	}
	if (count == 0)
	{
		geom->setFlag(flagName(AsciiString("TERRAIN_BOUNDS")), false);
		return;
	}
	Real average = totalHeight / count;
	int height = REAL_TO_INT_FLOOR(average * 25.6f + 0.5f);
	int center = REAL_TO_INT_FLOOR(TheTerrainLogic->getGroundHeight(pos.x, pos.y) * 25.6f);
	if (height > center)
		height = center;
	reinterpret_cast<Rva004DC082 *>(&iter)->rva004DC082();
	while (iter.rva004DC096(&pt))
	{
		ICoord2D grid;
		grid.x = REAL_TO_INT_FLOOR(pt.x * 0.1f);
		grid.y = REAL_TO_INT_FLOOR(pt.y * 0.1f);
		reinterpret_cast<Rva0028449FGlobalView *>(TheTerrainVisual)->setRawMapHeight(&grid, height);
		grid.x = REAL_TO_INT_FLOOR(pt.x * 0.1f) - 1;
		grid.y = REAL_TO_INT_FLOOR(pt.y * 0.1f);
		reinterpret_cast<Rva0028449FGlobalView *>(TheTerrainVisual)->setRawMapHeight(&grid, height);
		grid.x = REAL_TO_INT_FLOOR(pt.x * 0.1f) + 1;
		grid.y = REAL_TO_INT_FLOOR(pt.y * 0.1f);
		reinterpret_cast<Rva0028449FGlobalView *>(TheTerrainVisual)->setRawMapHeight(&grid, height);
		grid.x = REAL_TO_INT_FLOOR(pt.x * 0.1f);
		grid.y = REAL_TO_INT_FLOOR(pt.y * 0.1f) - 1;
		reinterpret_cast<Rva0028449FGlobalView *>(TheTerrainVisual)->setRawMapHeight(&grid, height);
		grid.x = REAL_TO_INT_FLOOR(pt.x * 0.1f);
		grid.y = REAL_TO_INT_FLOOR(pt.y * 0.1f) + 1;
		reinterpret_cast<Rva0028449FGlobalView *>(TheTerrainVisual)->setRawMapHeight(&grid, height);
		grid.x = REAL_TO_INT_FLOOR(pt.x * 0.1f) - 1;
		grid.y = REAL_TO_INT_FLOOR(pt.y * 0.1f) - 1;
		reinterpret_cast<Rva0028449FGlobalView *>(TheTerrainVisual)->setRawMapHeight(&grid, height);
		grid.x = REAL_TO_INT_FLOOR(pt.x * 0.1f) + 1;
		grid.y = REAL_TO_INT_FLOOR(pt.y * 0.1f) + 1;
		reinterpret_cast<Rva0028449FGlobalView *>(TheTerrainVisual)->setRawMapHeight(&grid, height);
		grid.x = REAL_TO_INT_FLOOR(pt.x * 0.1f) + 1;
		grid.y = REAL_TO_INT_FLOOR(pt.y * 0.1f) - 1;
		reinterpret_cast<Rva0028449FGlobalView *>(TheTerrainVisual)->setRawMapHeight(&grid, height);
		grid.x = REAL_TO_INT_FLOOR(pt.x * 0.1f) - 1;
		grid.y = REAL_TO_INT_FLOOR(pt.y * 0.1f) + 1;
		reinterpret_cast<Rva0028449FGlobalView *>(TheTerrainVisual)->setRawMapHeight(&grid, height);
	}
	geom->setFlag(flagName(AsciiString("TERRAIN_BOUNDS")), false);
}
