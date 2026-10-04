// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /Ireference/shims/bfme2_ascii
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
