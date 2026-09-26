// cl: /O1 /MD
// ??_GRadiateFearUpdateModuleData@@UAEPAXI@Z @0x0049C1D2 28B
// Deleting dtor slot 0 of vtable 0x00850FF0; calls rowed ??1 at 0x0049C1EE then rowed operator delete at 0x0002FD60.
class RadiateFearUpdateModuleData { public: __declspec(noinline) virtual ~RadiateFearUpdateModuleData(); private: int m_famgen; };
RadiateFearUpdateModuleData::~RadiateFearUpdateModuleData() { m_famgen = 0; }
void famgenDelete(RadiateFearUpdateModuleData *p) { delete p; }
