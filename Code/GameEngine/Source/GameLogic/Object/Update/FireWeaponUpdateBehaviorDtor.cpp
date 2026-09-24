// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// stlport
//
// ??1FireWeaponUpdate@@UAE@XZ, retail 0x0048BD11, 156 bytes. Behavior-side
// dtor completing the FireWeaponUpdate file-unit (behavior ctor rowed at
// 0x48C0C5 over the same model; poolkey + instance factory rowed).
//
// Shape: EH prolog plus three explicit vtable installs (+0/+0xC/+0x10) plus
// a watch-list drain loop (per value: release helper + operator delete +
// list remove) plus a tracked-pointer virtual release (slot0 with 0,
// return-fed operator delete) plus implicit list-base-dtor and base-dtor
// calls. The release helper rides as an Rva pin (value-this, do-not-name).

#include <list>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Thing;
class ModuleData;
class Object;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
};

struct FireWeaponTracked
{
	virtual void *deleteInstance(int flags);
};

class FireWeaponUpdate : public UpdateModule
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponUpdate();
	void Rva0048B95FHelper();
private:
	// No explicit m_vtable: the compiler installs the virtual-dtor vptr at
	// +0 in dtor entry (DIR32-masked, matches retail's first install).
	const ModuleData *m_moduleData;		// +4
	Object *m_object;					// +8
	const void *m_secondary0C;			// +0xC
	const void *m_secondary10;			// +0x10
	unsigned int m_nextCallFrameAndPhase;	// +0x14
	int m_indexInLogic;					// +0x18
	int m_reserved1C;					// +0x1C
	FireWeaponTracked *m_tracked;		// +0x20
	_STL::list<int> m_trackedIds;		// +0x24
	unsigned char m_weaponsReady;		// +0x28
};

// ??1FireWeaponUpdate@@UAE@XZ @0x0048BD11
FireWeaponUpdate::~FireWeaponUpdate()
{
	*(const void **)((char *)this + 0x0C) = (const void *)0x00BEFF90;
	*(const void **)((char *)this + 0x10) = (const void *)0x00C4C18C;
	_STL::list<int> *trackedIds = &m_trackedIds;
	_STL::list<int>::iterator it = trackedIds->begin();
	while (it != trackedIds->end()) {
		int trackedValue = *it;
		++it;
		if (trackedValue != 0) {
			((FireWeaponUpdate *)trackedValue)->Rva0048B95FHelper();
			::operator delete((void *)trackedValue);
		}
		trackedIds->remove(trackedValue);
	}
	if (m_tracked != 0) {
		::operator delete(m_tracked->deleteInstance(0));
	}
}
