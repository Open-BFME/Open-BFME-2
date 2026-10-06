// cl: /MD
// ??_GHordeMeleeFormation@@UAEPAXI@Z, retail 0x00586E35 28B.
// Deleting dtor for HordeMeleeFormation whose ??1 is rowed at 0x00586E51; placeholder ~ is duplicate.
class HordeMeleeFormation { public: __declspec(noinline) virtual ~HordeMeleeFormation(); private: int m_famgen; friend void famgenDelete(HordeMeleeFormation *p); };
HordeMeleeFormation::~HordeMeleeFormation() { m_famgen = 0; }
void famgenDelete(HordeMeleeFormation *p) { delete p; }
