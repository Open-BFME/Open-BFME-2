// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /MD /EHsc
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
class ThingTemplate;
class Player;
class Drawable;
class SpecialPowerModuleInterface;
enum SpecialPowerType { SPECIAL_POWER_TYPE_UNKNOWN = 0 };
#include "Common/BfmeAudioEventPrefix136.h"
// PC Lua registrations identify both handlers (audit lua-bindings.json).
// Reference guides: BFME1 CurDrawablePlaySound.cpp and ObjectPlaySound.cpp
// at6583b3c1ff21db4a561285717028fdafc780b7db. PC changes: Lua context+9C,
// resolve name through audio slot12C before construction, use canonical136B
// event prefix and audio add slot64. Unknown event returns0 for drawable,
// and1 without pushing a value for object, as the PC control flow establishes.
// Owners and event arguments are verified by the native constructor edges;
// the target-neutral prefix/reference identities are deliberately retained.
struct lua_State;
extern "C" int lua_gettop(lua_State *);
extern "C" int lua_type(lua_State *,int);
extern "C" const char *lua_tostring(lua_State *,int);
extern "C" void lua_pushnil(lua_State *);
extern "C" void lua_pushnumber(lua_State *,double);
struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *,int);
class Rva0036CA00Str {
public:
 OpaqueRefCounted *m_item;
 ~Rva0036CA00Str() { if(m_item) m_item->Release_Ref(); }
};
#include "../../Common/GameLogicObjectLookupView.h"
enum DrawableID { INVALID_DRAWABLE_ID=0 };
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
struct LuaDrawableState {char m_pad[0x9C]; LuaDrawableLink *m_drawable;};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
extern GameLogic *TheGameLogic;
class AudioManager {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot0a();
 virtual void slot0b();
 virtual void slot0c();
 virtual void slot0d();
 virtual void slot0e();
 virtual void slot0f();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual unsigned int addAudioEvent(const BfmeAudioEventPrefix136 *);
 virtual void slot1a();
 virtual void slot1b();
 virtual void slot1c();
 virtual void slot1d();
 virtual void slot1e();
 virtual void slot1f();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot2a();
 virtual void slot2b();
 virtual void slot2c();
 virtual void slot2d();
 virtual void slot2e();
 virtual void slot2f();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot3a();
 virtual void slot3b();
 virtual void slot3c();
 virtual void slot3d();
 virtual void slot3e();
 virtual void slot3f();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot4a();
 virtual Rva0036CA00Str rvaSlot12C(const AsciiString &);
};
extern AudioManager *TheAudio;
int CurDrawablePlaySound(lua_State *state) {
 LuaDrawableLink *selection=((LuaDrawableState*)TheLuaScriptEngine)->m_drawable;
 Drawable *drawable;
 if(!selection || !(drawable=selection->m_drawable) || lua_gettop(state)<=0 || !TheAudio) return 0;
 Rva0036CA00Str sound=TheAudio->rvaSlot12C(AsciiString(lua_tostring(state,1)));
 if(!sound.m_item) return 0;
 {
  BfmeAudioEventPrefix136 event((const OpaqueRefElement4&)sound,drawable->getID());
  TheAudio->addAudioEvent(&event);
 }
 return 0;
}
int ObjectPlaySound(lua_State *state) {
 if(lua_gettop(state)<2 || !TheAudio) return 0;
 unsigned id=Rva00990030Lookup((Rva00990030Range*)state,1);
 if(!id && lua_type(state,1)!=1) return 0;
 Object *object=TheGameLogic->findObjectByID((ObjectID)id);
 if(!object) return 0;
 Rva0036CA00Str sound=TheAudio->rvaSlot12C(AsciiString(lua_tostring(state,2)));
 if(!sound.m_item) return 1;
 {
  BfmeAudioEventPrefix136 event((const OpaqueRefElement4&)sound,object->m_id);
  unsigned int handle=TheAudio->addAudioEvent(&event);
  if(handle>=5) lua_pushnumber(state,(float)handle);
  else lua_pushnil(state);
 }
 return 1;
}
