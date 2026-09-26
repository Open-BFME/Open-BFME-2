// cl: /O1 /MD
// ??_GWeaponFireSpecialAbilityUpdate@@UAEPAXI@Z @0x004927B4 28B
// Deleting dtor slot 0 of vtable 0x0084E090; calls rowed ??1 at 0x0049256B then rowed operator delete at 0x0002FD60.
class WeaponFireSpecialAbilityUpdate { public: __declspec(noinline) virtual ~WeaponFireSpecialAbilityUpdate(); private: int m_famgen; };
WeaponFireSpecialAbilityUpdate::~WeaponFireSpecialAbilityUpdate() { m_famgen = 0; }
void famgenDelete(WeaponFireSpecialAbilityUpdate *p) { delete p; }
