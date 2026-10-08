// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ScriptEngine::evaluateTimer 0x00209486 (69B), ScriptEngine::restartTimer
// 0x002095FF (58B), ScriptEngine::pauseTimer 0x002095CA (53B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.

// FILE: ScriptEngine.cpp /////////////////////////////////////////////////////
//
// Recovered ScriptEngine bodies share the original TU named by the timer
// cluster's embedded retail source path. The class stays local and partial;
// pulling in ScriptEngine.h would expose the unreconstructed GameLogic graph.
//
///////////////////////////////////////////////////////////////////////////////

#include "StringInline.h"
#include "Common/LatchRestore.h"

typedef float Real;

extern "C" float __cdecl sinf(float);
extern "C" float __cdecl cosf(float);
extern "C" __declspec(dllimport) double __cdecl ceil(double);
int GetGameLogicRandomValue(int low, int high, char *file, int line);
unsigned long Rva003ECA13Get(const AsciiString &name);	// 0x003ECA13, the name's CRC

// The STLport list of flag-name CRCs at ScriptEngine+0x1A264 (header node).
struct ScriptFlagKeyNode
{
	ScriptFlagKeyNode *m_next;
	ScriptFlagKeyNode *m_prev;
	unsigned long m_key;
};


class Parameter
{
public:
	char m_unknown[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};


class Condition
{
public:
	enum ConditionType
	{
		CONDITION_FALSE = 0,
		COUNTER,
		FLAG,
		CONDITION_TRUE,
		TIMER_EXPIRED
	};

	Parameter *getParameter(int ndx)
	{
		if (ndx >= 0 && ndx < m_numParms)
			return m_parms[ndx];
		return 0;
	}
	ConditionType getConditionType() const { return m_conditionType; }
	int rva003B275A();	// 0x003B275A, the condition template's mode mask
	Condition *getNext() const { return m_nextAndCondition; }
	bool isEnabled() const { return m_enabled; }

private:
	char m_unknown[4];
	ConditionType m_conditionType;	// +0x04
	int m_numParms;
	Parameter *m_parms[12];
	Condition *m_nextAndCondition;	// +0x3C
	char m_unknown40[0x4C - 0x40];
	bool m_enabled;		// +0x4C, Script::getUiText shows " (DISABLED) " when clear
};

class OrCondition
{
public:
	OrCondition *getNextOrCondition() const { return m_nextOr; }
	Condition *getFirstAndCondition() const { return m_firstAnd; }

private:
	void *m_vtable;
	OrCondition *m_nextOr;			// +0x04
	Condition *m_firstAnd;			// +0x08
};

class Script
{
public:
	OrCondition *getOrCondition() const { return m_condition; }

private:
	char m_unknown[0x30];
	OrCondition *m_condition;		// +0x30
};

class Player;

class Team
{
public:
	Player *getControllingPlayer() const;
};

// TheScriptConditions 0x00A02E04: slot 14 evaluates the other condition types
// (Zero Hour's ScriptConditionsInterface::evaluateCondition).
class ScriptConditions
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual bool evaluateCondition(Condition *pCondition);	// +0x38
};
extern ScriptConditions *TheScriptConditions;

struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
	bool m_isMillisecondTimer;
};

class ScriptAction
{
public:
	Parameter *getParameter(int ndx)
	{
		if (ndx >= 0 && ndx < m_numParms)
			return m_parms[ndx];
		return 0;
	}

private:
	char m_unknown[8];
	int m_numParms;
	Parameter *m_parms[12];
};

#include "../../../../Libraries/Include/Lib/Coord2D.h"

struct BreezeInfo
{
	float m_direction;
	Coord2D m_directionVec;
	float m_intensity;
	float m_lean;
	float m_randomness;
	short m_breezePeriod;
	short m_breezeVersion;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	AsciiString getStats( Real *curTimePtr, Real *script1Time, Real *script2Time );
	bool evaluateConditions(Script *pScript, Team *thisTeam, Player *player);
	bool evaluateTimer(Condition *condition);
	bool evaluateFlag(Condition *condition);
	int rva00203693();	// 0x00203693, current mode mask (2 or 1)

protected:
	bool evaluateCounter(Condition *pCondition);	// 0x00208F61
	bool evaluateCondition(Condition *pCondition);
	void setSway(ScriptAction *pAction);
	ScriptCounter *bfmeCounter(AsciiString name);
	bool *bfmeFlagForWrite(AsciiString name);		// 0x002088A0
	void setTimer(ScriptAction *action, bool millisecondTimer, bool random);
	void pauseTimer(ScriptAction *action);
	void restartTimer(ScriptAction *action);
	void adjustTimer(ScriptAction *action, bool millisecondTimer, bool add);

private:
	unsigned char m_unreconstructed[0x17604];
	BreezeInfo m_breezeInfo;
	unsigned char m_unreconstructed17620[0x1a110 - 0x17620];
	Team *m_callingTeam;						// +0x1A110
	unsigned char m_unreconstructed1A114[0x1a130 - 0x1a114];
	Player *m_currentPlayer;					// +0x1A130
	unsigned char m_unreconstructed1A134[0x1a264 - 0x1a134];
	ScriptFlagKeyNode *m_flagKeys;				// +0x1A264, list header
};

