// cl: /O1 /MD
// ??_GDoCommandUpgradeModuleData@@UAEPAXI@Z @0x00256283 28B
// Deleting dtor slot 0 of vtable 0x007F3840; calls rowed ??1 at 0x00256222 then rowed operator delete at 0x0002FD60.
class DoCommandUpgradeModuleData { public: __declspec(noinline) virtual ~DoCommandUpgradeModuleData(); private: int m_famgen; };
// ??1DoCommandUpgradeModuleData@@UAE@XZ present-unmatched
DoCommandUpgradeModuleData::~DoCommandUpgradeModuleData() { m_famgen = 0; }
void famgenDeleteDoCommandUpgradeModuleData(DoCommandUpgradeModuleData *p) { delete p; }

// ??_GSpawnUnitBehaviorModuleData@@UAEPAXI@Z @0x0025629F 28B
// Deleting dtor slot 0 of vtable 0x007F36C0; calls rowed ??1 at 0x002562BB then rowed operator delete at 0x0002FD60.
// BFME1 donor: Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnUnitBehaviorModuleDataDestructor.cpp
class SpawnUnitBehaviorModuleData { public: __declspec(noinline) virtual ~SpawnUnitBehaviorModuleData(); private: int m_famgen; };
// ??1SpawnUnitBehaviorModuleData@@UAE@XZ present-unmatched
SpawnUnitBehaviorModuleData::~SpawnUnitBehaviorModuleData() { m_famgen = 0; }
void famgenDeleteSpawnUnitBehaviorModuleData(SpawnUnitBehaviorModuleData *p) { delete p; }

// ??_GCommandSetUpgradeModuleData@@UAEPAXI@Z @0x00256267 28B
// Deleting dtor slot 0 of vtable 0x007F37C0 (shared ICF with AttributeModifier 0x7F38C0 Castle 0x7F3940);
// calls rowed ??1 at 0x002561EF then rowed operator delete at 0x0002FD60.
class CommandSetUpgradeModuleData { public: __declspec(noinline) virtual ~CommandSetUpgradeModuleData(); private: int m_famgen; };
// ??1CommandSetUpgradeModuleData@@UAE@XZ present-unmatched
CommandSetUpgradeModuleData::~CommandSetUpgradeModuleData() { m_famgen = 0; }
void famgenDeleteCommandSetUpgradeModuleData(CommandSetUpgradeModuleData *p) { delete p; }

// ??_GStealthDetectorUpdateModuleData@@UAEPAXI@Z @0x00256000 28B
// Deleting dtor slot 0 of vtable 0x007F3540; calls rowed ??1 at 0x0025601C then rowed operator delete at 0x0002FD60.
class StealthDetectorUpdateModuleData { public: __declspec(noinline) virtual ~StealthDetectorUpdateModuleData(); private: int m_famgen; };
// ??1StealthDetectorUpdateModuleData@@UAE@XZ present-unmatched
StealthDetectorUpdateModuleData::~StealthDetectorUpdateModuleData() { m_famgen = 0; }
void famgenDeleteStealthDetectorUpdateModuleData(StealthDetectorUpdateModuleData *p) { delete p; }
