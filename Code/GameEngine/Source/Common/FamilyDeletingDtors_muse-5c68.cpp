// cl: /O1 /MD
// ??_GMonsterDockUpdateModuleData@@UAEPAXI@Z @0x004A1552 28B
// Deleting dtor slot 0 of vtable 0x00851DA8; calls rowed ??1 at 0x004A156E then rowed operator delete at 0x0002FD60.
class MonsterDockUpdateModuleData { public: __declspec(noinline) virtual ~MonsterDockUpdateModuleData(); private: int m_famgen; };
MonsterDockUpdateModuleData::~MonsterDockUpdateModuleData() { m_famgen = 0; }
void famgenDelete(MonsterDockUpdateModuleData *p) { delete p; }
