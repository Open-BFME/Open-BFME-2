// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
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
//   0x005A9A89  slot 3 (not here yet): flag the unit (+0x2E0 / +0x307
//               bits, +0x2D4 = 5) and set the flag
//   0x005A9916  slot 6: 0x004ED372 with the +0x20 record's +0x0C point
//   0x005A9923  slot 7: while running (+0x10), stop (0x004ED748(1, 0)) when
//               0x004ED169 says so or the +0x20 record is flagged at +0x18
#include "ascii_string.h"

// Retail's initializer calls AsciiString's out-of-line const char * ctor
// (0x0000654A) rather than expanding it, so inline expansion is off here.
#pragma inline_depth(0)
AsciiString AIBasePenetrationTroopsTactic_IsRunning("AIBasePenetrationTroopsTactic_IsRunning");
#pragma inline_depth()

// The engine's float helpers (fast_float_floor / fast_float2long_round).
extern "C" __declspec(dllimport) double __cdecl floor(double);

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

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

struct Rva005A990BThing
{
	char m_pad000[0x120];
	unsigned char m_120;
};

class Object
{
public:
	char m_pad000[4];
	Rva005A990BThing *m_04;
	char m_pad008[0x94 - 8];
	unsigned char m_94;
	char m_pad095[0x438 - 0x95];
	unsigned char m_438;
};

class Rva002C589B
{
public:
	Object *rva002C5DA6();
};

struct Rva005A990BUnit;

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(Rva005A990BUnit *unit, void *unused);
	virtual void v4(); virtual void v5();
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
	unsigned char rva004ED169();
	void rva004ED372(void *point);
	void end(bool a, bool b);
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	unsigned char checkTarget(void *request);
	char m_pad04[0x10 - 4];
	bool m_running;			// +0x10
	char m_pad11[0x20 - 0x11];
	Rva005A990BRecord *m_record;	// +0x20
	void *m_owner;			// +0x24
	char m_pad28[0x58 - 0x28];
};

class AIBasePenetrationTroopsTactic : public AITacticOffensive
{
public:
	virtual ~AIBasePenetrationTroopsTactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual void run();
	virtual void update();
};

bool AIBasePenetrationTroopsTactic::canRun(void *request)
{
	Rva002A8AB1Record *running = g_00DFEEF8->rva002A8AB1(m_owner);
	if (running->rva002C7196(AIBasePenetrationTroopsTactic_IsRunning))
		return false;
	if (!checkTarget(request))
		return false;
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	if (!record || record->m_16C < 1)
		return false;
	Object *obj = ((Rva002C589B *)request)->rva002C5DA6();
	if (!obj)
		return false;
	if ((obj->m_04->m_120 & 4) && !(obj->m_94 & 1) && !(obj->m_438 & 1))
		return true;
	return false;
}

void AIBasePenetrationTroopsTactic::cleanUp()
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	if (record)
		record->rva002C717E(AIBasePenetrationTroopsTactic_IsRunning, 0);
}

void AIBasePenetrationTroopsTactic::run()
{
	rva004ED372(m_record->m_point0C);
}

void AIBasePenetrationTroopsTactic::update()
{
	if (m_running && (m_record->m_18 || rva004ED169()))
		end(1, 0);
}
