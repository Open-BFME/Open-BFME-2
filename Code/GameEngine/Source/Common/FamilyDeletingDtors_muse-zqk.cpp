// cl: /MD
// ??_GCivilianSpawnCollideModuleData@@UAEPAXI@Z @0x004BD70E
class CivilianSpawnCollideModuleData { public: __declspec(noinline) virtual ~CivilianSpawnCollideModuleData(); private: int m_famgen; };
CivilianSpawnCollideModuleData::~CivilianSpawnCollideModuleData() { m_famgen = 0; }
void famgenDelete(CivilianSpawnCollideModuleData *p) { delete p; }
// ??_GRankInfo@@UAEPAXI@Z @0x0020021A
class RankInfo { public: __declspec(noinline) virtual ~RankInfo(); private: int m_famgen; };
RankInfo::~RankInfo() { m_famgen = 0; }
void famgenDelete(RankInfo *p) { delete p; }
// ??_GSpecialDisguiseUpdateModuleData@@UAEPAXI@Z @0x004B044C
class SpecialDisguiseUpdateModuleData { public: __declspec(noinline) virtual ~SpecialDisguiseUpdateModuleData(); private: int m_famgen; };
SpecialDisguiseUpdateModuleData::~SpecialDisguiseUpdateModuleData() { m_famgen = 0; }
void famgenDelete(SpecialDisguiseUpdateModuleData *p) { delete p; }
