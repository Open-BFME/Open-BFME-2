#include "../../GameClient/BuffManager.h"
// cl: /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
//
// Snapshot xfer methods (slot 3) of four BFME 2 snapshot classes, each named
// by its vftable's slot-2 name literal; members are labelled by offset and
// by the Xfer overload each is passed to:
//
//  - GlowMaterial::xfer, retail 0x003624C4 (58 bytes; vftable 0x00C16FE8):
//    version, then UnsignedInts at +0x0C and +0x10.
//  - TScorch::xfer, retail 0x00068D53 (115 bytes; vftable 0x00BC5CB4):
//    nothing for a light CRC; version, four Reals at +0x04..+0x10, an Int at
//    +0x14 and a Bool at +0x18.
//  - EventParameter::xfer, retail 0x003318F7 (107 bytes; vftable
//    0x00BC9CD0): nothing for a light CRC; version, a Real (+0x04), a Bool
//    (+0x08), an ObjectID (+0x0C, rowed XferObjectID), an AsciiString
//    (+0x10) and 4 raw bytes (+0x14).
//  - CarryoverUnit::xfer, retail 0x0037DE79 (107 bytes; vftable 0x00BDF158):
//    version, an AsciiString (+0x04), an Int (+0x90), a Real (+0x08), the
//    rowed Rva004E0513 xfer of the member at +0x94, the pinned 1024-bit set
//    helper 0x003064CB on +0x10, and an Int (+0x0C).
//  - RegionBonusInfo::xfer, retail 0x003EFCD1 (102 bytes; vftable
//    0x00BE4324): version, then six Ints (+0x04, +0x0C, +0x08, +0x10,
//    +0x14, +0x18).
//  - ScoreKeeper::PerFrameStats::xfer, retail 0x0039B823 (112 bytes;
//    vftable 0x00C1AD6C): version 3; an Int (+0x04), two Shorts (+0x0C,
//    +0x0E), from version 2 a Real (+0x08), from version 3 an UnsignedShort
//    (+0x10).
//  - TBuff::xfer, retail 0x000D211D (152 bytes; vftable 0x00BCE310): nothing
//    for a light CRC; version 5, below which it throws XferException's
//    unnamed enum value 2 (retail throw info 0x00D00D44 names the type
//    .?AW4__unnamed@XferException@@); a copy of the Int at +0x04, 4 raw
//    bytes (+0x08), a Real (+0x0C), a Bool (+0x44), a Coord3D (+0x48) and a
//    Real (+0x54).
//  - Rva0039AE75::xfer, retail 0x0039AD0B (58 bytes): slot 2 of the
//    three-slot ??_7Rva0039AE75 0x00C1AD60 (destructor, empty crc, xfer: the
//    bare Snapshot layout); version, a Real (+0x08) and an Int (+0x0C).
//  - BuffManager::xfer, retail 0x00362702 (109 bytes; vftable 0x00C17088):
//    version; unless CRC-ing, a count of 9 and the snapshot (own slot 3) of
//    each 0x44-byte entry from +0x08, with +0x04 published in the global at
//    VA 0x00E01E74 (.bss) for the duration.

#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *id );

class Rva00291440
{
	unsigned int m_bits[ 1024 / 32 ];
};
void xferUpgradeMask( Xfer *xfer, Rva00291440 *bits );

class Rva004E0513
{
public:
	void rva004E0513( Xfer *xfer );
private:
	char m_unrecovered00[ 4 ];
};

// Canonical four-slot snapshot lifetime and virtual layout.
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
typedef Snapshot SnapshotBase;

// ExperienceLevelStore's scalar table (its accessors live in
// ExperienceLevelSystem.cpp): an STLport vector<Real> at +0x00, the name at +0x0C.
class ExperienceScalarTable
{
public:
	int size() const { return m_end - m_begin; }
	Real *m_begin;
	Real *m_end;
	Real *m_endOfStorage;
	AsciiString m_name;			// +0x0C
};

#include "../../../Include/GameLogic/ExperienceLevelStore.h"

class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

// What the owner's +0x04 points at: only the scalar-table name at +0x9C is read.
struct Rva0039AE75Source
{
	char m_unrecovered00[ 0x9C ];
	AsciiString m_scalarTableName;																									///< 0x9C
};

// The owner is the ExperienceTracker whose constructor (0x0039AEBC) news this
// object with itself as the argument and keeps it at +0x2C.
struct Rva0039AE75Owner
{
	void *m_vtable;
	Rva0039AE75Source *m_parent;																										///< 0x04
};

#include "../../../Include/Common/Rva0039AE75.h"

// The 0x44-byte BuffManager entries: only the slot-3 xfer is used.


