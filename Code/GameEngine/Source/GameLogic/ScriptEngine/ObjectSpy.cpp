// cl: /MD /GX
//
// Retail RE: ?ObjectSpy@@YAHPAUlua_State@@@Z @0x00335B88 (218B).
//
// BFME2 Lua callback ObjectSpy. Target facts from retail bytes (all read this
// round, independent of donor):
// - Boundary 0x335B88..0x335C62 (218B, SHA a158c8e9...); prev 0x335A61/295 ends
//   at 0x335B88 and next 0x335C62/38 starts at end; single ret at 0x335C61 (C3)
//   after xor eax,eax; no SEH; no float; cdecl int (lua_State*) with 1 stack arg
//   (esi=[esp+0xC] after push ecx+push esi); callee-saved edi/ebp/ebx preserved.
// - Registration at 0x3383C6 in unclaimed FUN_00738317: push 0x735B88 + push
//   [edi+0xC] + call lua_pushcclosure 0x747640 then push 0xC0E808 + push
//   [edi+0xC] + call lua_setglobal 0x747920; .rdata VA 0xC0E808 (RVA 0x80E808)
//   is single-occurrence cstring ObjectSpy (next registration 0x3383E1 pushes
//   0x73594A with 0xC0E7F4 ObjectDispatchEvent, 0x14 bytes earlier).
// - DIR32 globals from retail immediates, cross-checked with rowed siblings:
//   [0xDFE78C]=TheGameLogic (Rva002AA201IndexedByteGetter + ObjectRva0028C1CC),
//   [0xDF36A4]=TheNameKeyGenerator (NameKeyGenerator.cpp:96-97 + sibling
//   ImageCollectionFindImage), [0xE01DBC]=Lua event global (rowed Rva00332E60
//   50103 + symbols 7640/8998 BfmeCallJ63/LuaDrawableState views on same body).
// - Provider chain, all REL32-decoded this round to rowed/pinned bodies:
//   Lookup 0x747190 (rowed 9652), findObjectByID 0x49DC5 (rowed 5818),
//   lua_tostring 0x7473B0 (rowed 11137), nameToKey 0x148E1A (rowed 5170),
//   invoke 0x333918 (rowed 50103 Rva00332E60 + pinned 7640/8998),
//   bfmeFind 0x33321B (rowed 50097 same TU), io_debug 0x333E42 (rowed 55866),
//   adapter 0x2628C3 (pinned this seat, address-derived; bounds 0x2628B6/13
//   ends at 0x2628C3 and 0x2628C3/29 push/mov/push/add/push/call/ret 0xC ends
//   at 0x2628E0; calls rowed 0x3328ED/136B Ghidra FUN_007328ed).
// - Layout: Object+0x258 holds module pointer (mov ecx,[edi+0x258] null-guarded;
//   BFME2 ScriptEngine siblings establish +0x258 as module/AIUpdate slot, e.g.
//   ScriptActions_doNamedEnterNamed + Rva003C91D1Idle families); adapter takes
//   this=module with (object,eventKey,spyKey) then forwards [object+0x74] and
//   this+0x224 to 0x3328ED.
// Donor-carried only: reference/open-bfme-1/.../ObjectSpy.cpp rev 6583b3c1
// (// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ze, 120-line TU, same-name
// ObjectSpy + same Lua registration family + 8-call structural guide). Deltas
// below are BFME2 target facts, not donor verbatim:
// - module offset +0x258 (retail) vs +0x204 (donor Object::m_module204).
// - zero-ID paths go to io_debug 0x333E42 and return 0 (retail 0x735BC2 tail);
//   donor routes both to debugMode (?j_0003ebad + bfmeNotify2_574) which has no
//   call in 218B; not copied.
// - spyKey via TheNameKeyGenerator->nameToKey 0x148E1A directly (both event and
//   spy names); donor uses NAMEKEY (0x788E8 wrapper) for spyKey; retail shows
//   two 0x148E1A calls, so folded through one path.
// - final doProcess is two-level (adapter 0x2628C3: this+0x224 + [object+0x74]
//   to 0x3328ED) vs donor single BfmeThingED8::doProcess; adapter pinned.
// No shared-header edits; TU-scoped views only.

struct lua_State;
struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *range, int index);	// 0x00747190
extern "C" const char *lua_tostring(lua_State *state, int index);	// 0x007473B0
extern "C" int io_debug(lua_State *state);	// 0x00333E42

typedef unsigned NameKeyType;
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);	// 0x00148E1A
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00332E60
{
public:
	void *rva00333918(int key);	// 0x00333918
	void *rva0033321B(int key);	// 0x0033321B
};
struct LuaDrawableState
{
	unsigned char m_data[0x78];
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;	// 0x00E01DBC

class Rva002628C3
{
public:
	void rva002628C3(void *object, int eventKey, int spyKey);	// 0x002628C3 pinned
};

class Object
{
public:
	char m_pad000[0x258];
	Rva002628C3 *m_module258;	// +0x258
};

class GameLogic
{
public:
	Object *findObjectByID(int id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

// ?ObjectSpy@@YAHPAUlua_State@@@Z
int ObjectSpy(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (objectID == 0) {
		io_debug(state);
		return 0;
	}
	Object *object = TheGameLogic->findObjectByID((int)objectID);
	if (object == 0)
		return 0;
	unsigned targetID = Rva00990030Lookup((Rva00990030Range *)state, 2);
	if (targetID == 0) {
		io_debug(state);
		return 0;
	}
	Object *target = TheGameLogic->findObjectByID((int)targetID);
	if (target == 0)
		return 0;
	const char *eventName = lua_tostring(state, 3);
	NameKeyType eventKey = TheNameKeyGenerator->nameToKey(eventName);
	if (reinterpret_cast<Rva00332E60 *>(TheLuaScriptEngine)->rva00333918((int)eventKey) == 0) {
		io_debug(state);
		return 0;
	}
	const char *spyName = lua_tostring(state, 4);
	NameKeyType spyKey = TheNameKeyGenerator->nameToKey(spyName);
	if (reinterpret_cast<Rva00332E60 *>(TheLuaScriptEngine)->rva0033321B((int)spyKey) == 0) {
		io_debug(state);
		return 0;
	}
	if (target->m_module258 != 0) {
		target->m_module258->rva002628C3(object, (int)eventKey, (int)spyKey);
	}
	return 0;
}
