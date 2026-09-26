// cl: /O1 /MD
// ??_GTransitionDamageFX@@MAEPAXI@Z @0x004BA7C4 28B
// Deleting dtor slot 0 of vtable 0x00859AEC (class of ctor at 0x4BA3EA); calls
// rowed ??1TransitionDamageFX@@MAE@XZ at 0x004BA47C then rowed operator delete
// at 0x0002FD60. Protected to match the rowed ??1 (memory pool macro).
class TransitionDamageFX { protected: __declspec(noinline) virtual ~TransitionDamageFX(); private: int m_famgen;
  friend void famgenDelete(TransitionDamageFX *p); };
// ??1TransitionDamageFX@@MAE@XZ present-unmatched
TransitionDamageFX::~TransitionDamageFX() { m_famgen = 0; }
void famgenDelete(TransitionDamageFX *p) { delete p; }
