// cl: /Ireference/shims/bfme2_ascii /O1 /GX /MD /D_CRTIMP= /arch:SSE
//
// ?xfer@ExperienceTracker@@MAEXPAVXfer@@@Z @0x0039AFC8 257B (pinned): slot 3
// of vtable 0x0081AD20; also called by the ExperienceTrackerAutoResolve xfer
// 0x005DB074. BFME 2 reworked Zero Hour's ExperienceTracker::xfer (version
// 5): the version struct goes through Xfer slot 0x28; version >= 2 xfers the
// float at +0x10 directly, older loads read an int and convert it; the
// AsciiString at +0x08 (slot 0x6C) is re-keyed into +0x0C on load; then the
// float +0x1C, ints +0x14, a dropped int before version 4, +0x24, the bool
// +0x20 (slot 0x90) and +0x18; version >= 2 xfers the snapshot at +0x2C
// (its slot 2), version >= 3 the NameKeyType at +0x30 through the helper
// 0x00149101, version >= 5 the int at +0x28. Field names are unknown, so
// they stay offset-named.
#include "ascii_string.h"
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
struct RGBColor
{
	float red;
	float green;
	float blue;
};
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

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
	Version(unsigned char minimum, unsigned char current) : m_minimum(minimum), m_current(current) {}
	unsigned char m_minimum;
	unsigned char m_current;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

Xfer &Rva00149101XferNameKey( Xfer &xfer, NameKeyType &key );

class ExperienceTrackerSnapshot
{
public:
	virtual void v0();
	virtual void v1();
	virtual void xfer(Xfer *xfer) = 0; // slot 2
};

class ExperienceTracker
{
public:
	virtual ~ExperienceTracker();
	virtual void crc(Xfer *xfer);
	virtual void v2() = 0;
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_04;
	AsciiString m_08;
	NameKeyType m_0C;
	float m_10;
	int m_14;
	int m_18;
	float m_1C;
	bool m_20;
	int m_24;
	int m_28;
	ExperienceTrackerSnapshot *m_2C;
	NameKeyType m_30;
};

void ExperienceTracker::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 5 );
	*xfer == version;

	if( version.m_current >= 2 )
		*xfer == m_10;
	else if( xfer->IsLoading() )
	{
		int oldValue = 0;
		*xfer == oldValue;
		m_10 = (float)oldValue;
	}

	*xfer == m_08;
	if( xfer->IsLoading() )
		m_0C = TheNameKeyGenerator->nameToKey( m_08 );

	*xfer == m_1C;
	*xfer == m_14;
	if( version.m_current < 4 )
	{
		int unused = 0;
		*xfer == unused;
	}
	*xfer == m_24;
	*xfer == m_20;
	*xfer == m_18;
	if( version.m_current >= 2 )
		m_2C->xfer( xfer );
	if( version.m_current >= 3 )
		Rva00149101XferNameKey( *xfer, m_30 );
	if( version.m_current >= 5 )
		*xfer == m_28;
}

// ?xfer@Rva0039ADF3@@MAEXPAVXfer@@@Z @0x0039B10D 56B: slot 3 of vtable
// 0x0081AD34 (class of the rowed ??_GRva0039ADF3 0x0039B0F1, whose dtor
// 0x0039ADF3 chains to the tracker's): version 1, the tracker's xfer, then
// the ObjectID at +0x38 through the rowed XferObjectID 0x003060B2.
enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7fffffff
};
void XferObjectID( Xfer *xfer, ObjectID *id );

class Rva0039ADF3 : public ExperienceTracker
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_34;
	ObjectID m_38;
};

void Rva0039ADF3::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	ExperienceTracker::xfer( xfer );
	XferObjectID( xfer, &m_38 );
}
