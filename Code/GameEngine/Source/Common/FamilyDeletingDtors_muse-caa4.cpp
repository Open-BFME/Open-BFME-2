// cl: /O1 /MD
// ??_GToggleDeploySpecialAbilityUpdateModuleData@@UAEPAXI@Z @0x004AE669 28B
// Deleting dtor slot 0 of vtable 0x008553D8; calls rowed ??1ToggleDeploySpecialAbilityUpdateModuleData@@UAE@XZ at 0x004AE685 then rowed operator delete at 0x0002FD60.
class ToggleDeploySpecialAbilityUpdateModuleData { public: __declspec(noinline) virtual ~ToggleDeploySpecialAbilityUpdateModuleData(); private: int m_famgen; };
ToggleDeploySpecialAbilityUpdateModuleData::~ToggleDeploySpecialAbilityUpdateModuleData() { m_famgen = 0; }
void famgenDelete(ToggleDeploySpecialAbilityUpdateModuleData *p) { delete p; }
