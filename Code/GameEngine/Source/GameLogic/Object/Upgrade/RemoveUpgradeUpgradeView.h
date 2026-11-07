// RemoveUpgradeUpgradeView.h: the one view of RemoveUpgradeUpgrade over the
// canonical UpgradeModule.h, and of its ModuleData, shared by
// RemoveUpgradeUpgrade.cpp and the donors that merge into it.
// Target facts (code RVAs, table VAs): ctor 0x004B7FA4 and dtor 0x004B7F01
// store 0x00C58E20 at +0, UpgradeModule's 0x00C57328 at +0x0C, 0x00C58DD8 at
// +0x10 and UpgradeModule's 0x00C58790 at +0x18 (size 0x1C).
//  - 0x00C58E20 (12 slots): ??_G 0x004B7FD5, loadPostProcess 0x00497805
//    (`jmp 0x0058B03E`, UpgradeModule's own body), the name getter 0x004B7F21
//    (rowed as the non-virtual ?name@RemoveUpgradeUpgrade, so slot 2 stays
//    UpgradeModule's here), xfer 0x004B8710 (Version1 then UpgradeModule::xfer,
//    the body retail folds with ArmorUpgrade::xfer), getModuleNameKey
//    0x004B7F3D, then UpgradeModule's slots.
//  - 0x00C58DD8 (UpgradeMux, 18 slots): UpgradeModule's except slot 8,
//    upgradeRemovalImplementation 0x004B7F27, and slot 10,
//    upgradeImplementation 0x004B8095 (RemoveUpgradeUpgradeImplementation.cpp).
#ifndef REMOVEUPGRADEUPGRADEVIEW_H
#define REMOVEUPGRADEUPGRADEVIEW_H

#include <vector>
#define BFME_SNAPSHOT_NAME_SLOT
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

#include "../../../../Include/GameLogic/Module/UpgradeModule.h"

class RemoveUpgradeUpgrade : public UpgradeModule
{
public:
	RemoveUpgradeUpgrade(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual ~RemoveUpgradeUpgrade();
	virtual void xfer(Xfer *xfer);											// primary slot 3
	virtual void upgradeRemovalImplementation();							// UpgradeMux slot 8
	virtual void upgradeImplementation();									// UpgradeMux slot 10
};

#endif
