// cl: /MD /GX
// ?update@DelayedLuaEventUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x004A8F52 240B
// Slot 0 of the +0x10 interface vftable 0x00C53A50 (ctor 0x004A8E7B stores it): relationship flags 2 and 6 when +0x74 plus bit0 when +0x75 via iterateObjectsInRange then Lua event 0x003360D2 then destroyObject; /G7 for or al 1.
// Evidence: vftable slot plus rowed callees plus ThePartitionManager plus TheGameLogic; finish from stash 0x004a8f52 (0.97) via G7.
class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Thing;
class ModuleData;

class Object
{
public:
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class GameLogic
{
public:
	void destroyObject(Object *obj);	// 0x00242C09
};
extern GameLogic *TheGameLogic;

class DelayedLuaEventList
{
public:
	DelayedLuaEventList();
	~DelayedLuaEventList();

private:
	unsigned char m_data[0x4C];
};

struct BfmeDelayedLuaEventList;
class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModuleBase
{
public:
	virtual ~UpdateModuleBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;		// +0x08
};

class UpdateModuleInterface1
{
public:
	virtual void slot1() = 0;
};

class UpdateModuleInterface2
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public UpdateModuleBase,
		     public UpdateModuleInterface1,
		     public UpdateModuleInterface2
{
protected:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class DelayedLuaEventUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

private:
	int m_event;			// +0x20
	DelayedLuaEventList m_events;	// +0x24
	float m_range;			// +0x70
	bool m_f74;			// +0x74
	bool m_f75;			// +0x75
};

UpdateSleepTime DelayedLuaEventUpdate::update()
{
	Object *obj = m_object;
	int flags = 2;
	if (m_f74)
		flags = 6;
	if (m_f75)
		flags |= 1;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&obj->m_pos, m_range, 0,
		Rva00260EB1Filter(obj, flags, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(obj))), 1);
	for (Object *other = hits.next(); other != 0; other = hits.next()) {
		if (other != obj)
			reinterpret_cast<BfmeObjectEventDispatch *>(TheLuaScriptEngine)->rva003360D2(m_event, (void *)other, (BfmeDelayedLuaEventList *)&m_events);
	}
	TheGameLogic->destroyObject(m_object);
	return UPDATE_SLEEP_NONE;
}
