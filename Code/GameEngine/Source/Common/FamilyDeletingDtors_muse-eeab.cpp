// cl: /O1 /MD
// ??_GCivilianSpawnUpdateModuleData@@UAEPAXI@Z @0x0047FAA3
class CivilianSpawnUpdateModuleData { public: __declspec(noinline) virtual ~CivilianSpawnUpdateModuleData(); private: int m_famgen; };
CivilianSpawnUpdateModuleData::~CivilianSpawnUpdateModuleData() { m_famgen = 0; }
void famgenDelete(CivilianSpawnUpdateModuleData *p) { delete p; }
// ??_GStrafeAreaUpdateModuleData@@UAEPAXI@Z @0x003A4F05
class StrafeAreaUpdateModuleData { public: __declspec(noinline) virtual ~StrafeAreaUpdateModuleData(); private: int m_famgen; };
StrafeAreaUpdateModuleData::~StrafeAreaUpdateModuleData() { m_famgen = 0; }
void famgenDelete(StrafeAreaUpdateModuleData *p) { delete p; }
