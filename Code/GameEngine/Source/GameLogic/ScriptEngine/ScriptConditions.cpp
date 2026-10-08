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

#include "../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class Eva
{
public:
	Int rva001DE78E(const AsciiString *name);	// 0x001DE78E, event index or -1
	Bool getLastReallyPlayedFrameForEvaEvent(Int index, UnsignedInt *frame);	// 0x001DD604
};

extern Eva *TheEva;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Rva00261C89
{
public:
	Bool rva00261C89();			// 0x00261C89
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	Rva00261C89 *getField04() const { return m_field04; }

private:
	unsigned char m_pad00[4];
	Rva00261C89 *m_field04;			// +0x04
	unsigned char m_pad08[0x38 - 8];
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
	Int iterateObjects(Int (*func)(Object *obj, void *userData), void *userData) const;	// 0x002AB08B
};

class PlayerList
{
public:
	Player *getPlayerFromMask(Int mask);		// 0x002A7B91
	Player *getEachPlayerFromMask(Int &mask);	// 0x002A7BC9
};

// Distance-count callback data; its constructor (0x003E5563) zeroes the
// position, threshold and count and sets the cap to 0x7ffffffe.
class Rva003E5563
{
public:
	Rva003E5563();

	Coord3D m_pos;				// +0x00
	Real m_distSqr;				// +0x0C
	Int m_count;				// +0x10
	Int m_max;				// +0x14
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

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *pUnitParm);	// 0x003588E7
	Int rva00357B82(Parameter *pPlayerParm);		// 0x00357B82, player mask from a parameter
	Team *getTeamNamed(AsciiString teamName, Bool flag);	// 0x003584E9
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateHasEvaEventPlayedInLastNSeconds(const AsciiString &eventName, Real seconds);
	Bool evaluatePlayerHasNumberUnitsDistanceFromObject(Parameter *pPlayerParm, Parameter *pComparisonParm,
		Parameter *pCountParm, Parameter *pDistanceParm, Parameter *pObjectParm);
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



// Player::iterateObjects callback, retail 0x003E6032 (rowed under its
// address name in ScriptConditions_evaluateNamedInsideArea.cpp): counts
// qualifying objects farther than the threshold from the position and stops
// once the count passes the cap.
struct Rva003E6032Context;
int Rva003E6032(Object *object, Rva003E6032Context *context);

// ScriptConditions::evaluatePlayerHasNumberUnitsDistanceFromObject, retail
// 0x003E609F (WorldBuilder name; BFME2-only condition).
Bool ScriptConditions::evaluatePlayerHasNumberUnitsDistanceFromObject(Parameter *pPlayerParm,
	Parameter *pComparisonParm, Parameter *pCountParm, Parameter *pDistanceParm, Parameter *pObjectParm)
{
	Int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	Int count = pCountParm->getInt();
	Rva003E5563 data;
	Real dist = pDistanceParm->getReal();
	if (dist < 0.0f)
		dist = 0.0f;
	data.m_distSqr = dist * dist;
	data.m_max = count;
	Object *obj = TheScriptEngine->getUnitNamed(pObjectParm);
	if (obj)
	{
		data.m_pos = *obj->getPosition();
	}
	else
	{
		data.m_pos.x = 0.0f;
		data.m_pos.y = 0.0f;
		data.m_pos.z = 0.0f;
		data.m_distSqr = -1.0f;
	}
	while (mask && data.m_count <= count)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->iterateObjects((Int (*)(Object *, void *))Rva003E6032, &data);
	}
	Bool result;
	switch (pComparisonParm->getInt())
	{
	case Parameter::LESS_THAN:	result = data.m_count < count; break;
	case Parameter::LESS_EQUAL:	result = data.m_count <= count; break;
	case Parameter::EQUAL:		result = data.m_count == count; break;
	case Parameter::GREATER_EQUAL:	result = data.m_count >= count; break;
	case Parameter::GREATER:	result = data.m_count > count; break;
	case Parameter::NOT_EQUAL:	result = data.m_count != count; break;
	default:			result = false; break;
	}
	return result;
}
