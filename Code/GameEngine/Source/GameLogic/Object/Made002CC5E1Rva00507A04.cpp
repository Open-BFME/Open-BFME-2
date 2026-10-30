// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /ICode/GameEngine/Source/Common /ICode
//
// ?v4@DamageNugget@@UAEXPAX0@Z retail 0x00507A04..0x00507BB7 (435B): vtable
// slot 4 of 0x00864048/0x00864C38/0x008650B8, reached from slot 3 0x0050797D.
// Spawns TheWritableGlobalData->m_luaEventHelperName through ThingFactory and
// arms DelayedLuaEventUpdate; same view as Made002CC5E1Rva00507991.cpp.
// Exact via W7-D3 sweepeq4x equal-arm on request->m_frame (frame slot ranking).
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"

#include <string.h>

template <class T> inline const T &Made002CC5E1Max(const T &a, const T &b) { return a < b ? b : a; }

class DamageNugget;
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

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void setProducer(Object *producer);
	ObjectID getID() const { return m_id; }
protected:
	Module *findModule(NameKeyType key) const;
	friend class DamageNugget;
private:
	unsigned char m_pad060[0x74 - 0x60];
	ObjectID m_id; // +0x74
};

enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, ObjectID flag);
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

class DelayedLuaEventList
{
public:
	DelayedLuaEventList();
	virtual ~DelayedLuaEventList();
	unsigned char m_pad00[0xC];
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

class DamageNugget : public Rva00507823
{
public:
	virtual ~DamageNugget();
	virtual bool v1(void *a, void *b);
	virtual bool rva00507943(const void *a, int b);
	virtual void rva0050797D(void *a, void *b);
	virtual void v4(void *a, void *position);
private:
	float m_128;
	float m_12C;
	float m_130;
};

void DamageNugget::v4(void *a, void *position)
{
	const AsciiString &helperName = TheWritableGlobalData->m_luaEventHelperName;
	if (((const StringBase<char> *)&helperName)->isEmpty())
		return;
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(helperName);
	if (!thingTemplate)
		return;
	Made002CC5E1Request *request = (Made002CC5E1Request *)a;
	Object *source = TheGameLogic->findObjectByID(request->m_objectID);
	if (!source)
		return;
	CreateMask mask;
	memset(&mask, 0, sizeof(mask));
	Team *team = source->getControllingPlayer()->m_defaultTeam;
	Object *helper = TheThingFactory->newObject(thingTemplate, team, &mask, (ObjectID)0);
	helper->setProducer(source);
	helper->setPosition((const struct Coord3D *)position);
	static NameKeyType key = TheNameKeyGenerator->nameToKey("DelayedLuaEventUpdate");
	DelayedLuaEventUpdate *update = (DelayedLuaEventUpdate *)helper->findModule(key);
	if (!update)
	{
		TheGameLogic->destroyObject(helper);
		return;
	}
	unsigned int frames = (update ? (request->m_frame) : (request->m_frame)) - TheGameLogic->getFrame();
	bool flag1 = request->m_source->m_flags.m_flag1;
	bool flag2 = request->m_source->m_flags.m_flag2;
	DelayedLuaEventList events;
	events.m_objectID = source->getID();
	events.m_kind = 3;
	events.m_delay = (float)frames;
	events.m_value = m_128;
	events.m_30 = 1;
	events.m_48 = 1;
	update->rva004A8F0B(9, (const DelayedLuaEventList &)events, UPDATE_SLEEP_NONE,
		Made002CC5E1Max(1.0f, m_130), flag1, flag2);
}