// GLOBALS (ZH ScriptEngine.cpp:143, the one definition in the game's ZH source)
extern ScriptEngine *TheScriptEngine;


bool ScriptEngine::evaluateTimer(Condition *condition)
{
	ScriptCounter *counter = bfmeCounter(condition->getParameter(0)->m_string);
	if (!counter->m_isCountdownTimer)
		return false;
	return counter->m_value < 1;
}


void ScriptEngine::pauseTimer(ScriptAction *action)
{
	bfmeCounter(action->getParameter(0)->m_string)->m_isCountdownTimer = false;
}

void ScriptEngine::restartTimer(ScriptAction *action)
{
	ScriptCounter *counter = bfmeCounter(action->getParameter(0)->m_string);
	if (counter->m_value > 0)
		counter->m_isCountdownTimer = true;
}

// ScriptEngine::evaluateFlag, retail 0x00209382: WB's name for Zero Hour's
// flag condition. True when the flag already holds the wanted value, else
// when the flag's name CRC is listed at +0x1A264.
bool ScriptEngine::evaluateFlag(Condition *condition)
{
	bool *flag = bfmeFlagForWrite(condition->getParameter(0)->m_string);
	bool wanted = condition->getParameter(1)->m_int != 0;
	bool current = *flag != 0;
	if (wanted == current)
		return true;
	unsigned long key = Rva003ECA13Get(condition->getParameter(0)->m_string);
	for (ScriptFlagKeyNode *node = m_flagKeys->m_next; node != m_flagKeys; node = node->m_next)
	{
		if (node->m_key == key)
			return true;
	}
	return false;
}

// ScriptEngine::evaluateCondition, retail 0x002096E2 (102B): Zero Hour's
// switch (ScriptEngine.cpp:7059) behind BFME2's test of the condition's mode
// mask (0x003B275A) against the engine's (0x00203693), the executeActions
// test's shape.
bool ScriptEngine::evaluateCondition(Condition *pCondition)
{
	if ((pCondition->rva003B275A() & rva00203693()) == 0)
		return false;
	switch (pCondition->getConditionType()) {
		default:
			return TheScriptConditions->evaluateCondition(pCondition);
		case Condition::CONDITION_FALSE: return false;
		case Condition::CONDITION_TRUE: return true;
		case Condition::COUNTER: return evaluateCounter(pCondition);
		case Condition::FLAG: return evaluateFlag(pCondition);
		case Condition::TIMER_EXPIRED: return evaluateTimer(pCondition);
	}
}

// The script latches' out-of-line members: LatchRestore<Team *> ctor 0x00203CA8,
// dtor 0x00203CC7 and scalar deleting dtor 0x00203D04 (vtable 0x00BE39EC);
// LatchRestore<Player *> ctor 0x00203CD6, dtor 0x00203CF5 and scalar deleting
// dtor 0x00203D29 (vtable 0x00BE39F0).
template class LatchRestore<Team*>;
template class LatchRestore<Player*>;

// ScriptEngine::evaluateConditions, retail 0x00209748 (201B): Zero Hour's
// (ScriptEngine.cpp:7582) with BFME2's test that skips a disabled condition.
// The latches' vtables are LatchRestore<Team *> 0x00BE39EC and
// LatchRestore<Player *> 0x00BE39F0.
bool ScriptEngine::evaluateConditions(Script *pScript, Team *thisTeam, Player *player)
{
	LatchRestore<Team*> latch(m_callingTeam, thisTeam);
	if (thisTeam) player = thisTeam->getControllingPlayer();
	if (player==0) player=m_currentPlayer;
	LatchRestore<Player*> latch2(m_currentPlayer, player);
	OrCondition *pConditionHead = pScript->getOrCondition();
	bool testValue = false;

	OrCondition *pCurCondition;
	for (pCurCondition = pConditionHead; pCurCondition; pCurCondition = pCurCondition->getNextOrCondition()) {
		Condition *pCondition = pCurCondition->getFirstAndCondition();
		if (!pCondition) continue; // No conditions, so go to the next or.
		bool andTerm = true;
		while (pCondition && andTerm) {
			if (pCondition->isEnabled() && !evaluateCondition(pCondition)) {
				andTerm = false;
				break; // Short circuit the and evauation - after the first false, we can quit.
			}
			pCondition = pCondition->getNext();
		}
		if (andTerm) { // The outer list is OR'ed - so any true inner means we are true.
			testValue = true;
			break;
		}
	}

	return testValue; // If none of the or's fired, then it is false.
}
