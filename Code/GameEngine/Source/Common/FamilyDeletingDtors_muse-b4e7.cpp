// cl: /O1 /MD
// ??_GStealthUpgrade@@MAEPAXI@Z @0x004B53A9 28B slot 0 of 0x00857E30.
// Calls rowed ??1StealthUpgrade@@MAE@XZ at 0x004B530D then operator delete.
class StealthUpgrade { protected: __declspec(noinline) virtual ~StealthUpgrade(); private: int m_famgen;
  friend void famgenDelete(StealthUpgrade *p); };
StealthUpgrade::~StealthUpgrade() { m_famgen = 0; }
void famgenDelete(StealthUpgrade *p) { delete p; }
