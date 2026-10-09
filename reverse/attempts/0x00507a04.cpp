// ?v4@Made002CC5E1@@UAEXPAX0@Z
// partial score=0.75 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /ICode/GameEngine/Source/Common
// ?v4@Made002CC5E1@@UAEXPAX0@Z
// Retail 0x00507A04..0x00507BB7 (435 bytes); vtable slot 4 of 0x00864048
// (Made002CC5E1), 0x00864C38 and 0x008650B8, reached from slot 3
// (0x0050797D) with the second argument's +0x38.
// Spawns the global-data helper object (TheGlobalData +0x18 template name)
// for the source object of the request (+0x08 id) at the given position with
// the source as producer on the source's controlling player's team, and arms
// its DelayedLuaEventUpdate: event kind 3 for the source object's id after
// the frames left until the request's frame (+0x1C), with this nugget's +0x128
// value and max(1, +0x130) as the delay scale; the two flags come from bits
// 1 and 2 of the request's +0x04 +0x110 word. Without that module the helper
// is destroyed again.
// Evidence (target): string "DelayedLuaEventUpdate"; rowed callees
// StringBase<char>::isEmpty ThingFactory::findTemplate (pin 0x002D06CA)
// GameLogic::findObjectByID Object::getControllingPlayer ThingFactory::newObject
// (pin) Object::setProducer Thing::setPosition NameKeyGenerator::nameToKey
// Object::findModule (pin) GameLogic::destroyObject DelayedLuaEventList
// ctor 0x000B6D8B / dtor 0x000B6DD2 (pins) and
// DelayedLuaEventUpdate::rva004A8F0B 0x004A8F0B; nugget fields +0x128/+0x130
// as in Made002CC5E1Rva00507991.cpp. WorldBuilder 0x0109F6E0 has the same
// calls. The method keeps the sibling unit's v4 slot name.
// NEAR (banked, ~0.75; 440 vs 435 bytes): the flow, calls, the static key
// guard, the bit-field flags, the event-list fields and the max(1, +0x130)
// reference all match. Register allocation differs: retail keeps the
// template in ebx, the request in esi and the source in edi with the helper
// in the dead argument slot, and loads TheGameLogic once for both the destroy
// path and the frame difference; this source puts the template/helper in esi,
// the request in edi and spills the source. Tried: request local first, a
// separately declared helper.
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"

extern "C" void *__cdecl memset(void *dst, int value, unsigned int count);

template <class T> inline const T &Made002CC5E1Max(const T &a, const T &b) { return a < b ? b : a; }

class ThingTemplate;
class Team;
class Module;
enum NameKeyType { NAMEKEY_INVALID = 0 };

struct CreateMask
{
	unsigned char m_data[0x10];
};

class Player
{
public:
	unsigned char m_pad000[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

class Thing
{
public:
	void setPosition(const struct Coord3D *pos);
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void setProducer(Object *producer);
	Module *findModule(NameKeyType key) const;
	ObjectID getID() const { return m_id; }
private:
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag);
};
extern ThingFactory *TheThingFactory;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GlobalData
{
public:
	unsigned char m_pad00[0x18];
	AsciiString m_luaEventHelperName; // +0x18
};
extern GlobalData *TheWritableGlobalData;

extern GameLogic *TheGameLogic;

class BfmeDelayedLuaEventList
{
public:
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();
	unsigned char m_pad00[0x10];
	ObjectID m_objectID;     // +0x10
	int m_14;
	int m_kind;              // +0x18
	int m_1C;
	float m_delay;           // +0x20
	unsigned char m_pad24[0x30 - 0x24];
	int m_30;                // +0x30
	int m_34;
	float m_value;           // +0x38
	unsigned char m_pad3C[0x48 - 0x3C];
	int m_48;                // +0x48
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 0 };

class DelayedLuaEventList;
class DelayedLuaEventUpdate
{
public:
	void rva004A8F0B(unsigned int f20, const DelayedLuaEventList &events, UpdateSleepTime sleep, float f70, bool f74, bool f75);
};

struct Made002CC5E1Flags
{
	unsigned int m_bit0 : 1;
	unsigned int m_flag1 : 1;
	unsigned int m_flag2 : 1;
};

struct Made002CC5E1Source
{
	unsigned char m_pad000[0x110];
	Made002CC5E1Flags m_flags; // +0x110
};

struct Made002CC5E1Request
{
	void *m_00;
	Made002CC5E1Source *m_source; // +0x04
	ObjectID m_objectID;          // +0x08
	unsigned char m_pad0C[0x1C - 0x0C];
	unsigned int m_frame;         // +0x1C
};

class Rva00507823
{
public:
	virtual ~Rva00507823();
private:
	char m_pad04[0x128 - 4];
};

class Made002CC5E1 : public Rva00507823
{
public:
	virtual ~Made002CC5E1();
	virtual bool v1(void *a, void *b);
	virtual bool rva00507943(const void *a, int b);
	virtual void rva0050797D(void *a, void *b);
	virtual void v4(void *a, void *b);
private:
	float m_128;
	float m_12C;
	float m_130;
};

void Made002CC5E1::v4(void *a, void *b)
{
	const AsciiString &helperName = TheWritableGlobalData->m_luaEventHelperName;
	if (((const StringBase<char> *)&helperName)->isEmpty())
		return;
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(helperName);
	if (!tmpl)
		return;
	Made002CC5E1Request *request = (Made002CC5E1Request *)a;
	Object *source = TheGameLogic->findObjectByID(request->m_objectID);
	if (!source)
		return;
	CreateMask mask;
	memset(&mask, 0, sizeof(mask));
	Team *team = source->getControllingPlayer()->m_defaultTeam;
	Object *helper = TheThingFactory->newObject(tmpl, team, &mask, false);
	helper->setProducer(source);
	helper->setPosition((const struct Coord3D *)b);
	static NameKeyType key = TheNameKeyGenerator->nameToKey("DelayedLuaEventUpdate");
	DelayedLuaEventUpdate *update = (DelayedLuaEventUpdate *)helper->findModule(key);
	if (!update)
	{
		TheGameLogic->destroyObject(helper);
		return;
	}
	unsigned int frames = request->m_frame - TheGameLogic->getFrame();
	bool flag1 = request->m_source->m_flags.m_flag1;
	bool flag2 = request->m_source->m_flags.m_flag2;
	BfmeDelayedLuaEventList events;
	events.m_objectID = source->getID();
	events.m_kind = 3;
	events.m_delay = (float)frames;
	events.m_value = m_128;
	events.m_30 = 1;
	events.m_48 = 1;
	update->rva004A8F0B(9, (const DelayedLuaEventList &)events, UPDATE_SLEEP_NONE,
		Made002CC5E1Max(1.0f, m_130), flag1, flag2);
}
