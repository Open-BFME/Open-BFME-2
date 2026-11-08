// cl: /D_OPERATOR_NEW_DEFINED_ /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// Two guarded forwarders at 0x00091E83 and 0x00091FBA (90 bytes each, ret 0x2C):
// when the target at +0x14 is set, the nine-argument terrain add is passed on to
// BaseHeightMapRenderObjClass::addTree (0x0006813B) and its shrub twin
// (0x00068223) with the by-value location going through Coord3D's user copy
// constructor, exactly as those callees' own bodies do. Owner class unknown:
// honest address-derived names.
//
// W3DTerrainVisual::addProp (0x0009257A, 306 bytes, ret 0x10) lives here for
// the same reason: it passes its location by value to
// BaseHeightMapRenderObjClass::addProp (0x0006831C), and retail builds that
// argument through Coord3D's user copy constructor (field moves, the copy's
// address spilled to [ebp+0x14] for the destructor's unwind).
typedef float Real;

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_DTOR
#include "../../../Libraries/Include/Lib/Coord3DCtorView.h"

// ECF79's own by-value location view; same shape and user copy semantics.
struct Rva000ECF79Coord
{
	Real x;
	Real y;
	Real z;
	Rva000ECF79Coord( const Rva000ECF79Coord &c ) { x = c.x; y = c.y; z = c.z; }
	~Rva000ECF79Coord() {}
};

#include <string.h>
#include "ascii_string.h"
#include "vector3.h"

class Matrix3D;
struct Rva000ECF79Data;
struct Rva000E91CEData;

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h"
class GeometryInfo;
// The rowed terrain callees 0x00068073/0x000680D6 and 0x00068119, under
// their ledger owners.
class Rva00068073Host
{
public:
	void rva00068073( int a, Real b, int c );
	void rva000680D6( const Coord3D *pos, const GeometryInfo &geom, Real value );
};
// Retail 0x000AC514 (299B, unrowed): a two-float, one-int method of the object
// at W3DTerrainVisual +0x1C, in the WorldHeightMap code range.
class Rva000AC514Host
{
public:
	void rva000AC514( Real x, Real y, int value );
};
struct RGBColor;
class WorldHeightMap
{
public:
	void getTerrainColorAt( Real x, Real y, RGBColor *pColor );
};
class Rva00068119
{
public:
	void rva00068119( const Coord3D *pos, const GeometryInfo *geom, Real value );
};

class Rva00091E83
{
public:
	void rva00091E83( unsigned int id, Rva000ECF79Coord location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD );
private:
	char m_pad00[ 0x14 ];
	BaseHeightMapRenderObjClass *m_terrain;	///< 0x14
};

class Rva00091FBA
{
public:
	void rva00091FBA( unsigned int id, Coord3D location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD );
private:
	char m_pad00[ 0x14 ];
	BaseHeightMapRenderObjClass *m_terrain;	///< 0x14
};

void Rva00091E83::rva00091E83( unsigned int id, Rva000ECF79Coord location, Real scale, const Matrix3D *transform,
	Real randomScaleAmount, const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName,
	const AsciiString &nameD )
{
	if (m_terrain) {
		m_terrain->addTree(id, location, scale, transform, randomScaleAmount, data, shadowKind, textureName, nameD);
	}
}

void Rva00091FBA::rva00091FBA( unsigned int id, Coord3D location, Real scale, const Matrix3D *transform,
	Real randomScaleAmount, const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName,
	const AsciiString &nameD )
{
	if (m_terrain) {
		m_terrain->rva00068223(id, location, scale, transform, randomScaleAmount, data, shadowKind, textureName, nameD);
	}
}

