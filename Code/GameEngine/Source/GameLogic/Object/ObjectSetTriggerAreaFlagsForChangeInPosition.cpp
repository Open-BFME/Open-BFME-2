// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?setTriggerAreaFlagsForChangeInPosition@Object@@QAEXXZ, retail 0x00291EB1
// (1016 bytes), one caller (0x00292E57).  Zero Hour's
// Object::setTriggerAreaFlagsForChangeInPosition is the lead (its trigger-area
// walk, ICoord3D position latch at +0x3FC and "***WARNING - Too many nested
// trigger areas. ***" are all here; BFME 1 kept the body as assembly);
// WorldBuilder twin 0x00CCFFC0 (constants/strings).  BFME2 differences read
// from retail: projectile/inert kinds 25 and 89, four moving kinds notify
// TheTerrainLogic (0x00285193), an Object+0xA4 gate queues the pathfind cell
// change (after frame 3) and resamples the average ground height at +0x1C4
// around a template circle (+0x4BC/+0x4C8/+0x544), up to seven trigger infos
// at +0x3C0 with a null-trigger guard, and entered/exited events go to Lua
// (TheLuaScriptEngine 0x003360D2 with the trigger name) and to the trigger
// (0x002E3777 / 0x002E3794).
// class-gate: allow GameLogic canonical view lacks QueueForNotifyPathfindCellChanged (0x00241C25) and the +0x180 trigger-change frame this body writes
#include <math.h>
#include "ascii_string.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;
struct Coord3D;

class ICoord3D
{
public:
	Int x, y, z;
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	void updateObjectsChangedTriggerAreas() { m_frameObjectsChangedTriggerAreas = m_frame; }
	void QueueForNotifyPathfindCellChanged(Object *obj);	// 0x00241C25
private:
	char m_pad00[0x40];
	UnsignedInt m_frame;	// +0x40
	char m_pad44[0x180 - 0x44];
	UnsignedInt m_frameObjectsChangedTriggerAreas;	// +0x180
};
extern GameLogic *TheGameLogic;

template <int N> class Rva00291EB1Slots : public Rva00291EB1Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class Rva00291EB1Slots<0>
{
};

class TerrainLogic : public Rva00291EB1Slots<7>
{
public:
	virtual Real getLayerHeight(Real x, Real y, Int layer, Coord3D *normal, Bool clip);	// slot 7
	void rva00285193(Object *obj);	// 0x00285193
};
extern TerrainLogic *TheTerrainLogic;

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &strMsg, Bool mustPause);	// 0x00205263
};
extern ScriptEngine *TheScriptEngine;

class Rva0036CA00Str;
class Rva001BDA20
{
public:
	void set(const Rva0036CA00Str &name);	// 0x000B28A5
};

struct BfmeDelayedLuaEvent
{
	unsigned char m_data[0x18];
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();
	void *m_vtable;
	BfmeDelayedLuaEvent m_events[3];
};

class BfmeObjectEventDispatch
{
public:
	void rva003360D2(Int index, void *object, BfmeDelayedLuaEventList *eventList);	// 0x003360D2
};

class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

// The trigger's entered/exited notifications, rowed under an address-named view.
class Rva002E3766Holder
{
public:
	void Rva002E3794Invoke(Int obj);	// 0x002E3794
	void Rva002E3777Invoke(Int obj);	// 0x002E3777
};

class PolygonTrigger
{
public:
	Bool pointInTrigger(const ICoord3D &point);	// 0x002E3A13
	PolygonTrigger *getNext() { return m_nextPolygonTrigger; }
	const Rva0036CA00Str &getTriggerName() const { return *(const Rva0036CA00Str *)m_triggerName; }
private:
	unsigned char m_pad00[0x3C];
	PolygonTrigger *m_nextPolygonTrigger;	// +0x3C
	char m_triggerName[4];	// +0x40
};

class Rva002E373CHolder
{
public:
	PolygonTrigger *m_head;
};
extern Rva002E373CHolder *g_Va00DBD0F4;	// ThePolygonTriggerListPtr holder

class Team
{
public:
	void rva0039D8BA(Object *obj);	// 0x0039D8BA setEnteredExited
};

class Rva004DD843
{
public:
	bool rva004DE2ED();	// 0x004DE2ED
};

class ThingTemplate
{
public:
	Real rva00291EB1SampleRadius() const { return m_heightSampleRadius; }
	__forceinline UnsignedInt isKindOf(Int k) const { return m_kindOf[k >> 5] & (1U << (k & 0x1f)); }
	char m_pad000[0x108];
	UnsignedInt m_kindOf[8];	// +0x108
	char m_pad128[0x4BC - 0x128];
	Real m_4BC;	// +0x4BC
	char m_pad4C0[0x4C8 - 0x4C0];
	Real m_heightSampleRadius;	// +0x4C8
	char m_pad4CC[0x544 - 0x4CC];
	Int m_heightSampleCount;	// +0x544
};

enum
{
	MAX_TRIGGER_AREA_INFOS = 7
};

struct TTriggerInfo
{
	PolygonTrigger *pTrigger;	// +0x00
	Bool entered;	// +0x04
	Bool exited;	// +0x05
	Bool isInside;	// +0x06
};

struct Coord3DView
{
	Coord3DView() {}
	Coord3DView(const Coord3DView &p) : x(p.x), y(p.y), z(p.z) {}
	Real x, y, z;
};

