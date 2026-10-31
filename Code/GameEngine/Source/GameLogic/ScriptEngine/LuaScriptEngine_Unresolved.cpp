// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHs /EHc- /arch:SSE /D_CRTIMP= /Ireference/shims/subsystem_bfme2
// Split from LuaScriptEngine.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// stlport
//
// Lua callbacks of BFME2's LuaScriptEngine.cpp: the file-name literal the two
// random-number bindings pass (VA 0x00C0DE00) reads
// "C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\
// ScriptEngine\LuaScriptEngine.cpp", and every body here is named by its
// registration: lua_pushcclosure (row @0x00747640) of the body's address
// followed by lua_setglobal (row @0x00747920) of the name string. The
// CurDrawable* names come from the drawable registration block
// (0x00335DC3..0x00335FB8), GetRandomNumber from the game registration at
// 0x00338782.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameLogic/ScriptEngine/
// LuaScriptEngine.cpp (revision 6583b3c1), which holds the BFME1 forms of
// GetClientRandomNumberReal, CurDrawableIsCurrentTargetKindof,
// CurDrawablePrevAnimationState and CurDrawablePrevAnimation. Target facts:
// the per-drawable Lua context sits at +0x9C of the Lua state global
// (+0x78 in BFME1), its drawable at +0x0C; the rest is read from the
// retail bodies, as noted per field.
#include "ascii_string.h"

struct lua_State;
extern "C" int lua_gettop(lua_State *state);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" const char *lua_tostring(lua_State *state, int index);
extern "C" void lua_pushnil(lua_State *state);
extern "C" void lua_pushstring(lua_State *state, const char *value);

typedef float Real;
typedef bool Bool;

Real GetGameClientRandomValueReal(Real low, Real high, char *file, int line);
Real GetGameLogicRandomValueReal(Real low, Real high, char *file, int line);

template<int Bits> class BitFlags
{
public:
	static int getSingleBitFromName(const char *name);
};

// Native callers examine the template query's bool result in AL.
enum KindOfType { KINDOF_INVALID = -1 };

class ThingTemplate
{
public:
	bool isKindOf(KindOfType bit) const;
	unsigned char isKindOf(int bit) const { return (unsigned char)isKindOf((KindOfType)bit); }
};

class Object
{
public:
	bool rva0028C149(int,float*,int);
	__forceinline unsigned char testStatus(int bit) const
	{
		return (m_status[(unsigned int)bit >> 5] & (1u << (bit & 31))) != 0;
	}

	char m_pad00[0x04];
	ThingTemplate *m_template;	// +0x04
	char m_pad08[0x94 - 0x08];
	unsigned int m_status[2];	// +0x94, tested with BitFlags<101> bits
	char m_pad9C[0x258 - 0x9C];
	void *m_ai258;
	char m_pad25C[0x398-0x25C];
	int m_currentTargetID;	// +0x398, passed to findObjectByID
};

enum ObjectID { INVALID_OBJECT_ID = 0 };


class Drawable
{
public:
	bool rva00278689(const AsciiString &name, bool a, bool b);
	void rva002724FD(const AsciiString &name, int show, int permanent, float c, float d);

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
public:
	AsciiString m_previousAnimationState; // +0x00
	AsciiString m_transitionAnimState; // +0x04
	AsciiString m_previousAnimation; // +0x08
	Drawable *m_drawable; // +0x0C
	float m_prevAnimFraction; // +0x10
	unsigned char m_allowToContinue; // +0x14
	char m_pad15[0x3];
};

