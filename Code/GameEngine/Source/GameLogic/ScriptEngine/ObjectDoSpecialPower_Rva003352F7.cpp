// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?ObjectDoSpecialPower@@YAHPAUlua_State@@@Z @0x003352F7 178B.
// Lua callback ObjectDoSpecialPower: with at least 2 args and TheAudio present,
// resolve object 1, name a SpecialPowerTemplate via TheSpecialPowerStore, resolve its
// module on the object and fire it when ready.
//
// Ported from Open-BFME-1
// game/GameEngine/Source/GameLogic/ScriptEngine/ObjectDoSpecialPower.cpp
// (donor revision 6583b3c1, donor flags /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// /EHsc /Igame/Libraries/Source/WWVegas/WWLib), recompiled here at /O1 with
// the bfme2_ascii shim (matched ScriptEngine siblings ObjectBroadcastEvent
// 365-520B, Rva003C4245Do 116B, ObjectCountNearbyEnemies 310B all /O1).
//
// Identity (target facts, read-only game.dat decode this seat):
// - Registration at 0x00338670 pushes func VA 0x007352F7 (RVA 0x003352F7) with
//   lua_pushcclosure then pushes string VA 0x00C0E5A4 ("ObjectDoSpecialPower")
//   with lua_setglobal; the pushed body is the one the setglobal names.
// - Ghidra FUN_007352F7 178B boundary [0x3352F7,0x3353A9); next body 0x3353A9
//   is rowed DelayedDeath 115B, prev 0x33508F/0x3352F7 gap holds 0x3352F7.
// - Retail head: lua_gettop 0x00746F30 <2 bail, TheAudio [0x00DFE6E8]==0 bail,
//   Rva00990030Lookup 0x00747190, lua_type 0x007470A0!=1 bail,
//   findObjectByID 0x00049DC5 (rowed 37B), lua_tostring 0x007473B0,
//   StringBase 0x0037BA0 AsciiString-from-char, findSpecialPowerTemplate
//   0x0029B6EB (rowed 71B) via TheSpecialPowerStore [0x00E02D4C],
//   friend_getFinalOverride 0x00288609 (rowed 24B) then type at [eax+0x1C],
//   findSpecialPowerModuleInterface 0x00290E22 (rowed 69B),
//   slot1 isReady [eax+4], slot10 doSpecialPower [eax+0x28] with 0.
// Donor facts carried only: lua_gettop<2/TheAudio-guard/lookup/type/object/
// template/module/ready/fire/return-1 shape; SpecialPowerModuleInterface
// isReady/doSpecialPower slots; AsciiString-by-value template lookup.
// BFME2-new adaptation (target evidence): template type via final-override
// +0x1C (ObjectFindSpecialPowerModuleInterface documents name +0x10, type
// +0x1C) instead of donor direct getSpecialPowerType(); interface slots
// 1/10 per that file (slot 1 isReady, slot 10 doSpecialPower).
#include "ascii_string.h"

struct lua_State;
extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_type(lua_State *state, int index);
extern "C" const char *lua_tostring(lua_State *state, int index);

struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *range, int index);	// 0x00747190

typedef unsigned int UnsignedInt;

enum SpecialPowerType
{
	SPECIAL_POWER_TYPE_UNKNOWN = 0
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
private:
	void *m_vptr;
public:
	Overridable *m_nextOverride;
	unsigned char m_isAllocated;
};

class SpecialPowerTemplate : public Overridable
{
public:
	char m_pad0C[0x10 - 0x0C];
	void *m_name10;
	char m_pad14[0x1C - 0x14];
	SpecialPowerType m_type1C;
};

class SpecialPowerModuleInterface
{
public:
	virtual bool isModuleForPower(const SpecialPowerTemplate *) const = 0;
	virtual bool isReady() const = 0;
	virtual void s02() const = 0;
	virtual void s03() const = 0;
	virtual void s04() const = 0;
	virtual void s05() const = 0;
	virtual void s06() const = 0;
	virtual void s07() const = 0;
	virtual void s08() const = 0;
	virtual void s09() const = 0;
	virtual void doSpecialPower(UnsignedInt commandOptions) = 0;
};

class Object
{
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

class AudioManager;
extern AudioManager *TheAudio;

class SpecialPowerStore;
extern SpecialPowerStore *TheSpecialPowerStore;

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

#define TheAudioClientUpdate ((void *)TheAudio)

// ?ObjectDoSpecialPower@@YAHPAUlua_State@@@Z
int ObjectDoSpecialPower(lua_State *state)
{
	if (lua_gettop(state) < 2 || !TheAudioClientUpdate)
		return 0;
	unsigned id = Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!id && lua_type(state, 1) != 1)
		return 0;
	Object *object = TheGameLogic->findObjectByID((int)id);
	if (!object)
		return 0;
	const SpecialPowerTemplate *power =
		TheSpecialPowerStore->findSpecialPowerTemplate(lua_tostring(state, 2));
	if (!power)
		return 0;
	const Overridable *finalOverride = power->friend_getFinalOverride();
	SpecialPowerModuleInterface *module = object->findSpecialPowerModuleInterface(
		((const SpecialPowerTemplate *)finalOverride)->m_type1C);
	if (!module)
		return 0;
	if (module->isReady())
		module->doSpecialPower(0);
	return 1;
}