// ------------------------------------------------------------------------------------------------
// W3DTerrainVisual::addProp
// ------------------------------------------------------------------------------------------------
// Zero Hour's W3DTerrainVisual::addProp (W3DTerrainVisual.cpp) is the semantic guide: build the
// snow/night model condition state, take the model name from the template's first draw module
// and hand the prop to the terrain render object. BFME 2 adds the scale argument (ret 0x10),
// asks the module data itself for the best model name (vslot 14, +0x38), then lets the prop
// draw module data (vslot 19, +0x4C; name at +0x08, flag at +0x0C as W3DPropDraw reads it)
// override both name and the extra flag BaseHeightMapRenderObjClass::addProp takes.
// Target facts: draw module info at ThingTemplate+0x2F0, getNthData 0x0033ACE8, weather at
// TheWritableGlobalData+0x138 and time of day at +0x134, 76-byte condition flags (bit 8 snow,
// bit 7 night), terrain render object at +0x14.

class ModelConditionFlags
{
public:
	ModelConditionFlags() { clear(); }
	void clear() { memset( m_bits, 0, sizeof( m_bits ) ); }
	void set( int i ) { m_bits[ i >> 5 ] |= 1u << ( i & 31 ); }
private:
	unsigned int m_bits[ 19 ];
};

enum
{
	MODELCONDITION_NIGHT = 7,
	MODELCONDITION_SNOW = 8
};

class W3DPropDrawModuleData
{
public:
	char m_unrecovered00[ 0x08 ];
	AsciiString m_modelName;	///< 0x08
	bool m_bfmeFlag;			///< 0x0C
};

class ModuleData
{
public:
	virtual void vslot00();
	virtual void vslot01();
	virtual void vslot02();
	virtual void vslot03();
	virtual void vslot04();
	virtual void vslot05();
	virtual void vslot06();
	virtual void vslot07();
	virtual void vslot08();
	virtual void vslot09();
	virtual void vslot10();
	virtual void vslot11();
	virtual void vslot12();
	virtual void vslot13();
	virtual AsciiString getBestModelNameForWB( const ModelConditionFlags &c ) const;	///< vslot 14
	virtual void vslot15();
	virtual void vslot16();
	virtual void vslot17();
	virtual void vslot18();
	virtual const W3DPropDrawModuleData *getAsW3DPropDrawModuleData() const;	///< vslot 19
};

class ModuleInfo
{
public:
	int getCount() const { return m_end - m_begin; }
	// LINK: same-body helper under a TU-unique name (identical inlined
	// bytes). This TU's getCount copy loses to the first-in-order copy (no
	// retail address); the call below inlines it but still emits the loser
	// COMDAT. Rebinding there emits only this unique (trivially kept) copy.
	// m_begin/m_end stay private. No flags touched.
	int bfme_get_count() const { return m_end - m_begin; }
	const ModuleData *getNthData( int i ) const;
private:
	struct Nugget { char m_unrecovered00[ 0x14 ]; };
	Nugget *m_begin;
	Nugget *m_end;
	Nugget *m_capacity;
};

class ThingTemplate
{
public:
	const ModuleInfo &getDrawModuleInfo() const { return m_drawModuleInfo; }
	// LINK: same reason as above; the call below inlines but emits the loser.
	const ModuleInfo &bfme_draw_info() const { return m_drawModuleInfo; }
private:
	char m_unrecovered0000[ 0x2F0 ];
	ModuleInfo m_drawModuleInfo;	///< 0x2F0
};

enum TimeOfDay { TIME_OF_DAY_NIGHT = 4 };
enum Weather { WEATHER_SNOWY = 1 };

#include "../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

class W3DTerrainVisual
{
public:
	virtual void addProp( const ThingTemplate *tTemplate, const Coord3D *pos, Real angle, Real scale );
	virtual void rva00091E19( int a, Real b, int c );
	virtual void removeTreesAndPropsForConstruction( const Coord3D *pos, const GeometryInfo &geom, Real value );
	virtual void rva00091E64( const Coord3D *pos, const GeometryInfo *geom, Real value );
	virtual void getTerrainColorAt( Real x, Real y, RGBColor *pColor );
	virtual void rva00091EEC( Vector3 pos, Real radius );
	virtual void rva000926AC( const AsciiString &name, bool flag, const AsciiString &secondName );
private:
	char m_unrecovered04[ 0x10 ];
	BaseHeightMapRenderObjClass *m_terrainRenderObject;	///< 0x14
	char m_unrecovered18[ 4 ];
	Rva000AC514Host *m_object1C;	///< 0x1C
};

