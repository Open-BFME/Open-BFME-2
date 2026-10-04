// cl: /Ireference/shims/bfme2_ascii /O1 /GX /MD /D_CRTIMP= /arch:SSE
//
// ?Rva00149101XferNameKey@@YAAAVXfer@@AAV1@AAW4NameKeyType@@@Z @0x00149101
// 140B: a cdecl helper that transfers a NameKeyType as its name. Loading
// reads an AsciiString (Xfer slot 0x6C) and stores nameToKey of it;
// otherwise it writes keyToName (row 0x00148C95 pinned as
// NameKeyGenerator::keyToName). Returns the Xfer (eax = first argument).
// Callers: ExperienceTracker::xfer 0x0039B0AB, 0x00354F37, 0x00355076 and
// 0x004EB2B3. Address-named: no ZH or BFME 1 counterpart.
// The Xfer view is the BFME 2 slot layout shared with W3DRopeDrawXfer.cpp
// (MSVC places the operator== overloads in reverse declaration order).
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

Xfer &Rva00149101XferNameKey( Xfer &xfer, NameKeyType &key )
{
	if( xfer.IsLoading() )
	{
		AsciiString name;
		xfer == name;
		key = TheNameKeyGenerator->nameToKey( name );
	}
	else
	{
		AsciiString name = TheNameKeyGenerator->keyToName( key );
		xfer == name;
	}
	return xfer;
}

