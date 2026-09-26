// cl: /O1 /MD
// ??_GW3DStreakDrawModuleData@@UAEPAXI@Z @0x000D0673
class W3DStreakDrawModuleData { public: __declspec(noinline) virtual ~W3DStreakDrawModuleData(); private: int m_famgen; };
W3DStreakDrawModuleData::~W3DStreakDrawModuleData() { m_famgen = 0; }
void famgenDelete(W3DStreakDrawModuleData *p) { delete p; }

// ??_GDelayedWeaponSetUpgradeUpdate@@MAEPAXI@Z @0x0048831C
class DelayedWeaponSetUpgradeUpdate { protected: __declspec(noinline) virtual ~DelayedWeaponSetUpgradeUpdate(); private: int m_famgen;
  friend void famgenDelete(DelayedWeaponSetUpgradeUpdate *p); };
DelayedWeaponSetUpgradeUpdate::~DelayedWeaponSetUpgradeUpdate() { m_famgen = 0; }
void famgenDelete(DelayedWeaponSetUpgradeUpdate *p) { delete p; }
