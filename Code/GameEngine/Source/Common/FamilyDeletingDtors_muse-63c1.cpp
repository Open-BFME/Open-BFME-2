// cl: /O1 /MD
// ??_GGeometryUpgrade@@UAEPAXI@Z @0x004B6C39 28B
// Deleting dtor slot 0 of vtable 0x008589C0; calls rowed ??1GeometryUpgrade@@UAE@XZ at 0x004B6C55 then rowed operator delete at 0x0002FD60.
class GeometryUpgrade { public: __declspec(noinline) virtual ~GeometryUpgrade(); private: int m_famgen; };
GeometryUpgrade::~GeometryUpgrade() { m_famgen = 0; }
void famgenDelete(GeometryUpgrade *p) { delete p; }
// ??_GSpellRechargeModifierUpgradeModuleData@@UAEPAXI@Z @0x004B606E 28B
// Deleting dtor slot 0 of vtable 0x008583E0; calls rowed ??1SpellRechargeModifierUpgradeModuleData@@UAE@XZ at 0x004B608A then rowed operator delete at 0x0002FD60.
class SpellRechargeModifierUpgradeModuleData { public: __declspec(noinline) virtual ~SpellRechargeModifierUpgradeModuleData(); private: int m_famgen; };
SpellRechargeModifierUpgradeModuleData::~SpellRechargeModifierUpgradeModuleData() { m_famgen = 0; }
void famgenDelete(SpellRechargeModifierUpgradeModuleData *p) { delete p; }
