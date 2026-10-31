// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Lua ObjectPlayerSide 0x00334EC4 (106B) + ObjectTemplateName 0x00334FAB (98B),
// dedicated TU. Home TU Code/GameEngine/Source/GameLogic/ScriptEngine/
// LuaScriptBindingsLuaAO1.cpp is held by scale-20261005-5; this TU reuses its
// flags/externs with TU-scoped views, no shared-header edits, no new pins.
//
// Target facts (game.dat, read-only, capstone + seat-55-r7 research):
// - 0x334EC4 106B [0x334EC4,0x334F2E) ret C3, cdecl int f(lua_State*), returns 1,
//   saves esi/edi (56 57). Registration 0x3384A4: push 0x734EC4 + push [edi+0xC]
//   + call lua_pushcclosure (row 11102 @0x747640), then push 0xC0E734
//   ("ObjectPlayerSide") + push [edi+0xC] + call lua_setglobal (row 11142).
//   Body: Lookup (row 9652 @0x747190) + lua_type (row 11127 @0x7470A0) +
//   findObjectByID (row 5818 @0x49DC5, single call, enum ObjectID, map +0xB4) +
//   Team::getControllingPlayer (row 13658 @0x39D7CF, ecx=[obj+0x304]) +
//   pushstring (row 11130) or pushnil (row 11104). Data: TheGameLogic 0xDFE78C
//   extern, empty 0xBBAC1C NUL, holder [player+0x58] -> string ([holder]?+8:empty).
// - 0x334FAB 98B [0x334FAB,0x33500D) same prologue/returns. Registration 0x3384DD:
//   push 0x734FAB + push [edi+0xC] + call pushcclosure, then push 0xC0E700
//   ("ObjectTemplateName") + push [edi+0xC] + call setglobal. Body: Lookup +
//   lua_type + findObjectByID (single, same row) + pushstring/pushnil, NO middle
//   getControllingPlayer. Holder [[obj+0x04]+0x64] -> string ([holder]?+8:empty).
// - Chain 0x334EC4 -> 0x334F2E (banked reverse/attempts/0x00334f2e.cpp 0.75) -> 0x334FAB -> 0x33500D contiguous.
// Donor provenance (read-only, 6583b3c1):
// - reference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine/
//   LuaScriptBindingsLuaA.cpp ObjectTestModelCondition lines 131-155 same
//   Lookup/type/findObjectByID/pushnil family shape (moderate repair, same
//   providers/ABI, new +0x304/+0x04/+0x64/+0x58 field logic). ObjectPlayerSide
//   itself BFME2-new (rg empty in BFME1 ScriptEngine). ObjectTemplateName has
//   BFME1 registration at LuaScriptEngineRegisterScriptFunctions.cpp line 155
//   via identical pushcclosure/setglobal idiom (j_ address BFME1-only).
// - BFME2 family TU LuaScriptBindingsLuaAO1.cpp rows 50955/50956 prove
//   /O2->/O1 migration + cdecl luaA shape places byte-exact in this family.
// - Object Team+0x304 view from Code/GameEngine/Source/GameLogic/Object/
//   ObjectGetControllingPlayer.cpp (team+0x304, genuine +0x304). Player +0x58
//   holder and ThingTemplate+0x04/+0x64 holder are target byte facts
//   ([eax+0x304], [eax+0x04]+0x64, +0x58, +8); semantic names hypothesis only.
// - GameLogic::findObjectByID retail 0x00049DC5 37B is
//   Code/GameEngine/Source/GameLogic/GameLogicFindObjectByID.cpp with
//   enum ObjectID { INVALID_OBJECT_ID=0 } and map at this+0xB4 (retail B4).
//   This TU uses that enum spelling (W4ObjectID mangling), NOT typedef int
//   with pad 0xB0 (B0 alias in ObjectEnterUncontrollable...). Genuine provider.
// - Rva00990030Lookup retail 0x00747190 52B is
//   Code/GameEngine/Source/Common/Rva00990030RecordLookup.cpp with
//   Rva00990030Range* (genuine), NOT lua_State* alias. This TU uses Range*
//   with (Rva00990030Range*)state cast, as in ObjectCountNearbyEnemies.cpp
//   and ObjectBroadcastEvent.cpp (both /O1, both matched).
// All callees rowed (9652/11127/5818/13658/11130/11104), no new symbols.csv pin.
// GameLogic uses the shared target view. Object/Team/Player remain existing
// per-unit layouts; the string holder preserves their native four-byte member.

struct lua_State;
extern "C" int lua_type( lua_State *state, int index );
extern "C" void lua_pushnil( lua_State *state );
extern "C" void lua_pushstring( lua_State *state, const char *str );
struct Rva00990030Range;
unsigned Rva00990030Lookup( Rva00990030Range *range, int index );

#include "../../Common/GameLogicObjectLookupView.h"

class Object;
class Player;
class Team;

struct BfmeSideHolder
{
	void *m_data;
};

