// cl: /O1 /MD
// ??_GToppleUpdateModuleData@@UAEPAXI@Z @0x004A838B 28B
// Deleting dtor slot 0 of vtable 0x008538A0; calls rowed ??1 at 0x004A83A7 then rowed operator delete at 0x0002FD60.
class ToppleUpdateModuleData { public: __declspec(noinline) virtual ~ToppleUpdateModuleData(); private: int m_famgen; };
ToppleUpdateModuleData::~ToppleUpdateModuleData() { m_famgen = 0; }
void famgenDelete(ToppleUpdateModuleData *p) { delete p; }

// ??_GDelayedLuaEventUpdate@@UAEPAXI@Z @0x004A8EEF 28B
// Deleting dtor slot 0 of vtable 0x00853A5C; calls rowed ??1 at 0x004A8D4A then rowed operator delete at 0x0002FD60.
class DelayedLuaEventUpdate { public: __declspec(noinline) virtual ~DelayedLuaEventUpdate(); private: int m_famgen; };
DelayedLuaEventUpdate::~DelayedLuaEventUpdate() { m_famgen = 0; }
void famgenDelete(DelayedLuaEventUpdate *p) { delete p; }
