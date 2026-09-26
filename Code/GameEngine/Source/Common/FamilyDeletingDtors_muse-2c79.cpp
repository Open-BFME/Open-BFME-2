// cl: /O1 /MD
// ??_GAnimateWindowManager@@UAEPAXI@Z @0x0053B827 28B
// Deleting dtor slot 0 of vtable 0x008692B0; calls rowed ??1 at 0x0053B6E0 then rowed operator delete at 0x0002FD60.
class AnimateWindowManager { public: __declspec(noinline) virtual ~AnimateWindowManager(); private: int m_famgen; };
// ??1AnimateWindowManager@@UAE@XZ present-unmatched
AnimateWindowManager::~AnimateWindowManager() { m_famgen = 0; }
void famgenDeleteAnimateWindowManager(AnimateWindowManager *p) { delete p; }