// TheLuaScriptEngine (VA 0x00E01DBC, the subsystem initSubsystem<LuaScriptEngine>
// fills); only the current-drawable context it exposes to the callbacks.
extern "C" void __cdecl lua_close(void *L);
#include <stdlib.h>
// The game allocator's free at 0x00030830: retail calls it directly, not through the CRT import.
void Rva00030830GameFree(void *block);
struct Rva003378D0
{
	~Rva003378D0();
	char m_pad[12];
};
#include "subsystem_interface.h"
template <class T> struct Rva00337AA8Buf
{
	void *m_ptr;
	~Rva00337AA8Buf()
	{
		if (m_ptr != 0)
			Rva00030830GameFree(m_ptr);
	}
};
// Retail C0E390 has the fourteen canonical subsystem slots, followed by
// an empty hook, the name getter at337AA2 and the Version1 Xfer
// callback at306A9B (same RET4 ABI as the owned free DoXfer worker). The constructor3379FD and
// WB LuaScriptEngine dtor support identity; the address-derived type retains
// compatibility with the already-owned deleting dtor337C70.
enum ParticleSystemID { ParticleSystemIDUnknown = 0 };
class Rva003371B1;
struct BfmeOpaqueRecord156;
namespace _STL {
template<> ParticleSystemID *vector<ParticleSystemID>::erase(ParticleSystemID *,ParticleSystemID *);
template<> Rva003371B1 *vector<Rva003371B1>::erase(Rva003371B1 *,Rva003371B1 *);
template<> BfmeOpaqueRecord156 *vector<BfmeOpaqueRecord156>::erase(BfmeOpaqueRecord156 *,BfmeOpaqueRecord156 *);
}
struct BfmeStringRecord00063BE4;
class Rva00335C88
{
public:
	void *rva00335C88(void *,void *);
	char m_pad00[0x4];
private:
	BfmeStringRecord00063BE4 *m_04; // +0x04
};
struct Rva00337RangeView { void *start,*finish,*limit; };
class LuaScriptEngine : public SubsystemInterface
{
public:
	virtual ~LuaScriptEngine();
 virtual void init();
 virtual void reset();
 virtual void update() {}
 virtual void slot14() {}
 virtual const char *GetSnapshotName() const; virtual void DoXfer(Xfer *);
private:
	lua_State *m_luaState;
	lua_State *m_lua10;
	char m_pad14[0x9C - 0x14];
public:
	LuaDrawableLink *m_drawable;
private:
	Rva00337AA8Buf<void> m_scriptedEvents;
	char m_padA4[0xAC - 0xA4];
	bool m_sorted; char m_padAD[3];
	Rva003378D0 m_eventLists;
	Rva00337AA8Buf<void> m_modelConditionEvents;
	char m_padC0[0xC8 - 0xC0];
	// C8 is explicitly released by the dtor body; BC/A0 are automatic.
	void *m_objectStatusEvents; void *m_endCC, *m_limitD0;
};
// Retail VA 0x00E01DBC starts with four zero-filled bytes; the verified
// initSubsystem<LuaScriptEngine> caller registers the subsystem here.
extern LuaScriptEngine *TheLuaScriptEngine;

int GetClientRandomNumberReal(lua_State *state);

int CurDrawableAllowToContinue(lua_State *state);

int GetRandomNumber(lua_State *state);

int CurDrawableModelcondition(lua_State *state);

int CurDrawableObjectStatus(lua_State *state);

int CurDrawableHideSubObject(lua_State *state);

int CurDrawableShowSubObject(lua_State *state);

int CurDrawableHideSubObjectPermanently(lua_State *state);

int CurDrawableShowSubObjectPermanently(lua_State *state);

int CurDrawablePrevAnimationState(lua_State *state);

int CurDrawablePrevAnimation(lua_State *state);

int CurDrawableIsCurrentTargetKindof(lua_State *state);

extern "C" int lua_type(lua_State*,int);
struct Rva00990030Range;
unsigned int Rva00990030Lookup(Rva00990030Range*,int);
class AIUpdateInterface
{
public:
	int getCurrentStateID() const;
	void processSpies(int key, void *argument2, void *argument3);
	int rva002632C7( void ) const;
	void rva002632E1( void );
	unsigned char rva002632C7Bool( void ) const { return (unsigned char)rva002632C7(); }
	char m_pad00[0x20];
	char m_commandInterface[0x3C4 - 0x20]; // +0x20, this of the command helpers
	bool m_flag3C4; // +0x3C4, set from Fear's third argument
	bool m_forbid3C5; // +0x3C5 target fact, Bool byte store
};
int GetGameLogicRandomValue(int,int,char*,int);

int ObjectTestCanSufferFear(lua_State *L);


LuaScriptEngine::~LuaScriptEngine()
{
	if (m_luaState != 0)
	{
		lua_close(m_luaState);
		m_luaState = 0;
	}
	if (m_lua10 != 0)
	{
		lua_close(m_lua10);
		m_lua10 = 0;
	}
 if(m_objectStatusEvents) Rva00030830GameFree(m_objectStatusEvents);
}
