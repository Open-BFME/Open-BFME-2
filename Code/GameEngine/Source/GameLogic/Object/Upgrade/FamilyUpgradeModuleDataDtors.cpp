// cl: /DNDEBUG /MD /EHsc
// Module-data destructors named from ModuleFactory registrations (name ->
// newModuleData -> ctor -> vtable -> deleting dtor -> dtor). Each is the
// same-shape sibling of UpgradeModuleData's destructor (0x255A42): the
// AsciiString member (offset read per class) is released, then the base vtable restored.
// Class names follow Zero Hour's <Module>ModuleData convention.
// The anchors construct through a tagged constructor so the TU emits each
// vtable and deleting destructor without the implicit default constructors:
// those are rowed in their own units, and this TU's copies came first in
// link order and are not retail's.
struct FamVtableEmissionTag;

class AsciiStringMember { public: ~AsciiStringMember(); char m_data[4]; };
class ModuleDataBase { public: virtual ~ModuleDataBase() {} };
#include "../../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
struct SoundHolder { ~SoundHolder() { if (m_ptr) m_ptr->Release_Ref(); } OpaqueRefCounted *m_ptr; };

class W3DBoatWakeModelDrawModuleData : public ModuleDataBase { public: W3DBoatWakeModelDrawModuleData(FamVtableEmissionTag *) {} char m_pad[0x8 - 4]; AsciiStringMember m_name; };
void *famgenMakeW3DBoatWakeModelDrawModuleData() { return new W3DBoatWakeModelDrawModuleData((FamVtableEmissionTag *)0); }

// UpgradeDieModuleData derives from the canonical DestroyDieModuleData, as its constructor
// unit (UpgradeDieModuleDataCtor.cpp) declares it, so this unit's copy of the 31-slot vftable
// (retail 0x00BF33C0) is the same table. Retail's destructor inlines the empty base
// destructors down to Snapshot's vptr restore, so this unit defines them inline.
#include "../../../../Include/GameLogic/Module/DestroyDieModuleData.h"
inline ModuleData::~ModuleData() {}
inline DestroyDieModuleData::~DestroyDieModuleData() {}
class UpgradeDieModuleData : public DestroyDieModuleData { public: UpgradeDieModuleData(FamVtableEmissionTag *) {} AsciiStringMember m_name; };
void *famgenMakeUpgradeDieModuleData() { return new UpgradeDieModuleData((FamVtableEmissionTag *)0); }

class BroadcastStealthUpdateModuleData : public ModuleDataBase { public: BroadcastStealthUpdateModuleData(FamVtableEmissionTag *) {} char m_pad[0x2C - 4]; AsciiStringMember m_name; };
void *famgenMakeBroadcastStealthUpdateModuleData() { return new BroadcastStealthUpdateModuleData((FamVtableEmissionTag *)0); }

class FadeAndDieOrnamentUpdateModuleData : public ModuleDataBase { public: FadeAndDieOrnamentUpdateModuleData(FamVtableEmissionTag *) {} char m_pad[0x8 - 4]; AsciiStringMember m_name; };
void *famgenMakeFadeAndDieOrnamentUpdateModuleData() { return new FadeAndDieOrnamentUpdateModuleData((FamVtableEmissionTag *)0); }

// ??1DoCommandUpgradeModuleData@@UAE@XZ, retail 0x00256222, 69 bytes.
// Two AsciiString members at +0x118/+0x11C (own table 0x00857BC4 holding
// GetUpgradeCommandButtonName plus RemoveUpgradeCommandButtonName; ctor
// 0x255795 and0 factory 0x2557B5 news 0x120; vtable 0x00BF3840; caller
// ??_G 0x256283 slot 0). Same-shape sibling of UpgradeModuleData dtor
// 0x255A42 with two releases then base vtable 0x00BBB554 restored.
class DoCommandUpgradeModuleData : public ModuleDataBase { public: DoCommandUpgradeModuleData(FamVtableEmissionTag *) {} char m_pad[0x118 - 4]; AsciiStringMember m_getUpgradeCommandButtonName; AsciiStringMember m_removeUpgradeCommandButtonName; };
void *famgenMakeDoCommandUpgradeModuleData() { return new DoCommandUpgradeModuleData((FamVtableEmissionTag *)0); }

// ??1SpawnUnitBehaviorModuleData@@UAE@XZ, retail 0x002562BB, 63 bytes.
// Two AsciiString members at +0x8/+0xC (UnitName plus UnitCommand per own
// table 0x00C59238 and ctor 0x25598C; factory 0x2559F1 news 0x20; vtable
// 0x00BF36C0; caller ??_G 0x25629F slot 0). Same-shape sibling of
// DoCommandUpgradeModuleData dtor 0x256222 with two releases then base
// vtable 0x00BBB554 restored.
class SpawnUnitBehaviorModuleData : public ModuleDataBase { public: SpawnUnitBehaviorModuleData(FamVtableEmissionTag *) {} char m_pad[0x8 - 4]; AsciiStringMember m_unitName; AsciiStringMember m_unitCommand; };
void *famgenMakeSpawnUnitBehaviorModuleData() { return new SpawnUnitBehaviorModuleData((FamVtableEmissionTag *)0); }

// ??1CommandSetUpgradeModuleData@@UAE@XZ, retail 0x002561EF, 51 bytes.
// Single AsciiString at +0x118 (CommandSet per own table 0x008572C0 and ctor
// 0x255652; factory 0x255698 news 0x11C; vtable 0x00BF37C0; caller ??_G
// 0x256267 slot 0 shared with AttributeModifier/Castle ICF). Same-shape
// sibling of UpgradeModuleData dtor 0x255A42 with one release then base
// vtable 0x00BBB554 restored.
class CommandSetUpgradeModuleData : public ModuleDataBase { public: CommandSetUpgradeModuleData(FamVtableEmissionTag *) {} char m_pad[0x118 - 4]; AsciiStringMember m_commandSet; };
void *famgenMakeCommandSetUpgradeModuleData() { return new CommandSetUpgradeModuleData((FamVtableEmissionTag *)0); }

// ??1StealthDetectorUpdateModuleData@@UAE@XZ, retail 0x0025601C, 95 bytes.
// Two AsciiStrings at +0x6C/+0x2C plus two Release_Ref holders at +0x18/+0x14
// (factory 0x2553C5 news 0x70; vtable 0x00BF3540; caller ??_G 0x256000 slot 0).
// Same-shape sibling of AudioLoopUpgradeModuleData dtor 0x4B7C4C (holder plus
// BBB554 base) with two strings then two holders then base vtable restored.
class StealthDetectorUpdateModuleData : public ModuleDataBase { public: StealthDetectorUpdateModuleData(FamVtableEmissionTag *) {} char m_pad04[0x14 - 4]; SoundHolder m_holder14; SoundHolder m_holder18; char m_pad1C[0x2C - 0x1C]; AsciiStringMember m_str2C; char m_pad30[0x6C - 0x30]; AsciiStringMember m_str6C; };
void *famgenMakeStealthDetectorUpdateModuleData() { return new StealthDetectorUpdateModuleData((FamVtableEmissionTag *)0); }

