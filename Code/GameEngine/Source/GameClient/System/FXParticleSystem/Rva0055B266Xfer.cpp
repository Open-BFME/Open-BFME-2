// cl: /MD
// Retail export 1161 names Snapshot slot 3 as DefaultAlphaModuleInfo::DoXfer(Xfer &).
// ?DoXfer@DefaultAlphaModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z @0x0055B266 54B
// Unlock FX DoXfer loop 8x via Version1 plus xferRandomVariable plus Xfer slot 0x78.
// Evidence: thiscall 1 Xfer arg ret 4; push 8 pop ebx countdown plus add esi 0x10;
// lea [esi-0xc] for GameClientRandomVariable plus push esi for second slot;
// Version1 row 0x53EE; xferRandomVariable row 0x306183; vtable slot 5 of 0x0081BF08
// plus slot 3 of 0x0081BA60; neighbours parse/ctor same subsystem;
// unblocks 0x0055B30F. Xfer decl verbatim order from PoisonedBehaviorXfer.
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

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

struct Rva0055B266Elem
{
	GameClientRandomVariable m_var;
	unsigned int m_val;
};

namespace FXParticleSystem
{
class DefaultAlphaModuleInfo
{
public:
	virtual void DoXfer(Xfer &xfer);
private:
	Rva0055B266Elem m_elems[8];
};
}

void FXParticleSystem::DefaultAlphaModuleInfo::DoXfer(Xfer &xfer)
{
	xfer.Version1();
	unsigned int *pVal = &m_elems[0].m_val;
	int count = 8;
	do {
		xferRandomVariable(xfer, *(GameClientRandomVariable *)(pVal - 3));
		xfer == *pVal;
		pVal += 4;
	} while (--count != 0);
}