// g_Va00E01E74: VA 0x00E01E74 (.bss); retail initial bytes 00 00 00 00.
void *g_Va00E01E74;





class TScorch : public SnapshotBase
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Real m_bfmeReal04;																												///< 0x04
	Real m_bfmeReal08;																												///< 0x08
	Real m_bfmeReal0C;																												///< 0x0C
	Real m_bfmeReal10;																												///< 0x10
	Int m_bfmeValue14;																												///< 0x14
	Bool m_bfmeFlag18;																												///< 0x18
};

class EventParameter : public SnapshotBase
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Real m_bfmeReal04;																												///< 0x04
	Bool m_bfmeFlag08;																												///< 0x08
	ObjectID m_bfmeObject0C;																									///< 0x0C
	AsciiString m_bfmeString10;																								///< 0x10
	UnsignedInt m_bfmeRaw14;																									///< 0x14, 4 raw bytes
};

class CarryoverUnit : public SnapshotBase
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	AsciiString m_bfmeString04;																								///< 0x04
	Real m_bfmeReal08;																												///< 0x08
	Int m_bfmeValue0C;																												///< 0x0C
	Rva00291440 m_bfmeBits10;																									///< 0x10, 1024-bit set
	Int m_bfmeValue90;																												///< 0x90
	Rva004E0513 m_bfmeMember94;																								///< 0x94
};

// The vectors Rva001EBAEA::xfer clears on old versions: STLport's erase is
// all it calls (rowed 0x001EBDFA for the 172-byte carryover records, the
// folded 4-byte element erase 0x00532803 for the science list).
namespace _STL
{
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	T *erase( T *first, T *last );
	void clear() { erase( _M_start, _M_finish ); }
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}
struct BfmeAssignRecord172;
struct Rva005334A4Element;
class CarryoverUnit;
Xfer *Rva001EC0A0Xfer( Xfer *xfer, _STL::vector<CarryoverUnit> *units );
Xfer *Rva001ECA2DXfer( Xfer *xfer, void *sciences );
#include <string.h>

// The LinearCampaign snapshot (vftable 0x00BDF168, slot-2 name getter
// 0x001EAE63 "LinearCampaign"); its rowed constructor 0x001EBAEA sets out this
// layout. Field meanings are not established.
class Rva001EBAEA : public SnapshotBase
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Int m_bfmeValue04;																												///< 0x04
	Int m_bfmeValue08;																												///< 0x08
	Int m_bfmeValue0C;																												///< 0x0C
	Real m_bfmeReal10;																												///< 0x10
	_STL::vector<Rva005334A4Element> m_bfmeSciences14;																				///< 0x14
	Rva00291440 m_bfmeBits20;																									///< 0x20, 1024-bit set
	Real m_bfmeRealA0;																												///< 0xA0
	_STL::vector<BfmeAssignRecord172> m_bfmeUnitsA4;																				///< 0xA4
	Int m_bfmeValueB0;																												///< 0xB0
	_STL::vector<BfmeAssignRecord172> m_bfmeUnitsB4;																				///< 0xB4
	Bool m_bfmeFlagC0;																												///< 0xC0
	Bool m_bfmeFlagC1;																												///< 0xC1
	Bool m_bfmeFlagC2;																												///< 0xC2
	Bool m_bfmeFlagC3;																												///< 0xC3
};

class RegionBonusInfo : public SnapshotBase
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Int m_bfmeValue04;																												///< 0x04
	Int m_bfmeValue08;																												///< 0x08
	Int m_bfmeValue0C;																												///< 0x0C
	Int m_bfmeValue10;																												///< 0x10
	Int m_bfmeValue14;																												///< 0x14
	Int m_bfmeValue18;																												///< 0x18
};

class ScoreKeeper
{
public:
	class PerFrameStats : public SnapshotBase
	{
	protected:
		virtual void xfer( Xfer *xfer );
	private:
		Int m_bfmeValue04;																											///< 0x04
		Real m_bfmeReal08;																											///< 0x08
		short m_bfmeShort0C;																										///< 0x0C
		short m_bfmeShort0E;																										///< 0x0E
		unsigned short m_bfmeShort10;																						///< 0x10
	};
};

#include "../../../Include/Common/XferException.h"

// Retail ctor 0x000D1AF3 builds the slot array through rowed vector_constructor_iterator
// (0x1423) with the 3-byte folded empty ctor VA 0x87A6A9 (stride 0x10). The slot has no
// destructor (retail takes ??_H, not ??_L), so it is not Region2D, whose empty dtor retail
// exports at 0x000B3FD0; an opaque four-float row with an empty inline ctor stands in.
struct TBuffSlot
{
	TBuffSlot() {}
	float m_value[ 4 ];
};
// Source argument views: +0x441 flag, float getter 0x000788D3 (+0x200), position getter
// 0x002763E6 (rowed under the address-derived Drawable name).
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva000788D3FloatField.h"
#include "../../../Include/GameClient/Drawable.h"
int g_012F801C;	// 0x009EBC38 (live-instance counter bumped by the ctor)
struct TBuffSource
{
	char m_pad[ 0x441 ];
	unsigned char m_flag441;
};

