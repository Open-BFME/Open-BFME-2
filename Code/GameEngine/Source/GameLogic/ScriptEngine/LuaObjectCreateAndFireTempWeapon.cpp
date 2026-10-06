// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?ObjectCreateAndFireTempWeapon@@YAHPAUlua_State@@@Z, retail 0x0033541C 186B.
// Lua binding: fire temp weapon from named template at object pos.
// Evidence: pinned name, rowed lua_gettop 0x00746F30, rowed Rva00990030Lookup
// 0x00747190, rowed lua_type 0x007470A0, rowed findObjectByID 0x00049DC5,
// rowed lua_tostring 0x007473B0, rowed StringBase ctor 0x00037BA0,
// rowed findWeaponTemplate 0x002CB8BF, rowed releaseBuffer 0x00036410,
// rowed createAndFireTempWeapon 0x002CE904, globals TheAudio TheGameLogic
// TheWeaponStore, neighbours DelayedDeath and HasUpgrade.
#include "ascii_string.h"

struct lua_State;
extern "C" int lua_gettop(lua_State *s);
extern "C" int lua_type(lua_State *s, int i);
extern "C" const char *lua_tostring(lua_State *s, int i);

struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *r, int i);

enum ObjectID { INVALID_OBJECT_ID = 0 };
class Object;
class WeaponTemplate;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class AudioManager;
extern AudioManager *TheAudio;

struct Coord3D { float x; float y; float z; };
class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_pos38;
};

class WeaponTemplate
{
};

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &n) const;
	void createAndFireTempWeapon(const WeaponTemplate *w, const Object *o, const struct Coord3D *p);
};
extern WeaponStore *TheWeaponStore;

int ObjectCreateAndFireTempWeapon(lua_State *L)
{
	if (lua_gettop(L) < 2 || TheAudio == 0)
		return 0;
	unsigned id = Rva00990030Lookup((Rva00990030Range *)L, 1);
	if (id == 0 && lua_type(L, 1) != 1)
		return 0;
	Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
	if (obj != 0) {
		const char *wName = lua_tostring(L, 2);
		const WeaponTemplate *tpl;
		{
			AsciiString tmp(wName);
			tpl = TheWeaponStore->findWeaponTemplate(tmp);
		}
		if (tpl != 0) {
			TheWeaponStore->createAndFireTempWeapon(tpl, obj, &obj->m_pos38);
			return 1;
		}
	}
	return 0;
}