enum UpgradeStatusType { UPGRADE_STATUS_02 = 2 };
class UpgradeTemplate;
class Upgrade;
class Player
{
public:
	bool rva002AB87D(const UpgradeTemplate *t) const;
	bool rva002AA245() const;
	Upgrade *addUpgrade(const UpgradeTemplate *t, UpgradeStatusType s, int x);
	void removeUpgrade(const UpgradeTemplate *t, int x);
	char m_pad00[0x58];
	BfmeSideHolder m_side58; // +0x58 target fact, AsciiString-compatible 4B
};

class Team
{
    unsigned char pad00[0x34];
public:
    Player *controllingPlayer;
	Player *getControllingPlayer() const; // row 13658 @0x39D7CF
};

class AIUpdateInterface;
class LuaAllegianceAI {
    unsigned char pad00[0x240];
public:
    Player *allegiance;
};

class Object
{
private:
	unsigned char m_pad00[ 0x04 ]; // +0x00 vtable slot

public:
	ThingTemplate *m_template; // +0x04 target fact

private:
	unsigned char m_pad08[ 0x80 - 0x08 ];
public:
    ObjectID m_capturingID;
private:
    unsigned char m_pad84[0x258 - 0x84];
public:
    AIUpdateInterface *m_ai;
private:
    unsigned char m_pad25C[0x304 - 0x25C]; // +0x08..0x304

public:
	Team *m_team304; // +0x304 target fact (Team* for player-side path)
    Player *getControllingPlayer() const;
};


extern GameLogic *TheGameLogic;

// Native lookup bodies are visible so the compiler knows they only read the
// map and can retain TheGameLogic across both calls in ObjectCapturingObjectPlayerSide.
// Same verified traversal as ProjectileNuggetObjectEffect.cpp: native
// _M_find2888D4 plus pinned STLport reference; 37B/47B COMDAT owners unchanged.
struct LuaCapturingLookupNode { LuaCapturingLookupNode *next; ObjectID key; Object *object; };
struct LuaCapturingLookupBuckets {
 LuaCapturingLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 LuaCapturingLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct LuaCapturingLookupMap { unsigned char hashEqual[4]; LuaCapturingLookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 LuaCapturingLookupMap *map=(LuaCapturingLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 LuaCapturingLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}

inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}

// ?ObjectPlayerSide@@YAHPAUlua_State@@@Z (Lua ObjectPlayerSide binding)
int ObjectPlayerSide( lua_State *state )
{
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		goto fail;
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( object )
	{
		Team *team = object->m_team304;
		Player *player = team->getControllingPlayer();
		BfmeSideHolder *holder = &player->m_side58;
		const char *side = holder->m_data ?
			(const char *)holder->m_data + 8 : "";
		lua_pushstring( state, side );
		return 1;
	}
fail:
	lua_pushnil( state );
	return 1;
}

// ?ObjectTemplateName@@YAHPAUlua_State@@@Z (Lua ObjectTemplateName binding)
int ObjectTemplateName( lua_State *state )
{
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		goto fail;
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( object )
	{
		BfmeSideHolder *holder = (BfmeSideHolder *)( (char *)object->m_template + 0x64 );
		const char *name = holder->m_data ?
			(const char *)holder->m_data + 8 : "";
		lua_pushstring( state, name );
		return 1;
	}
fail:
	lua_pushnil( state );
	return 1;
}

// Native334F2E..334FAB,125B. Lua registration3384C2 identifies
// ObjectCapturingObjectPlayerSide. Object capture ID is read at80; both
// lookup calls use the same game-logic receiver. Controller28AFA9 and
// player side holder58 match the neighboring player-side binding.
int ObjectCapturingObjectPlayerSide(lua_State *state) {
    unsigned id=Rva00990030Lookup((Rva00990030Range*)state,1);
    if(!id && lua_type(state,1)!=1)goto fail;
    Object *object=TheGameLogic->findObjectByID((ObjectID)id);
    Object *capturing=object ? TheGameLogic->findObjectByID(object->m_capturingID) : 0;
    if(capturing) {
        Player *player=capturing->getControllingPlayer();
        BfmeSideHolder *holder=&player->m_side58;
        const char *side=holder->m_data ? (const char*)holder->m_data+8 : "";
        lua_pushstring(state,side);
        return 1;
    }
fail:
    lua_pushnil(state); return 1;
}

// Native334C9F..334D16,119B. Registration33875F / C0E4B8 names
// ObjectChangeAllegianceFromNonPlayablePlayer. Lookup IDs 1/2, reject a
// playable controller, then set AI+240 to the second object's team+34 player.
int ObjectChangeAllegianceFromNonPlayablePlayer(lua_State *state) {
    unsigned firstID=Rva00990030Lookup((Rva00990030Range*)state,1);
    unsigned secondID=Rva00990030Lookup((Rva00990030Range*)state,2);
    if(secondID && firstID) {
        Object *first=TheGameLogic->findObjectByID((ObjectID)firstID);
        Object *second=TheGameLogic->findObjectByID((ObjectID)secondID);
        if(first && second && !first->getControllingPlayer()->rva002AA245())
            ((LuaAllegianceAI *)first->m_ai)->allegiance=second->m_team304->controllingPlayer;
    }
    return 0;
}
