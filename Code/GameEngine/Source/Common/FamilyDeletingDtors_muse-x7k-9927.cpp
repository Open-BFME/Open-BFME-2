// cl: /O1 /MD
// ??_GRespawnBodyModuleData@@UAEPAXI@Z @0x004C154D 28B
// Deleting dtor slot 0 of vtable 0x00C5BA00; calls rowed ??1 at 0x004C1569 then rowed operator delete at 0x0002FD60.
class RespawnBodyModuleData { public: __declspec(noinline) virtual ~RespawnBodyModuleData(); private: int m_famgen; };
// ??1RespawnBodyModuleData@@UAE@XZ present-unmatched
RespawnBodyModuleData::~RespawnBodyModuleData() { m_famgen = 0; }
void famgenDelete(RespawnBodyModuleData *p) { delete p; }
