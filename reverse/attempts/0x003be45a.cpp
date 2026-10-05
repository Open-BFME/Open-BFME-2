// ?Rva003BE45ASet@@YGXPBVAsciiString@@PAXPAVParameter@@0@Z
// partial score=0.935 date=2026-10-05
// ?Rva003BE38BSet@@YGXPBVAsciiString@@PAVParameter@@0@Z
// partial score=0.93 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// ?Rva003BE45ASet@@YGXPBVAsciiString@@PAXPAVParameter@@0@Z @0x003BE45A 216B
// (dump range 18). Template-plus-unit gate: resolves the template name
// through rowed 0x002D06CA findTemplate and the unit through rowed
// ScriptEngine 0x003588E7 getUnitNamed, requires the controlling player to
// be nonzero, flagged at +0x339 and equal to rowed ScriptEngine 0x00205C93
// getCurrentPlayer, resolves the Castle pool-key module through rowed static
// 0x003955DA plus rowed protected Object 0x0028B6D6 findModule (friend
// bridge), then chains rowed 0x003971BF (template), rowed Player 0x002AA00C
// (template, 0), pinned 0x003980BF (template, -2, 0), and emits through
// rowed ScriptEngine 0x00208968 plus rowed 0x0020A5FF unless the second
// name isEmpty (rowed 0x00001E2F).
#include "ascii_string.h"

class Parameter;
class Player;
class Module;
struct Arg3971BF;

enum NameKeyType
{
	NAMEKEY_NONE = 0
};
class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

class Object;
class ThingTemplate
{
public:
	int rva0033A69A(Object *obj, int a, int b) const;
};
class Object;
void __stdcall Rva003BE45ASet(const AsciiString *tname, void *px, Parameter *p1, const AsciiString *str);

class Object
{
public:
	Player *getControllingPlayer() const;
protected:
	Module *findModule(NameKeyType key) const;
	friend void __stdcall Rva003BE45ASet(const AsciiString *tname, void *px, Parameter *p1, const AsciiString *str);
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
	Player *getCurrentPlayer();
	void rva00208968(const AsciiString &name, Object *obj);
	void rva0020A5FF(Object *obj, const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

class Player
{
public:
	unsigned char rva002AA00C(ThingTemplate *t, int v);
	unsigned char m_pad[0x339];
	unsigned char m_x339;
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern Rva002D06CA *TheThingFactory;

class Rva003971BF
{
public:
	bool rva003971BF(Arg3971BF *a);
};
class Rva003980BF
{
public:
	void *rva003980BF(void *p, int a, int b);
};

void __stdcall Rva003BE45ASet(const AsciiString *tname, void *px, Parameter *p1, const AsciiString *str)
{
	Object *obj = TheScriptEngine->getUnitNamed(p1);
	if (obj == 0)
		return;
	Player *pl = obj->getControllingPlayer();
	if (pl == 0)
		return;
	if (pl->m_x339 == 0)
		return;
	if (pl != TheScriptEngine->getCurrentPlayer())
		return;
	ThingTemplate *tmpl = (ThingTemplate *)TheThingFactory->rva002D06CA(tname);
	if (tmpl == 0)
		return;
	Module *mod = obj->findModule(CastleBehavior::rva0003955DA());
	if (mod == 0)
		return;
	if (!((Rva003971BF *)mod)->rva003971BF((Arg3971BF *)tmpl))
		return;
	if (pl->rva002AA00C(tmpl, 0) == 0)
		return;
	int v = *(int *)((char *)px + 8);
	void *ptr = ((Rva003980BF *)mod)->rva003980BF(tmpl, v, 0);
	if (ptr == 0)
		return;
	if (str->isEmpty())
		return;
	TheScriptEngine->rva00208968(*str, (Object *)ptr);
	TheScriptEngine->rva0020A5FF((Object *)ptr, *str);
}