class Object
{
public:
	void setTriggerAreaFlagsForChangeInPosition();
	const Coord3DView *getPosition() const { return (const Coord3DView *)&m_x; }
	void rva0028B2BF();	// 0x0028B2BF updateTriggerAreaFlags

	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline UnsignedInt isKindOf(Int k) const { return getTemplate()->isKindOf(k); }

private:
	void *m_vtable;
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Real m_x;	// +0x38
	Real m_y;	// +0x3C
	Real m_z;	// +0x40
	char m_pad044[0xA4 - 0x44];
	Rva004DD843 *m_a4;	// +0xA4
	char m_pad0A8[0x1C4 - 0xA8];
	Real m_averageGroundHeight;	// +0x1C4
	char m_pad1C8[0x304 - 0x1C8];
	Team *m_team;	// +0x304
	char m_pad308[0x3C0 - 0x308];
	TTriggerInfo m_triggerInfo[MAX_TRIGGER_AREA_INFOS];	// +0x3C0
	UnsignedInt m_enteredOrExitedFrame;	// +0x3F8
	ICoord3D m_iPos;	// +0x3FC
	Int m_layer;	// +0x408
	Int m_40C;	// +0x40C
	char m_pad410[0x43A - 0x410];
	signed char m_numTriggerAreasActive;	// +0x43A
};

void Object::setTriggerAreaFlagsForChangeInPosition()
{
	if (isKindOf(25) || isKindOf(89))
		return;

	ICoord3D iPos;
	Coord3DView pos = *getPosition();
	iPos.x = (Int)pos.x;
	iPos.y = (Int)pos.y;
	iPos.z = 0;
	if (m_iPos.x == iPos.x && m_iPos.y == iPos.y)
		return;

	if (!isKindOf(2))
	{
		if (isKindOf(8) || isKindOf(9) || isKindOf(11) || isKindOf(10))
			TheTerrainLogic->rva00285193(this);
	}

	if (m_a4 && m_a4->rva004DE2ED())
	{
		if (TheGameLogic->getFrame() > 3)
			TheGameLogic->QueueForNotifyPathfindCellChanged(this);
		if (getTemplate()->m_4BC > 0.0f)
		{
			m_averageGroundHeight = 0.0f;
			Real step = 6.282f / getTemplate()->m_heightSampleCount;
			Real angle = 0.0f;
			for (Int i = 0; i < getTemplate()->m_heightSampleCount; i++, angle += step)
			{
				Coord3DView pt;
				pt.x = cos(angle) * getTemplate()->rva00291EB1SampleRadius() + getPosition()->x;
				pt.y = sin(angle) * getTemplate()->rva00291EB1SampleRadius() + getPosition()->y;
				m_averageGroundHeight += TheTerrainLogic->getLayerHeight(pt.x, pt.y, m_40C, 0, true);
			}
			m_averageGroundHeight /= getTemplate()->m_heightSampleCount;
		}
	}

	UnsignedInt now = TheGameLogic->getFrame();
	if (m_enteredOrExitedFrame != 0 && m_enteredOrExitedFrame != now)
		rva0028B2BF();

	Int i;
	for (i = 0; i < m_numTriggerAreasActive; i++)
	{
		if (m_triggerInfo[i].pTrigger && !m_triggerInfo[i].pTrigger->pointInTrigger(m_iPos))
		{
			m_triggerInfo[i].isInside = false;
			m_triggerInfo[i].exited = true;
			m_enteredOrExitedFrame = now;
			if (m_team)
				m_team->rva0039D8BA(this);
			TheGameLogic->updateObjectsChangedTriggerAreas();
			BfmeDelayedLuaEventList events;
			((Rva001BDA20 *)&events.m_events[0])->set(m_triggerInfo[i].pTrigger->getTriggerName());
			((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva003360D2(5, this, &events);
			((Rva002E3766Holder *)m_triggerInfo[i].pTrigger)->Rva002E3794Invoke((Int)this);
		}
	}

	m_iPos = iPos;

	for (PolygonTrigger *pTrig = g_Va00DBD0F4->m_head; pTrig; pTrig = pTrig->getNext())
	{
		Bool skip = false;
		for (i = 0; i < m_numTriggerAreasActive; i++)
		{
			if (m_triggerInfo[i].pTrigger == pTrig)
			{
				skip = true;
				break;
			}
		}
		if (skip)
			continue;
		if (pTrig->pointInTrigger(m_iPos))
		{
			if (m_numTriggerAreasActive < MAX_TRIGGER_AREA_INFOS)
			{
				m_triggerInfo[m_numTriggerAreasActive].isInside = true;
				m_triggerInfo[m_numTriggerAreasActive].entered = true;
				m_triggerInfo[m_numTriggerAreasActive].exited = false;
				m_triggerInfo[m_numTriggerAreasActive].pTrigger = pTrig;
				m_enteredOrExitedFrame = now;
				if (m_team)
					m_team->rva0039D8BA(this);
				TheGameLogic->updateObjectsChangedTriggerAreas();
				++m_numTriggerAreasActive;
				BfmeDelayedLuaEventList events;
				((Rva001BDA20 *)&events.m_events[0])->set(m_triggerInfo[i].pTrigger->getTriggerName());
				((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva003360D2(3, this, &events);
				((Rva002E3766Holder *)pTrig)->Rva002E3777Invoke((Int)this);
			}
			else
			{
				static Bool didWarn = false;
				if (!didWarn)
				{
					didWarn = true;
					TheScriptEngine->AppendDebugMessage("***WARNING - Too many nested trigger areas. ***", true);
				}
			}
		}
	}
}
