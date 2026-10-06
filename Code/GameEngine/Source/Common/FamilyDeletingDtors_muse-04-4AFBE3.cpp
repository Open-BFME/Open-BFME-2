// cl: /MD
// ??_GRespawnUpdateModuleData@@UAEPAXI@Z @0x004AFBE3, 28B.
// Scalar deleting dtor slot 0 of vtable 0x008556F8; calls rowed ??1 at
// 0x004AFBFF plus rowed delete at 0x0002FD60.

// ??_GRespawnUpdateModuleData@@UAEPAXI@Z @0x004AFBE3 present-unmatched
class RespawnUpdateModuleData { public: __declspec(noinline) virtual ~RespawnUpdateModuleData(); private: int m_famgen;
  friend void famgenDelete(RespawnUpdateModuleData *p); };
RespawnUpdateModuleData::~RespawnUpdateModuleData() { m_famgen = 0; }
void famgenDelete(RespawnUpdateModuleData *p) { delete p; }
