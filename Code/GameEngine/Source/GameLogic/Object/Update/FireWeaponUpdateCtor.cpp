// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// stlport
//
// ??0FireWeaponUpdate@@QAE@PAVThing@@PBVModuleData@@@Z retail 0x0048C0C5
// 112 bytes. Behavior-side ctor completing the FireWeaponUpdate file-unit
// (behavior instance factory rowed at 0x24CF1E news 0x2C with this 2-arg
// ctor as its caller; FireWeaponUpdate poolkey rowed at 0x48BDB3; ModuleData
// proc 0x48C0B4 is the opaque Hero-side base link).
//
// Shape: EH prolog plus UpdateModule base call 0x253390 plus three explicit
// vtable installs (+0/+0xC/+0x10) plus a runtime watch list plus setWakeFrame
// tail (frame literal 1). The vtable installs must precede the list-base
// row (0x4EC36C), but body statements run after all member inits, so the
// TU uses an empty UpdateModule base (inline-empty ctor plus
// declared-only dtor, bracketing EH states with zero code) with every data
// member redeclared in declaration order on the derived class and
// initialized in the init-list: the RMW-and of m_20 hoists to the front
// (PassiveAreaEffect precedent), the vtable stores keep init-list position
// ahead of the implicit list construction, and the list resolves through
// the rowed _List_base int spelling (the four alias pins at 0x4EC36C prove
// the fold; element type follows the PassiveAreaEffect watch-list
// precedent). Member names are behavior-state inferred from the zero-init
// layout; no donor names them. Row supersedes the ctor pin (surgical
// delete, same commit); the single-caller 0x48BDF8 helper rides as an
// opaque Rva pin (do-not-name note).

#include <list>

class Thing;
class ModuleData;
class Object;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *object, unsigned int frame);
};

class FireWeaponUpdate : public UpdateModule
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	void Rva0048BDF8Helper(void);

private:
	const void *m_vtable;				// +0
	const ModuleData *m_moduleData;		// +4
	Object *m_object;					// +8
	const void *m_secondary0C;			// +0xC
	const void *m_secondary10;			// +0x10
	unsigned int m_nextCallFrameAndPhase;	// +0x14
	int m_indexInLogic;					// +0x18
	int m_reserved1C;					// +0x1C
	int m_weaponState;					// +0x20
	_STL::list<int> m_trackedIds;		// +0x24, runtime watch list
	unsigned char m_weaponsReady;		// +0x28
};

// ??0FireWeaponUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0048C0C5
FireWeaponUpdate::FireWeaponUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_vtable(reinterpret_cast<const void *>(0x00C4C198))
	, m_secondary0C(reinterpret_cast<const void *>(0x00BEFF90))
	, m_secondary10(reinterpret_cast<const void *>(0x00C4C18C))
	, m_weaponState(0)
	, m_weaponsReady(0)
{
	Rva0048BDF8Helper();
	Object **objSlot = &m_object;
	setWakeFrame(*objSlot, 1);
}
