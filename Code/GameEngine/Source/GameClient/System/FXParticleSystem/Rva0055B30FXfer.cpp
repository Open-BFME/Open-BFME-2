// cl: /MD
// ?rva0055B30F@Rva0055B30F@@UAEXPAVXfer@@@Z @0x0055B30F 28B
// Chain of rowed 0x0055B266 via Version1 plus member at +0x1c.
// Evidence: thiscall 1 Xfer arg ret 4; vtable slot 3 of 0x0081CDCC and 0x0081D5D4;
// call Version1 row 0x53EE then rowed 0x0055B266; neighbours parse and 0x0055B367 same subsystem.
// Xfer decl verbatim order from Rva0055B266Xfer.
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

#include "../../../../Include/Common/BfmeXfer.h"

namespace FXParticleSystem {
class DefaultAlphaModuleInfo { public: virtual void DoXfer(Xfer &); };
}

class Rva0055B30F
{
public:
	virtual void rva0055B30F(Xfer *xfer);
private:
	char m_pad[0x18];
	FXParticleSystem::DefaultAlphaModuleInfo m_member;
};

void Rva0055B30F::rva0055B30F(Xfer *xfer)
{
	xfer->Version1();
	m_member.FXParticleSystem::DefaultAlphaModuleInfo::DoXfer(*xfer);
}
