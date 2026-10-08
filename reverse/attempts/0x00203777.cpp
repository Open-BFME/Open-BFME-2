// ?setFade@ScriptEngine@@IAEXPAVScriptAction@@@Z
// partial score=1.0 date=2026-10-08
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

struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
	bool m_isMillisecondTimer;
};

class ScriptAction
{
public:
    enum FadeActionType {
        CAMERA_FADE_ADD = 0x7C, CAMERA_FADE_SUBTRACT,
        CAMERA_FADE_SATURATE, CAMERA_FADE_MULTIPLY
    };
    int getActionType() const { return m_actionType; }
	Parameter *getParameter(int ndx)
	{
		if (ndx >= 0 && ndx < m_numParms)
			return m_parms[ndx];
		return 0;
	}

private:
	char m_unknown[4];
	int m_actionType;
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
	bool evaluateTimer(Condition *condition);
	bool evaluateFlag(Condition *condition);

protected:
    enum TFade { FADE_NONE, FADE_SUBTRACT, FADE_ADD, FADE_SATURATE, FADE_MULTIPLY };
    void setFade(ScriptAction *action);
    void updateFades();
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
	unsigned char m_unreconstructed17620[0x1a138 - 0x17620];
    int m_fade;
    bool m_fadeActive;
    float m_minFade;
    float m_maxFade;
    float m_curFadeValue;
    int m_curFadeFrame;
    int m_fadeFramesIncrease;
    int m_fadeFramesHold;
    int m_fadeFramesDecrease;
    unsigned char m_unreconstructed1A15C[0x1a264 - 0x1a15c];
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

// ZH ScriptEngine.cpp setFade supplies the action purpose and field names.
// WB setFade 0x00B38B70 and retail 0x00203777..0x0020385F establish
// action values 0x7C..0x7F and the fade block at +0x1A138. BFME's active
// flag is raised after the optional first interpolation, as seen in WB
// and retail. The interpolation helper remains separately unrecovered.
void ScriptEngine::setFade(ScriptAction *pAction)
{
    switch (pAction->getActionType())
    {
        default: m_fade = FADE_NONE; return;
        case ScriptAction::CAMERA_FADE_ADD: m_fade = FADE_ADD; break;
        case ScriptAction::CAMERA_FADE_SUBTRACT: m_fade = FADE_SUBTRACT; break;
        case ScriptAction::CAMERA_FADE_SATURATE: m_fade = FADE_SATURATE; break;
        case ScriptAction::CAMERA_FADE_MULTIPLY: m_fade = FADE_MULTIPLY; break;
    }
    m_curFadeFrame = 0;
    m_minFade = pAction->getParameter(0)->m_real;
    m_maxFade = pAction->getParameter(1)->m_real;
    m_fadeFramesIncrease = pAction->getParameter(2)->m_int;
    m_fadeFramesHold = pAction->getParameter(3)->m_int;
    m_fadeFramesDecrease = pAction->getParameter(4)->m_int;
    m_curFadeValue = m_minFade;
    if (m_fadeFramesIncrease == 0)
        updateFades();
    m_fadeActive = true;
}

// ?updateFades@ScriptEngine@@IAEXXZ
void ScriptEngine::updateFades(void)
{
	m_curFadeFrame++;
	int fade = m_curFadeFrame;
	m_fadeActive = false;
	float factor;
	if (fade <= m_fadeFramesIncrease)
	{
		factor = (float)m_curFadeFrame / m_fadeFramesIncrease;
		m_curFadeValue = m_minFade + factor * (m_maxFade - m_minFade);
		return;
	}
	fade -= m_fadeFramesIncrease;
	if (fade <= m_fadeFramesHold)
	{
		m_curFadeValue = m_maxFade;
		return;
	}
	fade -= m_fadeFramesHold;
	if (fade <= m_fadeFramesDecrease)
	{
		int divisor = m_fadeFramesDecrease + 1;
		if (divisor == 0)
			divisor = 1;
		factor = (float)fade / divisor;
		m_curFadeValue = m_maxFade + factor * (m_minFade - m_maxFade);
		return;
	}
	m_fade = FADE_NONE;
}
