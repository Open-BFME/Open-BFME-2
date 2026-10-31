// cl: /MD /GX
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
class ThingTemplate;
class Player;
class Drawable;
class SpecialPowerModuleInterface;
enum SpecialPowerType { SPECIAL_POWER_TYPE_UNKNOWN = 0 };
enum DrawableID { INVALID_DRAWABLE_ID = 0 };
//
// CurDrawableGetCurrentTargetDistance (0x00333125, 93B): the Lua callback the
// registration at 0x00335ED2 pushes with lua_pushcclosure (nargs 0) and the
// lua_setglobal right after it names CurDrawableGetCurrentTargetDistance
// (cstr at RVA 0x0080E1C4, verified by pe read; neighbor 0x0080E17C names the
// adjacent Bearing sibling landed from the same ScriptEngine folder).
// Ported from Open-BFME-1's
// GameLogic/ScriptEngine/CurDrawableGetCurrentTargetDistance.cpp (donor
// revision 6583b3c1ff21db4a561285717028fdafc780b7db): the same drawable
// (+0x9C in BFME2, +0x78 in BFME1) / owner (+0x0C) / target (+0xFC)
// null-guard chain and the same sqrt-of-planar-distance pushnumber-or-pushnil
// return-1 idiom, keeping the donor's repeated owner->m_object reads with no
// caching local (the add eax,0xFC idiom folds to mov+test with a cached
// local under MSVC 7.1, per the Bearing sibling). Single-return nested
// if/else: retail shares one xor/inc/ret tail reached by jmp from the number
// arm, unlike the donor's early return.

struct lua_State;
extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" void lua_pushnil(lua_State *state);

// Real CRT sqrt ABI: math.h double sqrt(double) emits the rowed msvcr71
// import call at 0x0062921C (same as the PathDistance/Rva00263778 siblings).
#include <math.h>

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// +0x38 (Object geometry position, per ObjectRva002C97E8.cpp)
// +0x38C payload position: semantic identity inferred from the
// rva002C97E8 (target-minus-[+0x38]) call contract, not independently proven.
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

struct LuaTargetOwner
{
	char m_targetPad[0xFC];
	Object *m_target;	// +0xFC
};

class Drawable
{
public:
	DrawableID getID() const;
	bool rva00278689(const AsciiString &name, bool a, bool b);
	void rva002724FD(const AsciiString &name, int show, int permanent, float c, float d);
 void rva002724FD(const AsciiString &name, unsigned char show, int permanent, float c, float d);

	__forceinline unsigned char testModelCondition(int bit) const
	{
		return (m_conditionState[(unsigned int)bit >> 5] & (1u << (bit & 31))) != 0;
	}

	char m_pad000[0xFC];
	Object *m_object;	// +0xFC
	char m_pad100[0x258 - 0x100];
	unsigned int m_conditionState[10];	// +0x258, tested with BitFlags<304> bits
};

struct LuaDrawableLink
{
	AsciiString m_previousAnimationState;	// +0x00
	AsciiString m_transitionAnimState;	// +0x04
	AsciiString m_previousAnimation;	// +0x08
	Drawable *m_drawable;	// +0x0C
	float m_prevAnimFraction;	// +0x10
	unsigned char m_allowToContinue;	// +0x14
};

struct LuaDrawableState
{
	char m_drawablePad[0x9C];
	LuaDrawableLink *m_drawable;	// +0x9C
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

// ?CurDrawableGetCurrentTargetDistance@@YAHPAUlua_State@@@Z
int CurDrawableGetCurrentTargetDistance(lua_State *state)
{
	LuaDrawableLink *drawable = reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->m_drawable;
	if (drawable != 0) {
		Drawable *owner = drawable->m_drawable;
		if (owner != 0) {
			if (owner->m_object != 0) {
				lua_pushnumber(state, sqrt(owner->m_object->rva002C97E8(&owner->m_object->m_position, &owner->m_object->m_targetPos)));
			}
			else {
				lua_pushnil(state);
			}
		}
		else {
			lua_pushnil(state);
		}
	}
	else {
		lua_pushnil(state);
	}
	return 1;
}
