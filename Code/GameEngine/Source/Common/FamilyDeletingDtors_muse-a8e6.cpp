// cl: /O1 /MD
// ??_GW3DStreakDrawModuleData@@UAEPAXI@Z @0x000D0673
class W3DStreakDrawModuleData { public: __declspec(noinline) virtual ~W3DStreakDrawModuleData(); private: int m_famgen; };
W3DStreakDrawModuleData::~W3DStreakDrawModuleData() { m_famgen = 0; }
void famgenDelete(W3DStreakDrawModuleData *p) { delete p; }