class TBuff : public SnapshotBase
{
public:
	TBuff( const TBuffSource *source, Int value );
protected:
	virtual void xfer( Xfer *xfer );
private:
	Int m_bfmeValue04;																												///< 0x04
	UnsignedInt m_bfmeRaw08;																									///< 0x08, 4 raw bytes
	Real m_bfmeReal0C;																												///< 0x0C
	char m_bfmeByte10;																												///< 0x10
	TBuffSlot m_bfmeSlots14[ 3 ];																							///< 0x14, three 16-byte slots
	Bool m_bfmeFlag44;																												///< 0x44
	char m_bfmeByte45;																												///< 0x45
	Coord3DBase m_bfmePosition48;																							///< 0x48
	Real m_bfmeReal54;																												///< 0x54
};

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void GlowMaterial::DoXfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	*xfer == m_0C;
	*xfer == m_10;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void TScorch::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;
	Xfer::Version version( 1, 1 );
	*xfer == version;
	*xfer == m_bfmeReal04;
	*xfer == m_bfmeReal08;
	*xfer == m_bfmeReal0C;
	*xfer == m_bfmeReal10;
	*xfer == m_bfmeValue14;
	*xfer == m_bfmeFlag18;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void EventParameter::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;
	Xfer::Version version( 1, 1 );
	*xfer == version;
	*xfer == m_bfmeReal04;
	*xfer == m_bfmeFlag08;
	XferObjectID( xfer, &m_bfmeObject0C );
	*xfer == m_bfmeString10;
	xfer->XferRawBytes( &m_bfmeRaw14, 4 );
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void CarryoverUnit::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	*xfer == m_bfmeString04;
	*xfer == m_bfmeValue90;
	*xfer == m_bfmeReal08;
	m_bfmeMember94.rva004E0513( xfer );
	xferUpgradeMask( xfer, &m_bfmeBits10 );
	*xfer == m_bfmeValue0C;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method: retail 0x001ECBAD (326 bytes), version 6. Older saves leave the
 *  later fields cleared. */
// ------------------------------------------------------------------------------------------------
void Rva001EBAEA::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 6 );
	*xfer == version;
	*xfer == m_bfmeValue0C;
	if( version.m_minimum >= 6 )
		*xfer == m_bfmeFlagC3;
	else
		m_bfmeFlagC3 = false;
	Rva001EC0A0Xfer( xfer, (_STL::vector<CarryoverUnit> *)&m_bfmeUnitsA4 );
	*xfer == m_bfmeFlagC0;
	*xfer == m_bfmeFlagC1;
	*xfer == m_bfmeFlagC2;
	if( version.m_minimum >= 2 )
	{
		*xfer == m_bfmeValueB0;
		Rva001EC0A0Xfer( xfer, (_STL::vector<CarryoverUnit> *)&m_bfmeUnitsB4 );
	}
	else
	{
		m_bfmeUnitsB4.clear();
		m_bfmeValueB0 = 0;
	}
	if( version.m_minimum >= 3 )
	{
		*xfer == m_bfmeReal10;
		Rva001ECA2DXfer( xfer, &m_bfmeSciences14 );
	}
	else
	{
		m_bfmeReal10 = 0.0f;
		m_bfmeSciences14.clear();
	}
	if( version.m_minimum >= 4 )
		xferUpgradeMask( xfer, &m_bfmeBits20 );
	else
		memset( &m_bfmeBits20, 0, sizeof( m_bfmeBits20 ) );
	if( version.m_minimum >= 5 )
		*xfer == m_bfmeRealA0;
	else
		m_bfmeRealA0 = 0.0f;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void RegionBonusInfo::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	*xfer == m_bfmeValue04;
	*xfer == m_bfmeValue0C;
	*xfer == m_bfmeValue08;
	*xfer == m_bfmeValue10;
	*xfer == m_bfmeValue14;
	*xfer == m_bfmeValue18;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void ScoreKeeper::PerFrameStats::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 3 );
	*xfer == version;
	*xfer == m_bfmeValue04;
	*xfer == m_bfmeShort0C;
	*xfer == m_bfmeShort0E;
	if( version.m_minimum >= 2 )
		*xfer == m_bfmeReal08;
	if( version.m_minimum >= 3 )
		*xfer == m_bfmeShort10;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void TBuff::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;
	Xfer::Version version( 1, 5 );
	*xfer == version;
	if( version.m_minimum < 5 )
		throw XferException::XFER_EXCEPTION_BFME_2;
	Int value = m_bfmeValue04;
	*xfer == value;
	xfer->XferRawBytes( &m_bfmeRaw08, 4 );
	*xfer == m_bfmeReal0C;
	*xfer == m_bfmeFlag44;
	*xfer == m_bfmePosition48;
	*xfer == m_bfmeReal54;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void Rva0039AE75::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	*xfer == m_bfmeReal08;
	*xfer == m_bfmeValue0C;
}  // end xfer

