// cl: /O1 /MD
// ??_GHordeMeleeSwarm@@UAEPAXI@Z retail 0x005844E6 28B.
// Deleting dtor slot0 of vtable 0x0086FC80 for HordeMeleeSwarm whose ??1 is at
// 0x00584502 rowed as dup alias; placeholder ~ is duplicate.
class HordeMeleeSwarm { public: __declspec(noinline) virtual ~HordeMeleeSwarm(); private: int m_famgen; friend void famgenDelete(HordeMeleeSwarm *p); };
// ??1HordeMeleeSwarm@@UAE@XZ present-unmatched
HordeMeleeSwarm::~HordeMeleeSwarm() { m_famgen = 0; }
void famgenDelete(HordeMeleeSwarm *p) { delete p; }
