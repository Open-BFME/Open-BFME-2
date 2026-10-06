// ?evaluateSkirmishCanFireSpecialPowerOnTeam@ScriptConditions@@IAE_NPAVParameter@@00@Z
// partial score=0.53 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// ScriptConditions.cpp -- condition evaluators recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names each function and
// its source file; retail supplies the bytes. The evaluators are thiscall
// members that mostly ignore `this`.
#include <math.h>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// Zero Hour BaseType.h conversions; BFME2's ceil goes through the CRT.
__forceinline float fast_float_ceil(float f)
{
	return (float)ceil((double)f);
}

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_CEIL(x) (fast_float2long_round(fast_float_ceil(x)))

extern Int g_Va00DBA4E4;	// logic frames per second
#define LOGICFRAMES_PER_SECOND g_Va00DBA4E4
extern Real g_Va00DBA4EC;	// logic frames per millisecond (0.005)
#define LOGICFRAMES_PER_MSEC_REAL g_Va00DBA4EC

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame;			// +0x40
};

extern GameLogic *TheGameLogic;

class Eva
{
public:
	Int rva001DE78E(const AsciiString *name);	// 0x001DE78E, event index or -1
	Bool getLastReallyPlayedFrameForEvaEvent(Int index, UnsignedInt *frame);	// 0x001DD604
};

extern Eva *g_00DFDC30;	// TheEva
#define TheEva g_00DFDC30

struct Coord3D
{
	Real length() const;			// 0x00003571
	void set(Real ax, Real ay, Real az) { x = ax; y = ay; z = az; }

	Real x, y, z;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }

private:
	unsigned char m_pad00[0x38];
	Coord3D m_pos;				// +0x38
};

class Parameter
{
public:
	// Zero Hour's comparison codes.
	enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };

	Int getInt() const { return m_int; }
	Real getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }

	unsigned char m_pad00[8];
	Int m_int;				// +0x08
	Real m_real;				// +0x0C
	AsciiString m_string;			// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	Int m_field20;				// +0x20, set to -1 when the special power name is unknown
};

class Condition
{
public:
	Parameter *getParameter(Int ndx) const { if (ndx >= 0 && ndx < m_numParms) return m_parms[ndx]; return 0; }

private:
	unsigned char m_pad00[8];
	Int m_numParms;				// +0x08
	Parameter *m_parms[12];			// +0x0C
};

class Team
{
public:
	Bool hasAnyObjects(Bool ignoreBuildings);		// 0x0039E042
	Coord3D *rva0039DA2A(Coord3D *center) const;		// 0x0039DA2A, centroid
};

class Player
{
public:
	Object *rva002AC629();				// 0x002AC629
};

class PlayerList
{
public:
	Player *getPlayerFromMask(Int mask);		// 0x002A7B91
};

extern PlayerList *ThePlayerList;

class SpecialPowerTemplate;

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);	// 0x0029B6EB
};

extern SpecialPowerStore *g_00E02D4C;
#define TheSpecialPowerStore g_00E02D4C

enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT, CMD_FROM_AI };

class ActionManager
{
public:
	Bool canDoSpecialPowerAtLocation(const Object *obj, const Coord3D *loc, CommandSourceType commandSource,
		const SpecialPowerTemplate *spTemplate, const Object *objectInWay, UnsignedInt commandOptions,
		Bool checkSourceRequirements = true);		// 0x0041D60B
};

extern ActionManager *TheActionManager;

struct TCounter
{
	Int value;
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *pUnitParm);	// 0x003588E7
	Int rva00357B82(Parameter *pPlayerParm);		// 0x00357B82, player mask from a parameter
	Team *getTeamNamed(AsciiString teamName, Bool flag);	// 0x003584E9
	void *rva002086C5(AsciiString counterName);	// 0x002086C5, Zero Hour getCounter (returns TCounter *)
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateHasEvaEventPlayedInLastNSeconds(const AsciiString &eventName, Real seconds);
	Bool evaluateCounterSeconds(Condition *pCondition);
	Bool evaluateSkirmishCanFireSpecialPowerOnTeam(Parameter *pSkirmishPlayerParm, Parameter *pSpecialPowerParm, Parameter *pTeamParm);
};

// ScriptConditions::evaluateHasEvaEventPlayedInLastNSeconds, retail 0x003E543A
// (WorldBuilder name; BFME2-only condition).
Bool ScriptConditions::evaluateHasEvaEventPlayedInLastNSeconds(const AsciiString &eventName, Real seconds)
{
	Int frames = REAL_TO_INT_CEIL(LOGICFRAMES_PER_SECOND * seconds);
	Int index = TheEva->rva001DE78E(&eventName);
	UnsignedInt lastFrame;
	if (index == -1)
		return false;
	if (!TheEva->getLastReallyPlayedFrameForEvaEvent(index, &lastFrame))
		return false;
	return TheGameLogic->getFrame() - lastFrame <= (UnsignedInt)frames;
}


// ScriptConditions::evaluateCounterSeconds, retail 0x003E7D83 (WorldBuilder
// name): Zero Hour's evaluateCounter with the threshold given in seconds.
Bool ScriptConditions::evaluateCounterSeconds(Condition *pCondition)
{
	Int value = 0;
	TCounter *pCounter = (TCounter *)TheScriptEngine->rva002086C5(pCondition->getParameter(0)->getString());
	if (pCounter)
		value = pCounter->value;
	Int frames = REAL_TO_INT_CEIL(LOGICFRAMES_PER_MSEC_REAL * pCondition->getParameter(2)->getReal() * 1000.0f);
	switch (pCondition->getParameter(1)->getInt())
	{
	case Parameter::LESS_THAN:	return value < frames;
	case Parameter::LESS_EQUAL:	return value <= frames;
	case Parameter::EQUAL:		return value == frames;
	case Parameter::GREATER_EQUAL:	return value >= frames;
	case Parameter::GREATER:	return value > frames;
	case Parameter::NOT_EQUAL:	return value != frames;
	}
	return false;
}

// ScriptConditions::evaluateSkirmishCanFireSpecialPowerOnTeam, retail
// 0x003E91F6 (WorldBuilder name; BFME2-only condition).
Bool ScriptConditions::evaluateSkirmishCanFireSpecialPowerOnTeam(Parameter *pSkirmishPlayerParm,
	Parameter *pSpecialPowerParm, Parameter *pTeamParm)
{
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357B82(pSkirmishPlayerParm));
	if (player == 0)
		return false;
	Object *obj = player->rva002AC629();
	if (obj == 0)
		return false;
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(pSpecialPowerParm->getString());
	if (power == 0)
	{
		pSpecialPowerParm->m_field20 = -1;
		return false;
	}
	Team *team = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (team == 0 || !team->hasAnyObjects(false))
		return false;
	Coord3D pos;
	return TheActionManager->canDoSpecialPowerAtLocation(obj, team->rva0039DA2A(&pos), CMD_FROM_AI, power, 0, 0, true);
}
