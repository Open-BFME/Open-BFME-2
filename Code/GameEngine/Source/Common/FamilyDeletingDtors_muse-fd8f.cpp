// cl: /MD
// ??_GDefectorSpecialPowerModuleData@@UAEPAXI@Z @0x004C2A84 28B
// Deleting dtor slot 0 of vtable 0x0085E7A8; calls rowed ??1DefectorSpecialPowerModuleData@@UAE@XZ at 0x004C8AB0 then rowed operator delete at 0x0002FD60.
class DefectorSpecialPowerModuleData { public: __declspec(noinline) virtual ~DefectorSpecialPowerModuleData(); private: int m_famgen; };
DefectorSpecialPowerModuleData::~DefectorSpecialPowerModuleData() { m_famgen = 0; }
void famgenDelete(DefectorSpecialPowerModuleData *p) { delete p; }
