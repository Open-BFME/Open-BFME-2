// cl: /MD
// ??_GTerrainResourceBehaviorModuleData@@UAEPAXI@Z @0x00482259
class TerrainResourceBehaviorModuleData { public: __declspec(noinline) virtual ~TerrainResourceBehaviorModuleData(); private: int m_famgen; };
TerrainResourceBehaviorModuleData::~TerrainResourceBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(TerrainResourceBehaviorModuleData *p) { delete p; }
