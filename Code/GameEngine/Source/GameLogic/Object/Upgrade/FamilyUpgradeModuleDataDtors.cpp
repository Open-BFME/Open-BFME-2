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

