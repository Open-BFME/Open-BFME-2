// cl: /DNDEBUG /MD
//
// ?rva00495C6E@AutoPickUpUpdate@@UAEXXZ, retail 0x00495C6E, 9 bytes: slot 2 of
// the vtable 0x00C4EF90 that AutoPickUpUpdate's ctors (0x00495C5C, 0x00495D77)
// install at +0x20; raises the bytes at +0x28 and +0x29. Compiled with the
// +0x20 subobject this. Names by address.
struct AutoPickUpUpdateModuleData
{
	char m_pad00[0x10];
	float m_scanDistance;
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };

class Object;
class Thing;
class ModuleData;
class Xfer;
enum NameKeyType;
#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModule : public ObjectModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class AutoPickUpUpdateInterface
{
public:
	virtual void anchor() = 0;
	virtual void slot1() = 0;
	virtual void rva00495C6E() = 0;
};

class AutoPickUpUpdate : public UpdateModule, public AutoPickUpUpdateInterface
{
public:
	AutoPickUpUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AutoPickUpUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual void rva00495C6E();
	virtual UpdateSleepTime update();
	bool rva00495DD4();__forceinline float getScanRange()const{return getAutoPickUpUpdateModuleData()->m_scanDistance;}

	const AutoPickUpUpdateModuleData *getAutoPickUpUpdateModuleData() const
	{
		return (const AutoPickUpUpdateModuleData *)m_moduleData;
	}
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_count24;
	bool m_flag28;
	bool m_flag29;
};

void AutoPickUpUpdate::rva00495C6E()
{
	m_flag28 = true;
	m_flag29 = true;
}
