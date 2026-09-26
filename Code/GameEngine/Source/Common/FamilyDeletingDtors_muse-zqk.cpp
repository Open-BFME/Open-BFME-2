// cl: /O1 /MD
// ??_GCivilianSpawnCollideModuleData@@UAEPAXI@Z @0x004BD70E
class CivilianSpawnCollideModuleData { public: __declspec(noinline) virtual ~CivilianSpawnCollideModuleData(); private: int m_famgen; };
CivilianSpawnCollideModuleData::~CivilianSpawnCollideModuleData() { m_famgen = 0; }
void famgenDelete(CivilianSpawnCollideModuleData *p) { delete p; }
// ??_GHeroModeSpecialAbilityUpdateModuleData@@UAEPAXI@Z @0x004922D5
class HeroModeSpecialAbilityUpdateModuleData { public: __declspec(noinline) virtual ~HeroModeSpecialAbilityUpdateModuleData(); private: int m_famgen; };
HeroModeSpecialAbilityUpdateModuleData::~HeroModeSpecialAbilityUpdateModuleData() { m_famgen = 0; }
void famgenDelete(HeroModeSpecialAbilityUpdateModuleData *p) { delete p; }
// ??_GRankInfo@@UAEPAXI@Z @0x0020021A
class RankInfo { public: __declspec(noinline) virtual ~RankInfo(); private: int m_famgen; };
RankInfo::~RankInfo() { m_famgen = 0; }
void famgenDelete(RankInfo *p) { delete p; }
// ??_GBaikonurLaunchPower@@UAEPAXI@Z @0x004CAFC1
class BaikonurLaunchPower { public: __declspec(noinline) virtual ~BaikonurLaunchPower(); private: int m_famgen; };
BaikonurLaunchPower::~BaikonurLaunchPower() { m_famgen = 0; }
void famgenDelete(BaikonurLaunchPower *p) { delete p; }
