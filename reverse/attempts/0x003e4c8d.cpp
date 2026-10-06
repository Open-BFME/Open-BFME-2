// ?evaluateDistanceBetweenObjects@ScriptConditions@@IAE_NPAVCondition@@@Z
// partial score=0.77 date=2026-10-06
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

private:
	unsigned char m_pad00[8];
	Int m_int;				// +0x08
	Real m_real;				// +0x0C
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

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *pUnitParm);	// 0x003588E7
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateHasEvaEventPlayedInLastNSeconds(const AsciiString &eventName, Real seconds);
	Bool evaluateDistanceBetweenObjects(Condition *pCondition);
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

// ScriptConditions::evaluateDistanceBetweenObjects, retail 0x003E4C8D
// (WorldBuilder name). Parameters: two named units, a Zero Hour comparison
// code and a distance.
Bool ScriptConditions::evaluateDistanceBetweenObjects(Condition *pCondition)
{
	Object *obj1 = TheScriptEngine->getUnitNamed(pCondition->getParameter(0));
	Object *obj2 = TheScriptEngine->getUnitNamed(pCondition->getParameter(1));
	if (obj1 == 0 || obj2 == 0)
		return false;

	Real dx = obj1->getPosition()->x - obj2->getPosition()->x;
	Real dy = obj1->getPosition()->y - obj2->getPosition()->y;
	Real dz = obj1->getPosition()->z - obj2->getPosition()->z;
	Coord3D delta;
	delta.x = dx;
	delta.y = dy;
	delta.z = dz;
	Real dist = delta.length();
	Real value = pCondition->getParameter(3)->getReal();
	switch (pCondition->getParameter(2)->getInt())
	{
	case Parameter::LESS_THAN:	if (!(dist < value)) return false; break;
	case Parameter::LESS_EQUAL:	if (!(dist <= value)) return false; break;
	case Parameter::EQUAL:		if (!(dist == value)) return false; break;
	case Parameter::GREATER_EQUAL:	if (!(dist >= value)) return false; break;
	case Parameter::GREATER:	if (!(dist > value)) return false; break;
	case Parameter::NOT_EQUAL:	if (!(dist != value)) return false; break;
	default:			return false;
	}
	return true;
}