void W3DTerrainVisual::addProp( const ThingTemplate *tTemplate, const Coord3D *pos, Real angle, Real scale )
{
	ModelConditionFlags state;
	state.clear();
	if (TheGlobalData->m_weather == WEATHER_SNOWY)
	{
		state.set(MODELCONDITION_SNOW);
	}
	if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
	{
		state.set(MODELCONDITION_NIGHT);
	}
	AsciiString modelName;
	bool bfmeFlag = true;
	const ModuleInfo &mi = tTemplate->bfme_draw_info();
	if (mi.bfme_get_count() > 0)
	{
		const ModuleData *mdd = mi.getNthData(0);
		const W3DPropDrawModuleData *md;
		if (mdd)
		{
			modelName = mdd->getBestModelNameForWB(state);
			md = mdd->getAsW3DPropDrawModuleData();
		}
		else
		{
			md = 0;
		}
		if (md)
		{
			modelName = md->m_modelName;
			bfmeFlag = md->m_bfmeFlag;
		}
	}
	if (m_terrainRenderObject && !modelName.isEmpty())
	{
		m_terrainRenderObject->addProp(1, *pos, angle, scale, modelName, bfmeFlag);
	}
}

// Three more guarded slots of the same table (retail 0x00091E19, 0x00091E45
// and 0x00091E64, just before 0x00091E83 above): each passes its
// arguments unchanged to a rowed terrain render object method when the
// object at +0x14 is set. Callee purposes are not recovered, so the slots
// keep address-derived names.
void W3DTerrainVisual::rva00091E19( int a, Real b, int c )
{
	if (m_terrainRenderObject)
		reinterpret_cast<Rva00068073Host *>(m_terrainRenderObject)->rva00068073(a, b, c);
}

void W3DTerrainVisual::removeTreesAndPropsForConstruction( const Coord3D *pos, const GeometryInfo &geom, Real value )
{
	if (m_terrainRenderObject)
		reinterpret_cast<Rva00068073Host *>(m_terrainRenderObject)->rva000680D6(pos, geom, value);
}

void W3DTerrainVisual::rva00091E64( const Coord3D *pos, const GeometryInfo *geom, Real value )
{
	if (m_terrainRenderObject)
		reinterpret_cast<Rva00068119 *>(m_terrainRenderObject)->rva00068119(pos, geom, value);
}

// Retail 0x00091D3D (36B, RET 0xC; vtable entry 0x00BC80B8): the same guarded
// pass-through against the object at +0x1C.
void W3DTerrainVisual::getTerrainColorAt( Real x, Real y, RGBColor *pColor )
{
	if (m_object1C)
		((WorldHeightMap *)m_object1C)->getTerrainColorAt(x, y, pColor);
}

// Retail 0x00091EEC (62B, RET 0x10; vtable entry 0x00BC80FC): passes a
// by-value position and a radius to the rowed four-float render object method.
void W3DTerrainVisual::rva00091EEC( Vector3 pos, Real radius )
{
	if (m_terrainRenderObject)
		m_terrainRenderObject->rva00069C5F(pos, radius);
}

// Retail 0x000926AC (64B, RET 0xC; the last W3DTerrainVisual vtable entry,
// 0x00BC812C): when the terrain render object is set, hands each name by value
// to its two rowed texture-slot reloads, 0x0006ABE7 (with the flag) and then
// 0x0006ACBD.
void W3DTerrainVisual::rva000926AC( const AsciiString &name, bool flag, const AsciiString &secondName )
{
	if (m_terrainRenderObject)
	{
		m_terrainRenderObject->rva0006ABE7(name, flag);
		m_terrainRenderObject->rva0006ACBD(secondName);
	}
}
