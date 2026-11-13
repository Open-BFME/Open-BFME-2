// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsCounters.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: ScriptActions::doCounterMathCounter 0x003C2950 (128B),
// ScriptActions::doCounterMathValue 0x003C29D0 (89B). Callee addresses are
// read off retail's call sites (reverse/symbols.csv). Only the placed bodies
// are carried; the donor's other definitions are omitted.
// Every ScriptActions action whose whole job is to work out one number and
// store it in a named script counter:
//
//   0x002F6330  doCounterMathCounter                COUNTER_MATH_COUNTER
//   0x002F6410  doCounterMathValue                  COUNTER_MATH_VALUE
//   0x002F6550  doSetPlayerMoneyToCounter           SET_PLAYER_MONEY_TO_COUNTER
//   0x002F65E0  doSetPlayerLightPointsToCounter     SET_PLAYER_LIGHT_POINTS_TO_COUNTER
//   0x002F6670  doSetUnitExperienceToCounter        SET_UNIT_EXPERIENCE_TO_COUNTER
//   0x002F66E0  doSetPlayerCommandPointsUsedToCounter
//   0x002F6760  doSetPlayerCommandPointsAvailableToCounter
//   0x002F67E0  doSetPlayerCommandPointsTotalToCounter
//   0x002F6920  doSetPlayerKillsOfTypeToCounter     SET_PLAYER_KILLS_OF_TYPE_TO_COUNTER
//   0x002F69B0  doSetCounterToNumberObjectsPlayerOwnesWithModelCondition
//
// All ten end the same way -- ScriptEngine::bfmeCounter on the counter name,
// then a store into ScriptCounter::m_value -- and differ only in where the
// number comes from, so they share every model declared here.

#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <string.h>
#include "ascii_string.h"

#pragma intrinsic(memcmp)

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Player;
class ScriptActions;

// The counter a script names. Only doCounterMathCounter looks past m_value, at
// the countdown-timer flag that tells a timer from a plain counter.
#include "../../../Include/GameLogic/ScriptCounter.h"

#include "../../../Include/GameLogic/ScriptEngine.h"

// Reached by casting TheScriptEngine: the mask helper is not a slot.
class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	unsigned short getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
#include "../../../Include/Common/PlayerList.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
#include "../../../Include/GameLogic/ScriptParameter.h"

class PlayerCommandPoints
{
};

class PlayerLightPoints
{
};

// PlayerKills uses the retail StringBase layout here: the generated body reads
// a ushort length at data+4 and compares data+8 inline.  The caller-side
// AsciiString remains the canonical StringInline ABI; this view is only the
// BFME PlayerKills member access proved by 0x000E9B20 and the named counter
// caller at 0x002F6920.
struct BfmePlayerKillsStringData
{
	char m_pad00[4];
	unsigned short m_length;
	unsigned short m_pad06;
	char m_text[1];
};

class BfmePlayerKillsStringView
{
public:
	Int compare(const BfmePlayerKillsStringView &other) const
	{
		const BfmePlayerKillsStringView *that = &other;
		const BfmePlayerKillsStringView *self = this;
		Int thatLen = that->m_data ? that->m_data->m_length : 0;
		const char *thatData = that->m_data ? &that->m_data->m_text[0] : "";
		Int thisLen = self->m_data ? self->m_data->m_length : 0;
		const char *thisData = self->m_data ? &self->m_data->m_text[0] : "";
		Int c = memcmp(thisData, thatData,
			(unsigned int)(thisLen < thatLen ? thisLen : thatLen));
		if (c != 0)
			return c;
		return thisLen - thatLen;
	}

	BfmePlayerKillsStringData *m_data;
};

// GameLogic's buildable override and the retail body both place the
// ThingTemplate name at +0x20.  PlayerKills owns 32 adjacent map objects;
// each STLport map is the 12-byte header walked by the retail outer loop.
class BfmePlayerKillsThingTemplateView
{
public:
	char m_beforeName[0x20];
	BfmePlayerKillsStringView m_name;
};

typedef _STL::map<const BfmePlayerKillsThingTemplateView *, Int>
	BfmePlayerKillsMap;

struct PlayerKills
{
	Int getKillsOfType(const AsciiString &objectType);

private:
	char m_beforeKills[0x150];
	BfmePlayerKillsMap m_kills[0x20];
};


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
#include "../../../Include/Common/Player.h"

struct UnitExperience
{
	unsigned char m_beforeExperience[0xc];
	float m_experience;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	unsigned char m_beforeExperience[0x210];

public:
	UnitExperience *m_experience;
};

extern PlayerList *ThePlayerList;

extern void j_000142b3();
extern void j_00047d34();
extern void j_0003deb0();
extern void j_0001af23();
extern void j_00004e3f();
extern void j_00020dc9();

// The 288-entry ModelConditionFlags name table is reached through the retail
// ILT shared by the already-converted BitFlags setter at 0x001C62B0.
extern Int bfmeLookup_001c62b0(void *name);

struct BfmeCommandPointsCall
{
	Int call(Int includeReserved);
};

struct BfmeTotalCommandPointsCall
{
	Int call();
};


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"

void ScriptActions::doCounterMathCounter(Parameter *counter,
	Parameter *operation, Parameter *otherCounter)
{
	ScriptCounter *destination;
	int result;
	const ScriptCounter *source;
	destination = TheScriptEngine->bfmeCounter(counter->getString());
	result = destination->m_value;
	int value;
	value = 0;
	source = (const ScriptCounter *)TheScriptEngine->rva002086C5(otherCounter->getString());
	if (source)
		value = source->m_value;

	switch (operation->getInt())
	{
	case 0:
		result += value;
		break;
	case 1:
		result -= value;
		break;
	case 2:
		result *= value;
		break;
	case 3:
		result /= value;
		break;
	}
	destination->m_value = result;
}

void ScriptActions::doCounterMathValue(Parameter *counter,
	Parameter *operation, Parameter *value)
{
	ScriptCounter *destination = TheScriptEngine->bfmeCounter(
		counter->getString());
	int result = destination->m_value;
	int operand = value->getInt();

	switch (operation->getInt())
	{
	case 0:
		result += operand;
		break;
	case 1:
		result -= operand;
		break;
	case 2:
		result *= operand;
		break;
	case 3:
		result /= operand;
		break;
	}
	destination->m_value = result;
}