// ------------------------------------------------------------------------------------------------
// Rva0039AE75's constructor, retail 0x0039AE30 (69 bytes; stores vftable
// 0x00C1AD60, called only from the ExperienceTracker constructor at 0x0039AF3C
// after a 0x14-byte operator new), Rva0039AE75::indexFor, retail 0x0039AE92
// (42 bytes), and Rva0039AE75::bfmeAt, retail 0x0039B145 (42 bytes), its only
// caller (call at 0x0039B161).
// Ported from Open-BFME-1 game/GameEngine/Source/GameLogic/Object/BfmeThingEFEAt.cpp,
// BfmeThingEFEClampIndex.cpp and BfmeThingEFECtor.cpp (donor revision 177ae72da755fb4adc35cb2b3fcf291e14174ad3;
// donor flags /DNDEBUG /MD /EHsc, recompiled /O1). Target facts: the donor
// indexFor body compiled /O1 places uniquely at 0x0039AE92 by masked whole-.text
// search; WorldBuilder's unnamed bodies at its counterparts (WB 0xFA0EC0 and
// 0xFA0E60, matched by call graph) read the same fields: the Int at +0x0C that
// this class's xfer 0x0039AD0B saves, and a begin/end Real table at +0x10.
// Carried from the donor: the method names (the donor tree's own inventions;
// retail and WB name neither) and the table's element type. Unlike BFME 1,
// BFME 2 keeps the clamp out of line, and its constructor reads the table name
// straight from the owner's +0x04 object at +0x9C (no template override walk)
// and looks it up through the rowed ExperienceLevelStore::FindExperienceScalarTableByName.
// ------------------------------------------------------------------------------------------------
Rva0039AE75::Rva0039AE75( Rva0039AE75Owner *owner ) :
	m_owner( owner ),
	m_bfmeReal08( 1.0f ),
	m_bfmeValue0C( 1 ),
	m_bfmeTable10( 0 )
{
	m_bfmeTable10 = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->FindExperienceScalarTableByName( m_owner->m_parent->m_scalarTableName );
}

Int Rva0039AE75::indexFor( Int value ) const
{
	Int index = value - m_bfmeValue0C;
	if ( index <= 0 )
		return 0;
	if ( index >= m_bfmeTable10->size() )
		return m_bfmeTable10->size() - 1;
	return index;
}

Real Rva0039AE75::bfmeAt( Int value ) const
{
	if ( m_bfmeTable10->size() == 0 )
		return 1.0f;
	return m_bfmeTable10->m_begin[ indexFor( value ) ];
}

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void BuffManager::DoXfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	if( xfer->IsCRC() )
		return;
	Int count = 9;
	*xfer == count;
	g_Va00E01E74 = m_drawable;
	for( Int i = 0; i < count; ++i )
	{
		BuffInstance *entry = &m_buffs[ i ];
		entry->DoXfer( xfer );
	}
	g_Va00E01E74 = 0;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Retail 0x000D1AF3 (173 bytes, RET 8): value and zeroed state, then, when a source is
 *  given, its +0x441 flag, float field (0x788D3) and position (0x2763E6). */
// ------------------------------------------------------------------------------------------------
TBuff::TBuff( const TBuffSource *source, Int value )
	: m_bfmeValue04( value ), m_bfmeRaw08( 0 ), m_bfmeReal0C( 0.0f ), m_bfmeByte10( 0 )
{
	m_bfmeFlag44 = false;
	m_bfmeByte45 = 0;
	Coord3DBase *position = &m_bfmePosition48;
	position->x = 0.0f;
	position->y = 0.0f;
	position->z = 0.0f;
	m_bfmeReal54 = 1.0f;
	if( source )
	{
		reinterpret_cast<unsigned char &>( m_bfmeFlag44 ) = source->m_flag441;
		m_bfmeReal54 = ((const Rva000788D3FloatField *)source)->get();
		*position = *(const Coord3DBase *)((const Drawable *)source)->getPosition();
	}
	++g_012F801C;
}
