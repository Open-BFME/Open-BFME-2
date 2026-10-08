// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// stlport
//
// ?getCenter@AIGroup@@QAE_NPAUCoord3D@@@Z, retail 0x0036D035, 282B.
// Zero Hour AIGroup::getCenter (GameLogic/AI/AIGroup.cpp): centroid of the
// members that are not DISABLED_HELD and have an AI, falling back to every
// non-held member when none has one; returns count > 0.
// Target evidence: list<Object*> at this+4 (node next/prev/value at +0/+4/+8),
// disabled mask byte test 8 at Object+0x1C8, AIUpdateInterface at +0x258 (as
// AIGroupIsIdle.cpp), position at +0x38. BFME2 adds a call to the rowed
// Object gate 0x002907A1 before the AI test; retail divides each axis by the
// count (one reciprocal, three multiplies). Callers: 11 matched rows already
// reference this name.
#include <list>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

class AIUpdateInterface;

class Object
{
public:
	Bool rva002907A1();
	Bool isDisabledByHeld() const { return (m_disabledMask[0] & 8) != 0; }
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }

private:
	char m_pad0[0x38];
	Coord3D m_position;
	char m_pad44[0x1C8 - 0x44];
	unsigned char m_disabledMask[0x258 - 0x1C8];
	AIUpdateInterface *m_ai;
};

class AIGroup
{
public:
	Bool getCenter(Coord3D *center);

private:
	virtual ~AIGroup();
	std::list<Object *> m_memberList;
};

Bool AIGroup::getCenter(Coord3D *center)
{
	Int count = 0;
	center->x = 0.0f;
	center->y = 0.0f;
	center->z = 0.0f;

	std::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		if ((*i)->isDisabledByHeld())
			continue;	// don't bother counting riders in the center calculation
		if (!(*i)->rva002907A1())
			continue;
		AIUpdateInterface *ai = (*i)->getAIUpdateInterface();
		if (ai)
		{
			const Coord3D *objPos = (*i)->getPosition();
			center->x += objPos->x;
			center->y += objPos->y;
			center->z += objPos->z;
			++count;
		}
	}

	if (count == 0 && !m_memberList.empty())
	{
		for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
		{
			if ((*i)->isDisabledByHeld())
				continue;	// don't bother counting riders in the center calculation
			const Coord3D *objPos = (*i)->getPosition();
			center->x = objPos->x + center->x;
			center->y += objPos->y;
			center->z += objPos->z;
			++count;
		}
	}

	center->x /= count;
	center->y /= count;
	center->z /= count;
	return count > 0;
}
