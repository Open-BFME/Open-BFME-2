// cl: /DNDEBUG /MD
// ?xfer@ArmySummaryEntry@@MAEXPAVXfer@@@Z @0x0040C4FE 136B
// Slot 3 of vtable 0x0083944C (class of ctor 0x0040C351). Version 1 1 via
// Xfer slot 0x28 then base CarryoverUnit xfer 0x0037DE79 then bool at +0xC5
// via slot 0x90 plus int at +0xB4 via Get 0x004E075F plus int at +0xB8 via
// LivingWorldArmyID 0x00318D1E plus bool at +0xC4 via slot 0x90 plus int at
// +0xBC via Get plus int at +0xC0 via Parse 0x004E12D7. Layout from ctor TU.
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
#include "../../Include/Common/BfmeXfer.h"
#include "../../Include/Common/XferVersion.h"
#include "../../Include/GameLogic/CarryoverUnit.h"
class Rva004E075FObj;
int Rva004E075FGet(Rva004E075FObj *o, int a);
void XferLivingWorldArmyID(Xfer *xfer, int *value);
void __cdecl Rva004E12D7Parse(void *ini, void *dest);
#include "../../Include/Common/ArmySummaryEntry.h"
void ArmySummaryEntry::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	CarryoverUnit::xfer(xfer);
	*xfer == m_c5;
	Rva004E075FGet((Rva004E075FObj *)xfer, (int)&m_b4);
	XferLivingWorldArmyID(xfer, &m_b8);
	*xfer == m_c4;
	Rva004E075FGet((Rva004E075FObj *)xfer, (int)&m_bc);
	Rva004E12D7Parse(xfer, &m_c0);
}
