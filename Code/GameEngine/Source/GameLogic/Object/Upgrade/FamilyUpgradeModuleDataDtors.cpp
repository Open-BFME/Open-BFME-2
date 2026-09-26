// cl: /DNDEBUG /MD /EHsc /O1
// Module-data destructors named from ModuleFactory registrations (name ->
// newModuleData -> ctor -> vtable -> deleting dtor -> dtor). Each is the
// same-shape sibling of UpgradeModuleData's destructor (0x255A42): the
// AsciiString member (offset read per class) is released, then the base vtable restored.
// Class names follow Zero Hour's <Module>ModuleData convention.

class AsciiStringMember { public: ~AsciiStringMember(); char m_data[4]; };
class ModuleDataBase { public: virtual ~ModuleDataBase() {} };

class W3DBoatWakeModelDrawModuleData : public ModuleDataBase { public: char m_pad[0x8 - 4]; AsciiStringMember m_name; };
void *famgenMakeW3DBoatWakeModelDrawModuleData() { return new W3DBoatWakeModelDrawModuleData; }

class UpgradeDieModuleData : public ModuleDataBase { public: char m_pad[0x38 - 4]; AsciiStringMember m_name; };
void *famgenMakeUpgradeDieModuleData() { return new UpgradeDieModuleData; }

class BroadcastStealthUpdateModuleData : public ModuleDataBase { public: char m_pad[0x2C - 4]; AsciiStringMember m_name; };
void *famgenMakeBroadcastStealthUpdateModuleData() { return new BroadcastStealthUpdateModuleData; }

class FadeAndDieOrnamentUpdateModuleData : public ModuleDataBase { public: char m_pad[0x8 - 4]; AsciiStringMember m_name; };
void *famgenMakeFadeAndDieOrnamentUpdateModuleData() { return new FadeAndDieOrnamentUpdateModuleData; }

// ??1DoCommandUpgradeModuleData@@UAE@XZ, retail 0x00256222, 69 bytes.
// Two AsciiString members at +0x118/+0x11C (own table 0x00857BC4 holding
// GetUpgradeCommandButtonName plus RemoveUpgradeCommandButtonName; ctor
// 0x255795 and0 factory 0x2557B5 news 0x120; vtable 0x00BF3840; caller
// ??_G 0x256283 slot 0). Same-shape sibling of UpgradeModuleData dtor
// 0x255A42 with two releases then base vtable 0x00BBB554 restored.
class DoCommandUpgradeModuleData : public ModuleDataBase { public: char m_pad[0x118 - 4]; AsciiStringMember m_getUpgradeCommandButtonName; AsciiStringMember m_removeUpgradeCommandButtonName; };
void *famgenMakeDoCommandUpgradeModuleData() { return new DoCommandUpgradeModuleData; }

// ??1SpawnUnitBehaviorModuleData@@UAE@XZ, retail 0x002562BB, 63 bytes.
// Two AsciiString members at +0x8/+0xC (UnitName plus UnitCommand per own
// table 0x00C59238 and ctor 0x25598C; factory 0x2559F1 news 0x20; vtable
// 0x00BF36C0; caller ??_G 0x25629F slot 0). Same-shape sibling of
// DoCommandUpgradeModuleData dtor 0x256222 with two releases then base
// vtable 0x00BBB554 restored.
class SpawnUnitBehaviorModuleData : public ModuleDataBase { public: char m_pad[0x8 - 4]; AsciiStringMember m_unitName; AsciiStringMember m_unitCommand; };
void *famgenMakeSpawnUnitBehaviorModuleData() { return new SpawnUnitBehaviorModuleData; }

