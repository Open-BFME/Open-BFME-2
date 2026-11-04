// cl: /MD
//
// ?rva0055B951@Rva0055B951@@UAEXPAVXfer@@@Z, retail 0x0055B951, 28 bytes.
// Evidence: slot 3 of 0x0081CDF0 and 0x0081D60C (DoXfer); calls Version1
// rowed 0x000053EE then inner ?rva0055B8CD rowed 0x0055B8CD at +0x1C;
// caller jmp at 0x003ABCF7; Ghidra FUN_0095b951 28B.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

namespace FXParticleSystem {
class DefaultColorModuleInfo { public: virtual void DoXfer(Xfer &); };
}

class Rva0055B951
{
	char m_pad[0x18];
	FXParticleSystem::DefaultColorModuleInfo m_inner;
public:
	virtual void rva0055B951(Xfer *xfer);
};

void Rva0055B951::rva0055B951(Xfer *xfer)
{
	xfer->Version1();
	m_inner.FXParticleSystem::DefaultColorModuleInfo::DoXfer(*xfer);
}
