// cl: /O1 /MD
// ?rva00514E20@AptMainMenu@@QAEXXZ @0x00514E20 75B.
// AptMainMenu's per-frame state machine 0x00515C64 enters it with the menu
// in ECX (mov ecx,esi; call) before the LAN / online restarts: a menu member
// that does not read its receiver.
// Restarts global thread object via wrapper. Evidence: chain lane packet.
#include <new>
#include <new>
class Rva0073F778 {
    char _pad[4];
    void *m_handle;
public:
    bool createThread(unsigned (__stdcall *start)(void *), void *arglist, int resume, unsigned stackSize, int priority, void *security);
    bool rva0073F83F(int resume, unsigned stackSize, int priority, void *security);
};
class AptMainMenu {
public:
    void rva00514E20();
};
class ThreadRestartObj {
public:
    virtual ~ThreadRestartObj();
    virtual void *unused0();
    virtual void *stop(int code);
private:
    void *m_handle;
    friend class AptMainMenu;
};
// ??1ThreadRestartObj@@UAE@XZ present-unmatched
inline ThreadRestartObj::~ThreadRestartObj() {}
// ?unused0@ThreadRestartObj@@UAEPAXXZ present-unmatched
inline void *ThreadRestartObj::unused0() { return 0; }
// ?stop@ThreadRestartObj@@UAEPAXH@Z present-unmatched
inline void *ThreadRestartObj::stop(int code) { return 0; }
extern ThreadRestartObj *g_bfmeThreadAtE048E0;
// g_bfmeThreadAtE048E0: matched references place it at VA 0xe048e0 (zero-filled .bss).
ThreadRestartObj * g_bfmeThreadAtE048E0;
void *Rva00514E20RestartHelper();
void AptMainMenu::rva00514E20()
{
    ThreadRestartObj *old = g_bfmeThreadAtE048E0;
    if (old) {
        void *p = old->stop(0);
        operator delete(p);
    }
    ThreadRestartObj *nw = (ThreadRestartObj *)operator new(8);
    if (nw) {
        nw->m_handle = 0;
        new (nw) ThreadRestartObj;
    } else {
        nw = 0;
    }
    g_bfmeThreadAtE048E0 = nw;
    if (nw) {
        ((Rva0073F778 *)nw)->rva0073F83F(1, 0, 4, 0);
    }
}
