// cl: /DNDEBUG /MD /GX
//
// ??0WallHubBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00452E27,
// 154 bytes. BFME 2 module without a ZH counterpart. Target evidence: the
// body runs the rowed UpdateModule ctor 0x00253390, then the implicit ctor
// of an abstract interface at +0x20 (vtable 0x008633C0, every slot
// _purecall 0x0003B810), and stores the class vtables: 0x0083FDBC primary
// (slot 2 the rowed WallHubBehavior name getter 0x00452D72, slot 3 the
// rowed WallHubBehavior::xfer 0x00452F25, slot 4 the rowed pool key
// 0x00452DA3), 0x0084B1E0 for UpdateModuleInterface and 0x0083FD80 for
// the interface. It wakes at once, then, given module data, registers the
// interface with its object under the data's +0x34 key through the rowed
// insert-if-absent 0x00295927 (the map at Object +0x268) and copies the
// data's +0x2C float to +0x24, taking the object's +0xB8 float instead when
// the data holds the 9.876 sentinel (constant 0x0083FD78).
typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Image;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Object
{
public:
	Real getBfmeB8() const { return m_bfmeB8; }
private:
	unsigned char m_pad00[0xB8];
	Real m_bfmeB8; // +0xB8
};

// Object's keyed-interface map insert at 0x00295927, rowed under an
// address name.
class Rva00295927
{
public:
	void rva00295927(unsigned int key, Image *value);
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

// The abstract interface at +0x20; its vtable holds five methods and the
// trailing slot.
class WallHubInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
};

class WallHubBehaviorModuleData
{
public:
	unsigned char m_pad00[0x2C];
	Real m_2c; // +0x2C
	unsigned char m_pad30[0x34 - 0x30];
	UnsignedInt m_34; // +0x34
};

class WallHubBehavior : public UpdateModule, public WallHubInterface
{
public:
	WallHubBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~WallHubBehavior();
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
private:
	const WallHubBehaviorModuleData *getWallHubBehaviorModuleData() const { return (const WallHubBehaviorModuleData *)m_moduleData; }

	Real m_24; // +0x24
};

WallHubBehavior::WallHubBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
	const WallHubBehaviorModuleData *data = getWallHubBehaviorModuleData();
	if (data)
	{
		((Rva00295927 *)getObject())->rva00295927(data->m_34, (Image *)static_cast<WallHubInterface *>(this));
		m_24 = data->m_2c;
		if (m_24 == 9.876f)
			m_24 = getObject()->getBfmeB8();
	}
}
