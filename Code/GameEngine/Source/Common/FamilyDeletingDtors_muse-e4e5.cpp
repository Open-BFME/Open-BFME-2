// cl: /O1 /MD
// ??_GW3DPropDrawModuleData@@UAEPAXI@Z @0x000CF058 28B
// Deleting dtor slot 0 of vtable 0x00BCD420; calls rowed ??1W3DPropDrawModuleData@@UAE@XZ at 0x000CEF3C then rowed operator delete at 0x0002FD60.
class W3DPropDrawModuleData { public: __declspec(noinline) virtual ~W3DPropDrawModuleData(); private: int m_famgen; };
W3DPropDrawModuleData::~W3DPropDrawModuleData() { m_famgen = 0; }
void famgenDelete(W3DPropDrawModuleData *p) { delete p; }
