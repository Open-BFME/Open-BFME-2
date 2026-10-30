// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
//
// ??0RadiateFearUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0049C106,
// 115 bytes. Behavior-side ctor (rowed instance factory 0x24E6B0 news
// 0x28 with this pinned 2-arg ctor as its sole raw caller at 0x24E6D7).
//
// Shape follows the SlaveWatcherBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, an UpgradeMux base at +0x20 built in the init-list (rowed
// 0-arg ctor 0x4CE2A3; member layout mirrors UpgradeModuleCtor.cpp), the
// setWakeFrame arg pushes above the stores (no intervening call), the
// three derived vtable installs, a vtable overwrite of the base, the
// setWakeFrame tail (protected IAEX Object-uint spelling resolves via the
// existing pin at 0x44DF71), and a conditional self-upgrade on the module
// data flag at +0x08 (rowed giveSelfUpgrade 0x45230C). Row supersedes the
// ctor pin.

// folded vftable 0x00C49F78 (3 classes), by its data-ledger name ("??_7AttributeModifierAuraUpdate@@6BBehaviorModuleInterface@@@")
// vftable 0x00C50F68 ("??_7Rva0049BFB7@@6B@")
// vftable 0x00C50FB0 ("??_7Rva0049BFB7@@6BRva0024A797_B2@@@")
// vftable 0x00C50FBC ("??_7Rva0049BFB7@@6BRva0024A797_Root@@@")

// base dtor, an UpgradeMux member at +0x20 built in the init-list (rowed
// three derived vtable installs, a vtable overwrite of the member, the
enum NameKeyType { NK_UNKNOWN = 0 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };
class Thing;
class ModuleData;
class Object;
#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };

class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class RadiateFearUpdate;

class UpgradeMux
{
	friend class RadiateFearUpdate;
public:
	UpgradeMux();
	void giveSelfUpgrade();
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class RadiateFearUpdate : public UpdateModule, public UpgradeMux
{
public:
	RadiateFearUpdate(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual void xfer(Xfer *xfer);
};

template <int N> class BitFlags;

extern BitFlags<116> KINDOFMASK_NONE;

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D storage);
private:
	int m_filterData; // +0x00
};

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();
};

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
};

class RadiateFearUpdateModuleData : public UpdateModuleData
{
	friend class RadiateFearUpdate;
public:
	RadiateFearUpdateModuleData();

private:
	void *m_vtable; // +0x00
	int m_unused04; // +0x04
	bool m_initiallyActive; // +0x08
	char m_pad09[3];
	int m_whichSpecialPower; // +0x0C
	unsigned char m_generateTerror; // +0x10
	unsigned char m_generateFear; // +0x11
	unsigned char m_generateUncontrollableFear; // +0x12
	unsigned char m_pad13;
	float m_emotionPulseRadius; // +0x14
	int m_emotionPulseInterval; // +0x18
	Rva003623E5Filter m_victimFilter; // +0x1C
	Rva0025342CMember m_20; // +0x20
	unsigned char m_pad[0x130 - 0x20 - 4];
};

// ??0RadiateFearUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0049C106
RadiateFearUpdate::RadiateFearUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), UpgradeMux()
{
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
	const RadiateFearUpdateModuleData *data = (const RadiateFearUpdateModuleData *)m_moduleData;
	if (data->m_initiallyActive)
		giveSelfUpgrade();
}
