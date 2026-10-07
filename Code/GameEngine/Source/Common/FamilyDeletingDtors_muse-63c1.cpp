// cl: /MD
// ??_GSpellRechargeModifierUpgradeModuleData@@UAEPAXI@Z @0x004B606E 28B
// Deleting dtor slot 0 of vtable 0x008583E0; calls rowed ??1SpellRechargeModifierUpgradeModuleData@@UAE@XZ at 0x004B608A then rowed operator delete at 0x0002FD60.
class SpellRechargeModifierUpgradeModuleData { public: __declspec(noinline) virtual ~SpellRechargeModifierUpgradeModuleData(); private: int m_famgen; };
SpellRechargeModifierUpgradeModuleData::~SpellRechargeModifierUpgradeModuleData() { m_famgen = 0; }
void famgenDelete(SpellRechargeModifierUpgradeModuleData *p) { delete p; }
// ??_GGeometryUpgradeModuleData@@UAEPAXI@Z @0x004B6F65 28B
// Deleting dtor slot 0 of vtable 0x008589F0; calls rowed ??1GeometryUpgradeModuleData@@UAE@XZ at 0x004B6F81 then rowed operator delete at 0x0002FD60.
class GeometryUpgradeModuleData { public: __declspec(noinline) virtual ~GeometryUpgradeModuleData(); private: int m_famgen; };
GeometryUpgradeModuleData::~GeometryUpgradeModuleData() { m_famgen = 0; }
void famgenDelete(GeometryUpgradeModuleData *p) { delete p; }
