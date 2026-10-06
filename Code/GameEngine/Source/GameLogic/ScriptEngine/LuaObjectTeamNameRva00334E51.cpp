// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Lua ObjectTeamName (0x00334E51, 115B): the Lua callback the registration at
// 0x00338489 pushes with lua_pushcclosure and names with lua_setglobal
// (literal ObjectTeamName at 0x00C0E748). Retail predecessor of the Lua204
// chain (E51 -> EC4 -> F2E -> FAB -> 33500D -> 508F -> 514A) served by the
// single 0x003384xx routine.
//
// Ported from Open-BFME-1
// game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptBindingsLuaA.cpp
// Rva002E5FF0ObjectFieldName (donor revision 6583b3c1, donor flags /O2):
// Lookup/type/findObjectByID + holder ternary m_data?+8:empty family shape.
// Donor layout: Object->m_team (Field23C at +0x23C) -> m_field4 (void* at
// +0x4) -> string at field+0x14, via Rva002E5FF0Str + Rva01336E50Str +
// g_bfmeEmptyAscii. BFME2 deltas (all retail-measured): Object+0x304 holder,
// holder+0x30 indirect (void*), string at indirect+0x14 as canonical
// AsciiString, TheEmptyString object at VA 0x00DE0878 (RVA 0x009E0878,
// exports.csv ?TheEmptyString@AsciiString@@2V1@B), empty NUL at 0x00BBAC1C.
// Genuine providers only: Rva00990030Range* Lookup (row 9652), enum
// ObjectID + B4 map findObjectByID (row 5818), lua_type/pushstring/pushnil
// (rows 11127/11130/11104), TheGameLogic DIR32 0x00DFE78C, canonical
// AsciiString::TheEmptyString + AsciiString::str().
//
// Target facts: 115B body bytes, registration pair, REL32 callees, DIR32
// TheGameLogic, immediates 0xDE0878/0xBBAC1C, offsets +0x304/+0x30/+0x14/+8.
// Donor facts: control shape + Lua cdecl return-1 lane + Field23C/m_field4
// naming only. Inference (unproven, from the ObjectTeamName registration
// literal only): the holder/indirect/string chain carries the object's team
// name; no Team/Proto class identity is asserted and no original type name
// is claimed.

struct lua_State;
extern "C" int lua_type(lua_State *state, int index);
extern "C" void lua_pushnil(lua_State *state);
extern "C" void lua_pushstring(lua_State *state, const char *str);

// Canonical AsciiString (registered reference/shims/bfme2_ascii/
// ascii_string.h, one-pointer 4B, TheEmptyString at 0xDE0878). No TU-local
// AsciiString copy per class_gate.
#include "ascii_string.h"

struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *range, int index);

// Retail-measured holder chain. Names are address-derived only: the
// Object+0x304 slot and holder+0x30 indirect are unproven as Team/Proto;
// the donor's equivalent slots are m_team (at +0x23C) and m_field4 (+0x4).
struct Rva00334E51Holder
{
	char m_unreconstructed00[0x30];
	void *m_field30;
};

class Object
{
public:
	char m_pad00[0x304];
	Rva00334E51Holder *m_holder304;
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

// ?Rva00334E51@@YAHPAUlua_State@@@Z
int Rva00334E51(lua_State *state)
{
	unsigned id = Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!id) {
		if (lua_type(state, 1) != 1)
			goto fail;
	}
	{
		Object *object = TheGameLogic->findObjectByID((ObjectID)id);
		if (object) {
			void *field = object->m_holder304->m_field30;
			AsciiString *str = !field ? (AsciiString *)&AsciiString::TheEmptyString : (AsciiString *)((char *)field + 0x14);
			lua_pushstring(state, str->str());
			goto done;
		}
	}
fail:
	lua_pushnil(state);
done:
	return 1;
}
