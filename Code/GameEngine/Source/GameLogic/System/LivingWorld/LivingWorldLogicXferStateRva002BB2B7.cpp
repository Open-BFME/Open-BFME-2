// cl: /O1 /DNDEBUG /MD
//
// ?rva002BB2B7@LivingWorldLogic@@QAEXPAVXfer@@@Z, retail 0x002BB2B7..0x002BB49C
// (485B), thiscall ret 4.
//
// The shared state block of LivingWorldLogic's two snapshot xfers (callers
// 0x002BB5FE in 0x002BB5DD and 0x002BBA7A in 0x002BBA45, both after their
// own xferVersion, with ecx = the logic and the stream pushed). Version 7:
// the region id at +0xB8 (rowed Rva003EFE82Get, "LivingWorldRegionID"); when
// not a CRC pass the flags +0xC8 / +0xE8 and from version 5 the int +0xE4,
// the flag +0x10A (cleared again on load) and the flags +0x176 / +0x177; the
// flag +0xE9; the game difficulty +0xEC (rowed XferGameDifficulty, not on CRC
// passes); from version 4 the words +0x100 / +0x104; from version 6 the flag
// +0x175 and from version 7 the flag +0x168 and the word +0x164 (both not on
// CRC passes); then the rowed XferPlayers, the owning army vector at +0x124
// (rowed XferOwningLivingWorldArmyVec), the two module vectors +0x10C /
// +0x118 (rowed rva002B8D06), the two ids +0xF4 / +0xF8 (rowed
// Rva002B2435Get), the flags +0x108 / +0x109 (not on CRC passes), the rowed
// XferDelayedRegionVictories and the rowed rva002B9CFC.
//
// Evidence (target): the callees above are read at the retail REL32s; the
// Xfer slots are +0x04 isLoading / +0x0C isCRC / +0x28 xferVersion / +0x78
// xferUnsignedInt / +0x7C xferInt / +0x90 xferBool. No WorldBuilder twin was
// found; the method and field names stay address-derived.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	unsigned char m_minVersion;
	unsigned char m_version;
};

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
#include "../../../../Include/Common/BfmeXfer.h"

class ModuleData;
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector;
}
typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > ModuleDataVector;

struct Rva003EFE82Obj;
struct Rva002B2435Obj;
class Other002B9CFC;

int __cdecl Rva003EFE82Get(Rva003EFE82Obj *obj, void *out);
int __cdecl Rva002B2435Get(Rva002B2435Obj *obj, void *out);
void __cdecl XferGameDifficulty(Xfer *xfer, int *difficulty);
void __cdecl XferOwningLivingWorldArmyVec(Xfer *xfer, ModuleDataVector *armies);

#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"

class Rva002B9CFC
{
public:
	void rva002B9CFC(Other002B9CFC *xfer);
};

#include "../../../../Include/GameLogic/LivingWorldLogic.h"

void LivingWorldLogic::rva002BB2B7(Xfer *xfer)
{
	XferVersion version;
	version.m_minVersion = 1;
	version.m_version = 7;
	(*xfer == reinterpret_cast<Xfer::Version &>(version));
	Rva003EFE82Get((Rva003EFE82Obj *)xfer, &fieldB8);
	if (!xfer->IsCRC())
	{
		(*xfer == fieldC8);
		(*xfer == fieldE8);
		if (version.m_version >= 5)
		{
			(*xfer == fieldE4);
			(*xfer == field10A);
			if (xfer->IsLoading())
				field10A = false;
			(*xfer == field176);
			(*xfer == field177);
		}
	}
	(*xfer == fieldE9);
	if (!xfer->IsCRC())
		XferGameDifficulty(xfer, &fieldEC);
	if (version.m_version >= 4)
	{
		(*xfer == field100);
		(*xfer == field104);
	}
	if (version.m_version >= 6 && !xfer->IsCRC())
		(*xfer == field175);
	if (version.m_version >= 7 && !xfer->IsCRC())
	{
		(*xfer == field168);
		(*xfer == field164);
	}
	XferPlayers(xfer);
	XferOwningLivingWorldArmyVec(xfer, (ModuleDataVector *)field124);
	((Rva002BA8F1Logic *)this)->rva002B8D06(xfer, (ModuleDataVector *)field10C);
	((Rva002BA8F1Logic *)this)->rva002B8D06(xfer, (ModuleDataVector *)field118);
	Rva002B2435Get((Rva002B2435Obj *)xfer, &fieldF4);
	Rva002B2435Get((Rva002B2435Obj *)xfer, &fieldF8);
	if (!xfer->IsCRC())
	{
		(*xfer == field108);
		(*xfer == field109);
	}
	XferDelayedRegionVictories(xfer);
	((Rva002B9CFC *)this)->rva002B9CFC((Other002B9CFC *)xfer);
}
