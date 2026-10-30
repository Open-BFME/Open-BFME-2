// RemoveUpgradeUpgradeView.h: the one view of RemoveUpgradeUpgrade, its
// UpgradeModule bases and its ModuleData, shared by RemoveUpgradeUpgrade.cpp
// and the donors that merge into it. Layout: BehaviorModule +0 (vptr,
// m_moduleData +4, m_object +8), BehaviorModuleInterface +0xC, UpgradeMux
// +0x10 (state +0x14), UpgradeTail +0x18 (size 0x1C); retail ctor 0x004B7FA4
// and dtor 0x004B7F01 store the four vptrs at +0/+0xC/+0x10/+0x18.
#ifndef REMOVEUPGRADEUPGRADEVIEW_H
#define REMOVEUPGRADEUPGRADEVIEW_H

#include <vector>
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

class Thing;
class Object;
class ModuleData;

// Retail dtor 0x004B8050 stores no derived vptr, so the class is novtable
// over the canonical Snapshot.
class __declspec(novtable) RemoveUpgradeUpgradeModuleData : public Snapshot
{
public:
	virtual ~RemoveUpgradeUpgradeModuleData();

private:
	// Opaque inherited storage between Snapshot's vptr and the two vectors.
	// The constructor's 0x118-byte base fixes this extent; its hierarchy is
	// not reconstructed by this view.
	unsigned char m_unrecoveredBase04[0x118 - 4];
	_STL::vector<AsciiString> m_upgradeToRemove; // +0x118
	_STL::vector<AsciiString> m_upgradeGroupsToRemove; // +0x124
	unsigned char m_suppressEvaEventForRemoval; // +0x130
	unsigned char m_removeFromAllPlayerObjects; // +0x131
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

struct BehaviorModuleInterface { virtual void iface() {} };

// UpgradeMux interface at +0x10: slot 8 upgradeRemovalImplementation, slot 9
// setUpgradeExecuted, slot 10 upgradeImplementation.
class UpgradeMux
{
public:
	UpgradeMux();
	virtual bool executed() const = 0;
	virtual void f1() = 0; virtual void f2() = 0; virtual void f3() = 0;
	virtual void f4() = 0; virtual void f5() = 0; virtual void f6() = 0;
	virtual void f7() = 0;
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(bool executed) = 0;
	virtual void upgradeImplementation() = 0;
	int state;
};

struct UpgradeTail { virtual void iface() {} };

class UpgradeModule : public BehaviorModule, public BehaviorModuleInterface, public UpgradeMux, public UpgradeTail
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);
	void rva004CE4A0();
	void rva004CE4A8();
protected:
	virtual ~UpgradeModule(); // retail ??1UpgradeModule@@MAE@XZ, 0x0046089D
};

class RemoveUpgradeUpgrade : public UpgradeModule
{
public:
	RemoveUpgradeUpgrade(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual ~RemoveUpgradeUpgrade();
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
};

#endif
