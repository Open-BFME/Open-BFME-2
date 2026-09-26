// cl: /O1 /MD
// ??_GTeleportSpecialAbilityUpdateModuleData@@UAEPAXI@Z @0x00492EFD
// Deleting dtor slot 0 of vtable 0xC4E208; calls the rowed ??1 at 0x492F19.
class TeleportSpecialAbilityUpdateModuleData { public: __declspec(noinline) virtual ~TeleportSpecialAbilityUpdateModuleData(); private: int m_famgen; };
TeleportSpecialAbilityUpdateModuleData::~TeleportSpecialAbilityUpdateModuleData() { m_famgen = 0; }
void famgenDelete(TeleportSpecialAbilityUpdateModuleData *p) { delete p; }
