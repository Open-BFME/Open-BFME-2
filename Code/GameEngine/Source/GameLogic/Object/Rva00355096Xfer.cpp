// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?Rva00355096Xfer@@YAPAVXfer@@PAV1@PAPAVRva0054840A@@@Z retail 0x00355096 106B.
// Chain lane: calls rowed 0x0054840A which you just landed; version 1,1 via slot 0x28 plus isLoading slot 4 plus news 0x14.
// Evidence: callers at 0x00355130 pass obj and obj+4 proving Xfer plus out-pointer; callees rowed ctor 0x0054829B plus xfer 0x0054840A plus new 0x0002FDA0.

#include "../../../Include/Common/ScalarTypes.h"



class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Rva0054840A
{
public:
	Rva0054840A();
	void rva0054840A(Xfer *xfer);
private:
	char m_pad[0x14];
};

Xfer *Rva00355096Xfer(Xfer *xfer, Rva0054840A **out)
{
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->operator==(version);
	if (xfer->IsLoading())
		*out = new Rva0054840A;
	(*out)->rva0054840A(xfer);
	return xfer;
}
