// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003C42B9@ScriptActions@@QAEXPAVParameter@@ABVAsciiString@@1@Z @0x003C42B9 151B
// Script unit command-button dispatch: named unit plus object-types or
// thing-template fallback, then command-button ready checks. Evidence:
// rowed getUnitNamed 0x3588E7 getObjectTypes 0x357651 findCommandButton
// 0x31BE3C isReady 0x35B069 rva002922D9 0x2922D9 rva002D06CA 0x2D06CA,
// pinned rva003C24F0 0x3C24F0 rva003BE11C 0x3BE11C, caller 0x3CCBC7,
// neighbours Rva003C4245Do Rva003C4350Do same flags, ret 0xC thiscall.
#include "ascii_string.h"

class Parameter;
class Object;
class ObjectTypes;
class Player;
class ThingTemplate;
class CommandButton;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
	ObjectTypes *getObjectTypes(const AsciiString &s);
};

extern class ScriptEngine *TheScriptEngine;

class ScriptActions
{
public:
	Object *rva003C24F0(const Coord3D *pos, ObjectTypes *types, Player *player, bool flag);
	void rva003C42B9(Parameter *param, const AsciiString &a, const AsciiString &b);
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *s);
};

extern class ThingFactory *TheThingFactory;

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &s);
};

class CommandButton
{
public:
	bool isReady(const Object *o) const;
};

class Object
{
public:
	bool rva002922D9(const CommandButton *b);
};

void __cdecl rva003BE11C(const ThingTemplate *tmpl, const CommandButton *button);

void ScriptActions::rva003C42B9(Parameter *param, const AsciiString &a, const AsciiString &b)
{
	Object *unit = TheScriptEngine->getUnitNamed(param);
	if (unit == 0)
		return;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(b);
	const ThingTemplate *tmpl;
	if (types != 0)
	{
		Object *obj = rva003C24F0((const Coord3D *)((const char *)unit + 0x38), types, 0, false);
		if (obj == 0)
			return;
		tmpl = *(const ThingTemplate *const *)((const char *)obj + 4);
	}
	else
		tmpl = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&b);
	if (tmpl == 0)
		return;
	const CommandButton *button = ((ControlBar *)(*(BfmeWorldRV **)&TheControlBar))->findCommandButton(a);
	if (button == 0)
		return;
	if (!button->isReady(unit))
		return;
	if (!unit->rva002922D9(button))
		return;
	rva003BE11C(tmpl, button);
}
