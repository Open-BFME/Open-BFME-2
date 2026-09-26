// cl: /O1 /MD
// ??_GMissileUpdateModuleData@@UAEPAXI@Z @0x004A784D 28B
// Deleting dtor slot 0 of vtable 0x00853668; calls rowed ??1 at 0x004A7869 then rowed operator delete at 0x0002FD60.
class MissileUpdateModuleData { public: __declspec(noinline) virtual ~MissileUpdateModuleData(); private: int m_famgen; };
// ??1MissileUpdateModuleData@@UAE@XZ present-unmatched
MissileUpdateModuleData::~MissileUpdateModuleData() { m_famgen = 0; }
void famgenDelete(MissileUpdateModuleData *p) { delete p; }
