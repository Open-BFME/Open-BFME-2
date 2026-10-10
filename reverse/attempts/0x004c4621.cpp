// ?rva004C4621@CloudBreakSpecialPower@@QAEXPBUCoord3D@@@Z
// partial score=0.9747033365908139 date=2026-10-10
// ?rva004C4621@CloudBreakSpecialPower@@QAEXPBUCoord3D@@@Z
// partial score=0.9 date=2026-10-09
// cl: /I. /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x004C4621, 377B: CloudBreakSpecialPower::rva004C4621 (name pinned:
// the member called with the location, ret 4; the location is not read).
// Target evidence: the map extent comes from TheTerrainLogic slot 0x20; the
// module data FX (+0x80) plays at the map centre on the ground (slot 0x18
// ground height), then, when the spacing (+0x88) exceeds 1, the whole map is
// tiled at that spacing inside a one-spacing border, each grid coordinate
// truncated to a whole unit, creating the object named at +0x84 on the
// ground at every point through the 0x004C45CF helper (rowed as a stdcall
// body; retail loads ECX with this before calling it, so it is called here
// through a thiscall placeholder spelling pinned to the same body).

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
typedef float Real;
typedef int Int;

#include "Code/Libraries/Include/Lib/Coord3D.h"

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

class AsciiString;
class Matrix3D;

class FXList
{
public:
	static void doFXPos( const FXList *fx, const Coord3D *primary,
		const Matrix3D *primaryMtx = 0, const Real primarySpeed = 0.0f,
		const Coord3D *secondary = 0 );
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual Real getGroundHeight( Real x, Real y, Coord3D *normal ) const;
	virtual void v07();
	virtual void getExtent( Region3D *extent ) const;
};

extern TerrainLogic *TheTerrainLogic;

struct CloudBreakSpecialPowerModuleData
{
	unsigned char m_pad00[0x80];
	const FXList *m_fx;
	unsigned char m_objectName[4];
	Real m_spacing;
};

class CloudBreakSpecialPower
{
public:
	void rva004C4621( const Coord3D *loc );
	void rva004C45CF( const Coord3D *pos, const AsciiString *name );
private:
	void *m_vtable;
	const CloudBreakSpecialPowerModuleData *m_moduleData;
};

void CloudBreakSpecialPower::rva004C4621( const Coord3D * )
{
	const CloudBreakSpecialPowerModuleData *data = m_moduleData;
	Region3D extent;
	TheTerrainLogic->getExtent( &extent );

	Coord3D pos;
	if( data->m_fx )
	{
		pos.x = ( extent.lo.x + extent.hi.x ) * 0.5f;
		pos.y = ( extent.lo.y + extent.hi.y ) * 0.5f;
		pos.z = TheTerrainLogic->getGroundHeight( pos.x, pos.y, 0 );
		FXList::doFXPos( data->m_fx, &pos );
	}

	Real spacing = data->m_spacing;
	if( spacing > 1.0f )
	{
		for( Real y = (Real)(Int)( extent.lo.y + spacing ); y < extent.hi.y - spacing; y = (Real)(Int)( y + spacing ) )
		{
			for( Real x = (Real)(Int)( extent.lo.x + spacing ); x < extent.hi.x - spacing; x = (Real)(Int)( x + spacing ) )
			{
				pos.x = x;
				pos.y = y;
{ _ReadWriteBarrier(); pos.z = TheTerrainLogic->getGroundHeight( pos.x, pos.y, 0 ); }
				rva004C45CF( &pos, (const AsciiString *)data->m_objectName );
			}
		}
	}
}
