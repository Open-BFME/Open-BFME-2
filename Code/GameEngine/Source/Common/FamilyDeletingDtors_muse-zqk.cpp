// cl: /O1 /MD
// ??_GCivilianSpawnCollideModuleData@@UAEPAXI@Z @0x004BD70E
class CivilianSpawnCollideModuleData { public: __declspec(noinline) virtual ~CivilianSpawnCollideModuleData(); private: int m_famgen; };
CivilianSpawnCollideModuleData::~CivilianSpawnCollideModuleData() { m_famgen = 0; }
void famgenDelete(CivilianSpawnCollideModuleData *p) { delete p; }
