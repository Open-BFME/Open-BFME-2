// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfmealloc /Ireference/shims/bfmelist -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
class ThingTemplate;
class Player;
class Drawable;
class SpecialPowerModuleInterface;
enum SpecialPowerType { SPECIAL_POWER_TYPE_UNKNOWN = 0 };
// ?ObjectModifyUpgrade@LuaScriptEngine@@SAHPAUlua_State@@_N@Z, retail 0x003354D6 220B.
// Gap between CreateAndFire 0x0033541C and HasUpgrade 0x003355B2, same flags.
// Grants/removes player or object upgrades by bool arg.
// Evidence: rowed lua_gettop 0x00746F30, rowed Rva00990030Lookup 0x00747190,
// rowed lua_type 0x007470A0, rowed findObjectByID 0x00049DC5,
// rowed lua_tostring 0x007473B0, rowed StringBase ctor 0x00037BA0,
// rowed findUpgrade 0x0026F26D, rowed releaseBuffer 0x00036410,
// rowed getControllingPlayer 0x0028AFA9, rowed Player addUpgrade 0x002AE329,
// rowed Player removeUpgrade 0x002ADAC3, rowed Object rva00293077 0x00293077,
// rowed Object removeUpgrade 0x00290D42.
#include "ascii_string.h"

struct lua_State;
extern "C" int lua_gettop(lua_State *s);
extern "C" int lua_type(lua_State *s, int i);
extern "C" const char *lua_tostring(lua_State *s, int i);

struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *r, int i);

#include "../../Common/GameLogicObjectLookupView.h"
class Object;
class Player;
class Upgrade;
class UpgradeTemplate;
enum UpgradeStatusType { UPGRADE_STATUS_02 = 2 };
typedef int Int;

extern GameLogic *TheGameLogic;

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

class Upgrade;
class UpgradeTemplate;
struct BfmeSideHolder
{
	void *m_data;
};

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

class UpgradeTemplate
{
public:
	int m_00;
	int m_type;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &n) const;
};
extern UpgradeCenter *TheUpgradeCenter;

// Static callback view only; this helper reads no LuaScriptEngine object.
// WB C06AD0 ObjectModifyUpgrade has the same two stack arguments, complete
// grant/remove control flow and retail call targets; native 3354D6..3355B2.
typedef unsigned char Bool;
#include <stdlib.h>
#include "subsystem_interface.h"
struct lua_State;
class Object;
class BfmeLexEAN;
class XmlNameSlotList;
struct LuaDrawableLink;
struct Rva003378D0
{
	~Rva003378D0();
	char m_pad[12];
};

template <class T> struct Rva00337AA8Buf
{
	void *m_ptr;
	~Rva00337AA8Buf()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
};
class LuaScriptEngine : public SubsystemInterface
{
public:
	LuaScriptEngine();
	virtual ~LuaScriptEngine();
 virtual void init();
 virtual void reset();
 virtual void update() {}
 virtual void slot14() {}
 virtual const char *GetSnapshotName() const; virtual void DoXfer(Xfer *);

 void ExecuteChunk(char *buff, int size, const AsciiString &chunk);
 void LoadScripts(const char *filename);
 void DispatchEvent(int *key, Object *object, void *parameters);
 void DispatchSpyEvent(int key, void *object, void *spy, void *parameters);
 void PushObjectTable(lua_State *state, Object *object);
 static int ObjectDescription(lua_State *state);
 static int ObjectModifyUpgrade(lua_State *state, bool grant);
 static int HordeBroadcastEventToMembers(lua_State *state);
 void ProcessEventsElement(BfmeLexEAN *parser);
 void ProcessInternalEvent(XmlNameSlotList *xml);
 void rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser);
 void ProcessScriptedEvent(XmlNameSlotList *xml);
 void rva002E9680ParseModelConditionEvent(BfmeLexEAN *parser);
 void ProcessSageElement(BfmeLexEAN *parser);
 void ProcessEventList(BfmeLexEAN *parser);
 void LoadXML(const char *filename, bool keepOpen);
 void rva003387DC(const AsciiString &mapName);
 void rva00338317RegisterScriptFunctions();
private:
	lua_State *m_luaState;
	lua_State *m_lua10;
	char m_pad14[0x9C - 0x14];
public:
	LuaDrawableLink *m_drawable;
private:
	Rva00337AA8Buf<void> m_bufA0;
	char m_padA4[0xAC - 0xA4];
	bool m_flagAC; char m_padAD[3];
	Rva003378D0 m_vecB0;
	Rva00337AA8Buf<void> m_bufBC;
	char m_padC0[0xC8 - 0xC0];
	// C8 is explicitly released by the dtor body; BC/A0 are automatic.
	void *m_bufC8; void *m_endCC, *m_limitD0;
 int m_depth; // +0xD4
 unsigned char m_keepOpen; // +0xD8
 char m_padD9[3];
 int m_singleStepKey; // +0xDC
};

int LuaScriptEngine::ObjectModifyUpgrade(lua_State *luaState, bool grant)
{
	if (lua_gettop(luaState) < 2)
		return 0;
	unsigned id = Rva00990030Lookup((Rva00990030Range *)luaState, 1);
	if (id == 0 && lua_type(luaState, 1) != 1)
		return 0;
	Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
	if (obj == 0)
		return 0;
	const char *upName = lua_tostring(luaState, 2);
	const UpgradeTemplate *tpl;
	{
		AsciiString tmp(upName);
		tpl = TheUpgradeCenter->findUpgrade(tmp);
	}
	if (tpl == 0)
		return 0;
	if (tpl->m_type == 0) {
		Player *player = obj->getControllingPlayer();
		if (grant != 0) {
			player->addUpgrade(tpl, (UpgradeStatusType)2, 0);
		} else {
			player->removeUpgrade(tpl, 0);
		}
	} else {
		if (grant != 0) {
			obj->rva00293077(tpl);
		} else {
			obj->removeUpgrade(tpl);
		}
	}
	return 1;
}

// ?ObjectGrantUpgrade@@YAHPAUlua_State@@@Z, retail 0x00335692 14B: the Lua
// callback registration 0x003386BF names ObjectGrantUpgrade (pushcclosure
// then setglobal); it forwards to the shared worker above with grant=true.
int ObjectGrantUpgrade(lua_State *luaState)
{
	return LuaScriptEngine::ObjectModifyUpgrade(luaState, true);
}

// ?ObjectRemoveUpgrade@@YAHPAUlua_State@@@Z, retail 0x003356A0 14B: the Lua
// callback registration 0x003386DA names ObjectRemoveUpgrade; same worker
// with grant=false.
int ObjectRemoveUpgrade(lua_State *luaState)
{
	return LuaScriptEngine::ObjectModifyUpgrade(luaState, false);
}
