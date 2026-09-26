// cl: /O1 /MD
// ??_GToppleUpdateModuleData@@UAEPAXI@Z @0x004A838B 28B
// Deleting dtor slot 0 of vtable 0x008538A0; calls rowed ??1 at 0x004A83A7 then rowed operator delete at 0x0002FD60.
class ToppleUpdateModuleData { public: __declspec(noinline) virtual ~ToppleUpdateModuleData(); private: int m_famgen; };
ToppleUpdateModuleData::~ToppleUpdateModuleData() { m_famgen = 0; }
void famgenDelete(ToppleUpdateModuleData *p) { delete p; }
