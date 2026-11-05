// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?xfer@Rva004AD9B0@@MAEXPAVXfer@@@Z, retail 0x004ADA2D, 67 bytes.
// Slot 3 (offset 0x0C) of vtable 0x008551C0 (class of ??1Rva004AD9B0 in
// ModuleUpdateDtors.cpp). Version(1,2) via Xfer slot 0x28, base
// SpecialAbilityUpdate::xfer rowed at 0x0044F996, then version-gated bool
// at +0x8C via Xfer slot 0x90. Xfer declaration verbatim from
// SpecialAbilityUpdateXfer.cpp (reverse overload order puts Version at
// 0x28 and bool at 0x90). No IsLightCRC (base handles). Callers: none
// rowed; vtable slot proves identity.
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
class Thing;
class ModuleData;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

class Thing;
class ModuleData;

class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();
protected:
	unsigned char m_pad[0x88 - 4];
};

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class Rva004AD9B0 : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned char m_pad8C[0x8C - 0x88];
	bool m_8C;
};

void Rva004AD9B0::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	SpecialAbilityUpdate::xfer(xfer);
	if (version.m_minimum >= 2)
		*xfer == m_8C;
}
