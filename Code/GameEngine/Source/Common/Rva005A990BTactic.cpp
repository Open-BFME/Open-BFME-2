// cl: /O1 /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "AIBasePenetrationTroopsTactic" skirmish-AI tactic (vtable 0x00871DB4;
// ctor 0x005A9988 in Rva004ECECDTacticCtors.cpp, dtor 0x005A990B and ??_G in
// Rva005DC73CDerived.cpp, slot 9 in Rva004ECECDTacticCreate.cpp). Base chain,
// all address-derived: AITacticOffensive over the AITactic.cpp object AITactic.
//
// The tactic keeps an "is running" flag per AI owner in the owner's
// TheSkirmishAIManager record (0x002A8AB1 lookup on the +0x24 owner), keyed
// by this unit's global AsciiString (0x00E06404, built by 0x007B445F and
// released by 0x007B95EA):
//
//   0x005A99D7  slot 1: not already running, the base test passes, the
//               owner's record has a positive +0x16C, and the request's
//               object (0x002C5DA6) is of the wanted kind and free
//   0x005A994B  slot 2: clear the flag
//   0x005A9A89  slot 3: flag the unit (+0x2E0 / +0x307
//               bits, +0x2D4 = 5) and set the flag
//   0x005A9916  slot 6: 0x004ED372 with the +0x20 record's +0x0C point
//   0x005A9923  slot 7: while running (+0x10), stop (0x004ED748(1, 0)) when
//               0x004ED169 says so or the +0x20 record is flagged at +0x18
#include "ascii_string.h"
#include <math.h>

// Retail's initializer calls AsciiString's out-of-line const char * ctor
// (0x0000654A) rather than expanding it, so inline expansion is off here.
#pragma inline_depth(0)
AsciiString AIBasePenetrationTroopsTactic_IsRunning("AIBasePenetrationTroopsTactic_IsRunning");
#pragma inline_depth()

// The engine's float helpers (fast_float_floor / fast_float2long_round).
static __forceinline float fast_floor(float f)
{
	return (float)floor((double)f);
}

static __forceinline int fast_round(float f)
{
	int i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

extern float g_secondsPerLogicFrame;

// A frame count this unit computes at startup (0x007B44AE); no retail code
// reads it back.
int g_00E06408 = fast_round(fast_floor(g_secondsPerLogicFrame * 20.0f));

struct Rva005A990BRecord
{
	char m_pad00[0x0C];
	char m_point0C[0x0C];	// +0x0C
	bool m_18;		// +0x18
};

struct Rva002A8AB1Record
{
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
	char m_pad000[0x16C];
	int m_16C;		// +0x16C
};

#include "../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

// WorldBuilder sets bit indices 8 and 9 in the +0x2E0 mask and 90
// in the +0x2FC mask. Target measures seven words in each accessed view.
struct TacticKindMask
{
	unsigned int bits[7];
	unsigned int &word(unsigned int bit) { return bits[bit / 32]; }
	void set(unsigned int bit) { word(bit) |= 1UL << (bit % 32); }
};
struct Rva005A990BUnit
{
	char pad[0x2D4];
	int m_2D4;
	char pad2D8[0x2E0 - 0x2D8];
	TacticKindMask m_2E0, m_2FC;
};

#include "../../Include/Common/AITactic.h"
#include "../../Include/Common/AITacticOffensive.h"

class AIBasePenetrationTroopsTactic : public AITacticOffensive
{
public:
	virtual ~AIBasePenetrationTroopsTactic();
	virtual bool initializeTeamTemplate(Rva005A990BUnit *, void *);
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual void run();
	virtual void update();
};


void AIBasePenetrationTroopsTactic::cleanUp()
{
	Rva002A8AB1Record *record = TheSkirmishAIManager->rva002A8AB1(((void *)m_field24));
	if (record)
		record->rva002C717E(AIBasePenetrationTroopsTactic_IsRunning, 0);
}

void AIBasePenetrationTroopsTactic::run()
{
	rva004ED372((const struct Coord3D *)((Rva005A990BRecord *)m_field20)->m_point0C);
}

void AIBasePenetrationTroopsTactic::update()
{
	if (m_field10 && (((Rva005A990BRecord *)m_field20)->m_18 || rva004ED169()))
		end(1, 0);
}

// Retail 0x005A9A89..0x005A9ACD, 68 bytes, vftable slot 3 (ret 8).
// WB 0x01519B80 names initializeTeamTemplate and asserts the owner record
// at AIBasePenetrationTroopsTactic.cpp:114. The template's original argument
// type and the unused second word remain unknown; the measured view follows
// the base's existing signature. All flag indices and offsets are native.
bool AIBasePenetrationTroopsTactic::initializeTeamTemplate(Rva005A990BUnit *unit, void *)
{
	unit->m_2E0.set(8);
	unit->m_2E0.set(9);
	unit->m_2FC.set(90);
	unit->m_2D4 = 5;
	Rva002A8AB1Record *record = TheSkirmishAIManager->rva002A8AB1(((void *)m_field24));
	if (record)
		record->rva002C717E(AIBasePenetrationTroopsTactic_IsRunning, 1);
	return true;
}
