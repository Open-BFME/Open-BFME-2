// cl: /O1 /GX /DNDEBUG /MD
// stlport
//
// ??0OilSpillUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0048C1F7,
// 97 bytes. Behavior-side ctor over the pinned FireWeaponUpdate base
// (0x48C0C5): the implicit _STL::vector<int> member at +0x2C builds through
// the folded Vector_base at 0x211E58 (int spelling reuses the existing pin;
// MineshaftPortalBehaviour precedent: only compiler stores split
// setup/call), then setWakeFrame through the pinned 0x44DF71. Two EH
// states (base + vector): the base carries a declared-only virtual dtor
// (Devastate-V5 precedent: unwindable with no code, links via vtable).
// Class size 0x38 proven by the rowed instance factory (news 0x38, sole
// caller at 0x24CFA7). Row supersedes the ctor pin.

#include <vector>

class Thing;
class ModuleData;
class Object;

class FireWeaponBaseA
{
	virtual void unusedA();
	int m_a0;

protected:
	void *m_owner08;
};

class FireWeaponBaseB
{
	virtual void unusedB();
};

class FireWeaponBaseC
{
	virtual void unusedC();
};

class FireWeaponUpdate : public FireWeaponBaseA, public FireWeaponBaseB, public FireWeaponBaseC
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponUpdate();

protected:
	void setWakeFrame(Object *obj, unsigned int frames);

private:
	unsigned char m_pad14[0x2C - 0x14];
};

class OilSpillUpdate : public FireWeaponUpdate
{
public:
	OilSpillUpdate(Thing *thing, const ModuleData *moduleData);

private:
	_STL::vector<int> m_items2C;
};

// ??0OilSpillUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0048C1F7
OilSpillUpdate::OilSpillUpdate(Thing *thing, const ModuleData *moduleData)
	: FireWeaponUpdate(thing, moduleData)
{
	setWakeFrame(reinterpret_cast<Object *>(m_owner08), 1);
}
