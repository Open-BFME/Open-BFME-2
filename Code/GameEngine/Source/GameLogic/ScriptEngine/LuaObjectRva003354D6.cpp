// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Rva003354D6@@YAHPAUlua_State@@_N@Z, retail 0x003354D6 220B.
// Gap between CreateAndFire 0x0033541C and HasUpgrade 0x003355B2, same flags.
// Grants/removes player or object upgrades by bool arg.
// Evidence: rowed lua_gettop 0x00746F30, rowed Rva00990030Lookup 0x00747190,
// rowed lua_type 0x007470A0, rowed findObjectByID 0x00049DC5,
// rowed lua_tostring 0x007473B0, rowed StringBase ctor 0x00037BA0,
// rowed findUpgrade 0x0026F26D, rowed releaseBuffer 0x00036410,
// rowed getControllingPlayer 0x0028AFA9, rowed Player rva002AE329 0x002AE329,
// rowed Player rva002ADAC3 0x002ADAC3, rowed Object rva00293077 0x00293077,
// rowed Object rva00290D42 0x00290D42.
#include "ascii_string.h"

struct lua_State;
extern "C" int lua_gettop(lua_State *s);
extern "C" int lua_type(lua_State *s, int i);
extern "C" const char *lua_tostring(lua_State *s, int i);

struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *r, int i);

enum ObjectID { INVALID_OBJECT_ID = 0 };
class Object;
class Player;
class Upgrade;
class UpgradeTemplate;
enum UpgradeStatusType { UPGRADE_STATUS_02 = 2 };
typedef int Int;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva00293077(const void *a);
	void rva00290D42(const UpgradeTemplate *u);
};

class Player
{
public:
	Upgrade *rva002AE329(const UpgradeTemplate *t, UpgradeStatusType s, Int x);
	void rva002ADAC3(const UpgradeTemplate *t, Int x);
};

class UpgradeTemplate
{
public:
	int m_00;
	int m_04;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &n) const;
};
extern "C" UpgradeCenter *TheUpgradeCenter;

int Rva003354D6(lua_State *L, bool b)
{
	if (lua_gettop(L) < 2)
		return 0;
	unsigned id = Rva00990030Lookup((Rva00990030Range *)L, 1);
	if (id == 0 && lua_type(L, 1) != 1)
		return 0;
	Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
	if (obj == 0)
		return 0;
	const char *upName = lua_tostring(L, 2);
	const UpgradeTemplate *tpl;
	{
		AsciiString tmp(upName);
		tpl = TheUpgradeCenter->findUpgrade(tmp);
	}
	if (tpl == 0)
		return 0;
	if (tpl->m_04 == 0) {
		Player *p = obj->getControllingPlayer();
		if (b != 0) {
			p->rva002AE329(tpl, (UpgradeStatusType)2, 0);
		} else {
			p->rva002ADAC3(tpl, 0);
		}
	} else {
		if (b != 0) {
			obj->rva00293077(tpl);
		} else {
			obj->rva00290D42(tpl);
		}
	}
	return 1;
}
