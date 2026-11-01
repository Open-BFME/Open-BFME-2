// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP=
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
#include "../../../../Libraries/Include/Lib/RGBColor.h"
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../Include/Common/BfmeXfer.h"


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

#include "../../../Include/Common/NameKeyGenerator.h"
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

