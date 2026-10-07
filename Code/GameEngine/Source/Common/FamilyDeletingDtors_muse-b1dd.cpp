// cl: /MD
// ??_GReplaceSelfUpgrade@@MAEPAXI@Z @0x004B70CF 28B
// Deleting dtor slot 0 of vtable 0x00858B10; calls rowed ??1ReplaceSelfUpgrade@@MAE@XZ at 0x004B70EB then rowed operator delete at 0x0002FD60.
class ReplaceSelfUpgrade { protected: __declspec(noinline) virtual ~ReplaceSelfUpgrade(); private: int m_famgen;
  friend void famgenDelete(ReplaceSelfUpgrade *p); };
ReplaceSelfUpgrade::~ReplaceSelfUpgrade() { m_famgen = 0; }
void famgenDelete(ReplaceSelfUpgrade *p) { delete p; }

