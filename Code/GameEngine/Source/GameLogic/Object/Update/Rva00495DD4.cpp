// cl: /DNDEBUG /MD
//
// ?rva00495DD4@AutoPickUpUpdate@@QAE_NXZ, retail 0x00495DD4, 36 bytes.
// Identity: AutoPickUpUpdate scan-ready predicate. ModuleData at +4 carries
// ScanDelayTime at +8 and RunFromButton at +0x21 (see
// AutoPickUpUpdateModuleDataCtor layout: +8 ScanDelayTime, +0x21
// RunFromButton, +0x24 RunFromButtonNumber, +0x28
// CanScanWhileAttackingOrMoving). Behavior holds countdown at +0x24 and
// cached flag at +0x28 (see AutoPickUpUpdateCtor/Xfer: +0x24 uint, +0x28
// bool). If RunFromButton is set return m_28; if countdown is zero reload
// it from ScanDelayTime and return true; else decrement and return false.
// Evidence: offsets match ctor/xfer/dtor triple; caller at 0x00495E5C in
// AutoPickUpUpdate area.

struct AutoPickUpUpdateModuleData
{
	char m_pad00[8];
	int m_scanDelayTime; // +8
	char m_pad0C[4];
	float m_scanDistance; // +0x10
	char m_pad14[0x21 - 0x14];
	unsigned char m_runFromButton; // +0x21
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

bool AutoPickUpUpdate::rva00495DD4()
{
	const AutoPickUpUpdateModuleData *data = getAutoPickUpUpdateModuleData();
	if (data->m_runFromButton)
		return m_flag28;
	if (m_count24 == 0) {
		m_count24 = data->m_scanDelayTime;
		return true;
	}
	m_count24--;
	return false;
}
