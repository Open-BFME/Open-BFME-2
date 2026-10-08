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

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

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
void rva003064CB( Xfer *xfer, Rva00291440 *bits );

class Rva004E0513
{
public:
	void rva004E0513( Xfer *xfer );
private:
	char m_unrecovered00[ 4 ];
};

// The snapshot base: only its virtual table matters to these bodies.
class SnapshotBase
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
};

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

class ExperienceLevelStore
{
public:
	ExperienceScalarTable *FindExperienceScalarTableByName(const AsciiString &name) const;	// 0x00288AF2
};

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

class Rva0039AE75
{
public:
	Rva0039AE75( Rva0039AE75Owner *owner );
	Real bfmeAt( Int value ) const;
protected:
	virtual ~Rva0039AE75();
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
private:
	Int indexFor( Int value ) const;
	Rva0039AE75Owner *m_owner;																												///< 0x04
	Real m_bfmeReal08;																												///< 0x08
	Int m_bfmeValue0C;																												///< 0x0C
	ExperienceScalarTable *m_bfmeTable10;																							///< 0x10
};

// The 0x44-byte BuffManager entries: only the slot-3 xfer is used.
class Rva00362702Entry : public SnapshotBase
{
protected:
	virtual void xfer( Xfer *xfer );
	friend class BuffManager;
private:
	char m_unrecovered04[ 0x44 - 0x04 ];
};

// g_Va00E01E74: VA 0x00E01E74 (.bss); retail initial bytes 00 00 00 00.
void *g_Va00E01E74;

class BuffManager : public SnapshotBase
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	void *m_bfmeOwner04;																											///< 0x04
	Rva00362702Entry m_entries[ 9 ];																					///< 0x08
};

class GlowMaterial : public SnapshotBase
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x0C - 0x04 ];
	UnsignedInt m_bfmeValue0C;																								///< 0x0C
	UnsignedInt m_bfmeValue10;																								///< 0x10
};

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

class XferException
{
public:
	enum
	{
		XFER_EXCEPTION_BFME_2 = 2
	};
};

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

class TBuff : public SnapshotBase
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Int m_bfmeValue04;																												///< 0x04
	UnsignedInt m_bfmeRaw08;																									///< 0x08, 4 raw bytes
	Real m_bfmeReal0C;																												///< 0x0C
	char m_unrecovered10[ 0x44 - 0x10 ];
	Bool m_bfmeFlag44;																												///< 0x44
	Coord3DBase m_bfmePosition48;																							///< 0x48
	Real m_bfmeReal54;																												///< 0x54
};

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void GlowMaterial::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	*xfer == m_bfmeValue0C;
	*xfer == m_bfmeValue10;
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
	rva003064CB( xfer, &m_bfmeBits10 );
	*xfer == m_bfmeValue0C;
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
void BuffManager::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	if( xfer->IsCRC() )
		return;
	Int count = 9;
	*xfer == count;
	g_Va00E01E74 = m_bfmeOwner04;
	for( Int i = 0; i < count; ++i )
	{
		Rva00362702Entry *entry = &m_entries[ i ];
		entry->xfer( xfer );
	}
	g_Va00E01E74 = 0;
}  // end xfer
