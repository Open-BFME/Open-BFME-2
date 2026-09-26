// cl: /O2 /MD
// ??_GCftp@@UAEPAXI@Z @0x006CB5B0 30B
// Deleting dtor slot 0 of vtable 0x008E8A38; calls pinned ??1Cftp@@UAE@XZ at 0x006CA600 then rowed operator delete at 0x0002FD60; ctor rowed at 0x006CA5E0 installs same vtable; BFME1 donor CftpDeletingDestructor.cpp virtual ~Cftp.
class Cftp { public: __declspec(noinline) virtual ~Cftp(); private: int m_famgen; };
// ??1Cftp@@UAE@XZ present-unmatched
Cftp::~Cftp() { m_famgen = 0; }
void famgenDelete(Cftp *p) { delete p; }
