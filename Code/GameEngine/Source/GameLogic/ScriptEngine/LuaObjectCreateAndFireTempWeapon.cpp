// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
class ThingTemplate;
class Player;
class Drawable;
class SpecialPowerModuleInterface;
enum SpecialPowerType { SPECIAL_POWER_TYPE_UNKNOWN = 0 };
enum DrawableID { INVALID_DRAWABLE_ID = 0 };
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

#include "../../Common/GameLogicObjectLookupView.h"
class Object;
class WeaponTemplate;
extern GameLogic *TheGameLogic;

class AudioManager;
extern AudioManager *TheAudio;

#include "../../../../Libraries/Include/Lib/Coord3D.h"
class UpgradeTemplate;
class Object
{
public:
	bool rva0028C149(int,float*,int);
 void rva00293077(const void *a);
 void removeUpgrade(const UpgradeTemplate *u);
 void rva0028EBDA(bool flag);
 void rva00291080(bool flag);
 float rva002C97E8(const Coord3D *a, const Coord3D *b) const;
 float GetRelativeAngle(const Coord3D *pos) const;
 Drawable *getDrawable() const;
public:
	__forceinline unsigned char testStatus(int bit) const
	{
		return (m_status[(unsigned int)bit >> 5] & (1u << (bit & 31))) != 0;
	}
public:
	char m_pad00[0x04];
public:
	ThingTemplate *m_template;
public:
	char m_pad08[0x38 - 0x08];
 Coord3D m_position; // +0x38
 char m_pad44[0x74 - 0x44];
 ObjectID m_id; // +0x74
 char m_pad78[0x94 - 0x78];
public:
	unsigned int m_status[2];
public:
	char m_pad9C[0x258 - 0x9C];
public:
	void *m_ai258;
public:
	char m_pad25C[0x38C - 0x25C];
 Coord3D m_targetPos; // +0x38C
public:
	int m_currentTargetID;
public:
	void rva0028EC68(int index, void *source, int delay);
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
public:
	Player *getControllingPlayer() const;
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
			TheWeaponStore->createAndFireTempWeapon(tpl, obj, &obj->m_position);
			return 1;
		}
	}
	return 0;
}
