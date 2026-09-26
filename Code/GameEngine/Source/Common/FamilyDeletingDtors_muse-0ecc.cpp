// cl: /O1 /MD
// ??_GAttributeModifierAuraUpdateModuleData@@UAEPAXI@Z @0x0049BF50, 28B.
// Scalar deleting dtor slot 0 of vtable 0x00850EE8; calls rowed ??1 at
// 0x0049BF6C plus rowed delete at 0x0002FD60.

// ??_GAttributeModifierAuraUpdateModuleData@@UAEPAXI@Z @0x0049BF50
class AttributeModifierAuraUpdateModuleData { public: __declspec(noinline) virtual ~AttributeModifierAuraUpdateModuleData(); private: int m_famgen;
  friend void famgenDelete(AttributeModifierAuraUpdateModuleData *p); };
AttributeModifierAuraUpdateModuleData::~AttributeModifierAuraUpdateModuleData() { m_famgen = 0; }
void famgenDelete(AttributeModifierAuraUpdateModuleData *p) { delete p; }

// ??_GBuildingBehaviorModuleData@@UAEPAXI@Z @0x004564CA, 28B.
// Scalar deleting dtor slot 0 of vtable 0x00840798; calls rowed ??1 at
// 0x004564E6 plus rowed delete at 0x0002FD60.

// ??_GBuildingBehaviorModuleData@@UAEPAXI@Z @0x004564CA
class BuildingBehaviorModuleData { public: __declspec(noinline) virtual ~BuildingBehaviorModuleData(); private: int m_famgen;
  friend void famgenDelete(BuildingBehaviorModuleData *p); };
BuildingBehaviorModuleData::~BuildingBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(BuildingBehaviorModuleData *p) { delete p; }
