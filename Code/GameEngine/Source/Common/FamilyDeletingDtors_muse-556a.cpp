// cl: /O1 /MD
// ??_GDoCommandUpgrade@@MAEPAXI@Z @0x004B4C5F, 28B.
// Scalar deleting dtor slot 0 of vtable 0x00857B58; calls rowed ??1 at
// 0x004B4BA1 plus rowed delete at 0x0002FD60.

class DoCommandUpgrade { protected: __declspec(noinline) virtual ~DoCommandUpgrade(); private: int m_famgen;
  friend void famgenDelete(DoCommandUpgrade *p); };
DoCommandUpgrade::~DoCommandUpgrade() { m_famgen = 0; }
void famgenDelete(DoCommandUpgrade *p) { delete p; }
