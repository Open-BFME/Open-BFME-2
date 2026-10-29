// stlport
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?Rva003C57A9Do@ScriptActions@@QAEXPAVParameter@@ABVAsciiString@@@Z @0x003C57A9 124B and
// ?Rva003C58C9Do@ScriptActions@@QAEXPAVParameter@@ABVAsciiString@@H@Z @0x003C58C9 161B: the
// named-unit command-button script actions (Zero Hour doNamedUseCommandButtonAbility
// and ...AtWaypoint, GeneralsMD ScriptActions.cpp). The unit is resolved through
// rowed ScriptEngine 0x003588E7; its command set string (0x00290E67) goes through
// the rowed ControlBar::findCommandSet (0x0031D5F8); every one of the 32 command
// buttons of the set whose name matches the ability fires through the pinned
// Object::doCommandButton (0x00296749, source 1 = from script) or, for the
// waypoint variant, the pinned 0x00297149 with the waypoint position at +0x0C
// (waypoint looked up through TerrainLogic vslot 0x88). Target evidence: retail
// bodies, loop bound 0x20 and callee REL32s read byte for byte; semantics from
// the Zero Hour donor.
#include "ascii_string.h"

class Parameter;
class CommandSet;
struct Coord3D;

class CommandButton
{
public:
	const AsciiString &getName() const { return m_name; }
private:
	char m_pad[0x10];
	AsciiString m_name;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name);	// rowed 0x0031D5F8 (ControlBar::findCommandSet)
};
class ControlBar
{
};
extern ControlBar *TheControlBar;

class Object
{
public:
	const AsciiString *rva00290E67() const;
	void doCommandButton(const CommandButton *button, int source, bool extra);
	void doCommandButtonAtPosition(const CommandButton *button, const Coord3D *pos, int source, int extra);
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class Waypoint
{
public:
	char m_pad00[0x0C];
	float m_x;
	float m_y;
	float m_z;
};

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33();
	virtual Waypoint *s34(int id);
};
extern TerrainLogic *TheTerrainLogic;

void ScriptActions::Rva003C57A9Do(Parameter *unit, const AsciiString &ability)
{
	Object *obj = TheScriptEngine->getUnitNamed(unit);
	if (obj == 0)
		return;
	const CommandSet *set = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(obj->rva00290E67());
	if (set == 0)
		return;
	for (int i = 0; i < 32; i++)
	{
		const CommandButton *button = set->getCommandButton(i);
		if (button != 0)
		{
			if (!button->getName().isEmpty())
			{
				if (button->getName() == ability)
					obj->doCommandButton(button, 1, 0);
			}
		}
	}
}

void ScriptActions::Rva003C58C9Do(Parameter *unit, const AsciiString &ability, int waypointId)
{
	Object *obj = TheScriptEngine->getUnitNamed(unit);
	Waypoint *way = TheTerrainLogic->s34(waypointId);
	if (obj == 0 || way == 0)
		return;
	const CommandSet *set = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(obj->rva00290E67());
	if (set == 0)
		return;
	for (int i = 0; i < 32; i++)
	{
		const CommandButton *button = set->getCommandButton(i);
		if (button != 0)
		{
			if (!button->getName().isEmpty())
			{
				if (button->getName() == ability)
					obj->doCommandButtonAtPosition(button, (const Coord3D *)&way->m_x, 1, 0);
			}
		}
	}
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
