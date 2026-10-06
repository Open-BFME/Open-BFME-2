// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?doUnpackBase@ScriptActions@@IAEXPAVParameter@@PBVAsciiString@@H@Z @0x003BE2DB 176B
// (dump range 18). Unit-plus-mask module gate: resolves the unit through
// rowed ScriptEngine 0x003588E7 getUnitNamed, requires its controlling
// player to be the rowed ScriptEngine 0x00205C93 current player, resolves
// the Castle pool-key module through rowed static 0x003955DA plus rowed
// protected Object 0x0028B6D6 findModule (friend bridge in this TU's view),
// then chains the pinned 0x00395F57 canUnpack, 0x00397F45, conditional
// 0x0039718B and 0x00399C6C module calls, and emits through pinned
// ScriptEngine 0x00208968 unless the name isEmpty (rowed 0x00001E2F).
#include "ascii_string.h"

class Parameter;
class Player;
class Module;
class Team;

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
class ScriptActions;

class Object
{
public:
	Player *getControllingPlayer() const;
protected:
	Module *findModule(NameKeyType key) const;
	friend class ScriptActions;
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
	Player *getCurrentPlayer();
	void rva00208968(const AsciiString &name, Object *obj);
};
extern ScriptEngine *TheScriptEngine;

class Rva00395F57
{
public:
	bool canUnpack(bool v);
};
class Rva00397F45
{
public:
	bool rva00397F45(Player *pl, int v);
};
class Rva0039718B
{
public:
	bool rva0039718B(Player *pl);
};
class Rva00399C6C
{
public:
	void rva00399C6C(int a, int b);
};

class ScriptActions
{
protected:
	void doUnpackBase(Parameter *p1, const AsciiString *str, int flag);
};

void ScriptActions::doUnpackBase(Parameter *p1, const AsciiString *str, int flag)
{
	Object *obj = TheScriptEngine->getUnitNamed(p1);
	if (obj == 0)
		return;
	Player *pl = obj->getControllingPlayer();
	if (pl != TheScriptEngine->getCurrentPlayer())
		return;
	Module *mod = obj->findModule(CastleBehavior::rva0003955DA());
	if (mod == 0)
		return;
	if (!((Rva00395F57 *)mod)->canUnpack(true))
		return;
	if (!((Rva00397F45 *)mod)->rva00397F45(obj->getControllingPlayer(), 1))
		return;
	if ((unsigned char)flag == 0) {
		if (!((Rva0039718B *)mod)->rva0039718B(obj->getControllingPlayer()))
			return;
	}
	((Rva00399C6C *)mod)->rva00399C6C(flag, 0);
	if (str->isEmpty())
		return;
	TheScriptEngine->rva00208968(*str, obj);
}
