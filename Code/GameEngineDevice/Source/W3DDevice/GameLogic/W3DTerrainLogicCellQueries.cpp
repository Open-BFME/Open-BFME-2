// cl: /MD /EHsc /DNDEBUG
// W3DTerrainLogic per-cell terrain queries that BFME added after isCliffCell.
//
// Target evidence: W3DTerrainLogic's vftable holds five adjacent (Real x, Real y)
// slots at 0x007C58E0..0x007C58F0, right after isUnderwater. The first is
// isCliffCell (0x00062D94, rowed in W3DTerrainLogic.cpp: ZH puts isCliffCell
// directly after isUnderwater); the other four are these bodies. Each is the
// same 31-byte forwarder, `return TheTerrainRenderObject->query(x, y);` with
// ecx reloaded from TheTerrainRenderObject (0x00DE1EAC, the global newMap and
// isClearLineOfSight read) and ret 8.
//
// Each callee is a 115-byte BaseHeightMapRenderObjClass body that null-checks
// m_map (+0x37C0), converts x/y to a border-adjusted clamped cell and asks the
// WorldHeightMap one per-cell question, exactly like isCliffCell at 0x000671B2.
// The donor names of the four BFME queries are unknown, so they are
// address-derived; return widths follow each callee's own return register use.
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Rva006BE630
{
public:
	bool bfmeBitA(int x, int y) const;
};

class BaseHeightMapRenderObjClass
{
public:
	unsigned char rva0006B187(float x, float y);
	unsigned char rva00067225(float x, float y);
	bool rva00067298(float x, float y);
	unsigned char rva0006730B(float x, float y);
	unsigned char m_unknown0000[0x37C0];
	Rva006BE630 *m_map; // +0x37C0
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

// The rowed base-object lookups the two tail-jump slots below reach.
template <class T> class StringBase;
class Rva00282021WaterLookup
{
public:
	void *rva00282021(const StringBase<char> &name);
};
// The base update entry takes the same secondary +4 receiver as this slot.
class TerrainLogic
{
public:
	virtual void update();
};

// TerrainLogic's rowed position lookup 0x0028170E (TerrainLogicWaterLookup.cpp).
struct Rva0028170EArea;
class Rva0028170EHost
{
public:
	Rva0028170EArea *rva0028170E(float x, float y, float z);
};

class W3DTerrainLogic
{
public:
	virtual unsigned char rva00062DB3(float x, float y) const;
	virtual unsigned char rva00062DD2(float x, float y) const;
	virtual bool rva00062DF1(float x, float y) const;
	virtual unsigned char rva00062E10(float x, float y) const;
	virtual bool rva00063082(const Coord3D *pos) const;
	virtual Rva0028170EArea *rva00062ACA(float x, float y, float z);
	virtual void *rva00062AEC(const StringBase<char> &name);
	virtual void update();
	unsigned char m_unknown0004[0x1C - 4];
	int m_width;  // +0x1C
	int m_height; // +0x20
};

// Native 0x00062ACA (34 bytes, RET 0xC), two adjacent W3DTerrainLogic
// vftable slots (and the same pair in three more tables): passes the three
// coordinates unchanged to the base-object lookup 0x0028170E.
Rva0028170EArea *W3DTerrainLogic::rva00062ACA(float x, float y, float z)
{
	return reinterpret_cast<Rva0028170EHost *>(this)->rva0028170E(x, y, z);
}

// Native 0x00062AEC and 0x00062B97 (5 bytes each), more W3DTerrainLogic
// vftable entries (the first also in three more tables): tail jumps to the
// base-object name lookup 0x00282021 and to 0x0027CD63.
void *W3DTerrainLogic::rva00062AEC(const StringBase<char> &name)
{
	return reinterpret_cast<Rva00282021WaterLookup *>(this)->rva00282021(name);
}

void W3DTerrainLogic::update()
{
	reinterpret_cast<TerrainLogic *>(this)->TerrainLogic::update();
}

// vftable 0x007C58E4, callee 0x0006B187
unsigned char W3DTerrainLogic::rva00062DB3(float x, float y) const
{
	return TheTerrainRenderObject->rva0006B187(x, y);
}

// vftable 0x007C58E8, callee 0x00067225
unsigned char W3DTerrainLogic::rva00062DD2(float x, float y) const
{
	return TheTerrainRenderObject->rva00067225(x, y);
}

// vftable 0x007C58EC, callee 0x00067298
bool W3DTerrainLogic::rva00062DF1(float x, float y) const
{
	return TheTerrainRenderObject->rva00067298(x, y);
}

// vftable 0x007C58F0, callee 0x0006730B
unsigned char W3DTerrainLogic::rva00062E10(float x, float y) const
{
	return TheTerrainRenderObject->rva0006730B(x, y);
}

// vftable 0x007C5958 (slot after TerrainLogic::updateBridgeDamageStates),
// native 0x00063082..0x00063153 RET4: the cell of a world position offset by
// the slot-11 float (the shared bare-ret stub in this table), clamped to
// [0, extent * 10] on each axis, floored to map cells at 0.1 and rounded by
// fistp, asked of the height map's bit plane (rowed 0x00062EA9).
struct Rva00063082SlotView
{
	virtual void s00() const; virtual void s01() const; virtual void s02() const;
	virtual void s03() const; virtual void s04() const; virtual void s05() const;
	virtual void s06() const; virtual void s07() const; virtual void s08() const;
	virtual void s09() const; virtual void s10() const;
	virtual float border() const;
};

__forceinline long fast_float2long_round(float inputValue)
{
	long roundedValue;
	__asm {
		fld [inputValue]
		fistp [roundedValue]
	}
	return roundedValue;
}

bool W3DTerrainLogic::rva00063082(const Coord3D *pos) const
{
	float border = reinterpret_cast<const Rva00063082SlotView *>(this)->border();
	float x = pos->x + border;
	float y = pos->y + border;
	if (x < 0.0f)
		x = 0.0f;
	else if (x > m_width * 10.0f)
		x = m_width * 10.0f;
	if (y < 0.0f)
		y = 0.0f;
	else if (y > m_height * 10.0f)
		y = m_height * 10.0f;
	return TheTerrainRenderObject->m_map->bfmeBitA(
		fast_float2long_round(floorf(x * 0.1f)), fast_float2long_round(floorf(y * 0.1f)));
}
