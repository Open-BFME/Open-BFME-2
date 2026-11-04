// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "AIStartWoTRBattleTactic" skirmish-AI tactic (vtable 0x00872224; ctor
// 0x005AB1B4 in Rva004ECECDTacticCtors.cpp, dtor 0x005AB125 and ??_G, slot 9
// in Rva004ECECDTacticCreate.cpp). Base chain, all address-derived:
// Rva005DCC24 (ctor 0x005DCC0A) over AITacticOffensive over the AITactic.cpp
// object AITactic.
//
// It runs once per AI owner: the owner's TheSkirmishAIManager record keeps
// this unit's global key (0x00E0640C, built by 0x007B4513 and released by
// 0x007B961C).
//
//   0x005AB130  slot 1: not run yet, the game is not in mode 3 and past
//               frame 5
//   0x005AB188  slot 5: xfer, version 1, then the AITactic's
//   0x005AB235  slot 6: mark it run, then order every live unit of the
//               owner's that is of kind 3 or 0x5A to the owner's base
//               (0x004EBF4B) and finish
#include "ascii_string.h"

// Retail's initializer calls AsciiString's out-of-line const char * ctor
// (0x0000654A) rather than expanding it, so inline expansion is off here.
#pragma inline_depth(0)
AsciiString StartWoTRBattleTacticHasRun("StartWoTRBattleTacticHasRun");
#pragma inline_depth()

#include "../../../Libraries/Include/Lib/Coord3D.h"

// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
class UnicodeString;
class PooledString;
struct XferUnknown11;
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

template <int N> class BitFlags
{
public:
	unsigned m_words[7];
};

struct Rva0006EE7A : public BitFlags<69>
{
	Rva0006EE7A(int unused, int b1, int b2);
};

#include "Thing/thing.h"

class Rva00295A0FCommands
{
public:
	void Rva00295A0FCommand(void *where, int a, int b);
};

struct Rva005AB125AI
{
	char m_pad00[0x20];
	Rva00295A0FCommands m_commands;	// +0x20
};

class Object : public Thing
{
public:
	char m_pad060[0x258 - 0x60];
	Rva005AB125AI *m_ai;		// +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_438;		// +0x438
};

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class Rva004EBF4B
{
public:
	Coord3D rva004EBF4B();
};

struct Rva002A8AB1Record
{
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
};

struct Rva005AB125IDs
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

class Player;

#include "../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

#include "../../Include/Common/AITactic.h"
#include "../../Include/Common/AITacticOffensive.h"

class AIStartWoTRBattleTactic : public AITacticOffensive
{
public:
	virtual ~AIStartWoTRBattleTactic();
	virtual bool canRun(void *request);
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual AITactic *create();
};

bool AIStartWoTRBattleTactic::canRun(void *)
{
	Rva002A8AB1Record *record = TheSkirmishAIManager->rva002A8AB1(m_field24);
	return !record->rva002C7196(StartWoTRBattleTacticHasRun)
		&& TheGameLogic->m_114 != 3
		&& TheGameLogic->getFrame() > 5;
}

void AIStartWoTRBattleTactic::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	AITactic::xfer(xfer);
}

void AIStartWoTRBattleTactic::run()
{
	Rva002A8AB1Record *record = TheSkirmishAIManager->rva002A8AB1(m_field24);
	if (!record->rva002C7196(StartWoTRBattleTacticHasRun)) {
		record->rva002C717E(StartWoTRBattleTacticHasRun, 1);
		Rva005AB125IDs *ids = (Rva005AB125IDs *)(*(Rva005C4AD1LeaField **)TheSkirmishAIManager->rva002A8F24((Player *)m_field24))->get();
		Coord3D base = ((Rva004EBF4B *)record)->rva004EBF4B();
		ObjectID *last = ids->m_end;
		for (ObjectID *it = ids->m_begin; it != last; ++it) {
			Object *obj = TheGameLogic->findObjectByID(*it);
			if (obj && !(obj->m_438 & 1) && obj->isAnyKindOf(Rva0006EE7A(0, 3, 0x5A)))
				obj->m_ai->m_commands.Rva00295A0FCommand(&base, 0x7FFFFFFF, 0);
		}
		end(1, 0);
	} else {
		end(0, 0);
	}
}
