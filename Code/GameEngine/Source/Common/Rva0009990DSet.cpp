// cl: /O1 /MD
// ?set@Rva0009990D@@QAEXPAX@Z retail 0x000998EA 35B guarded pointer swap with
// LockClass dtor plus delete. Evidence: named pin plus rowed dtor 0x00613AC0
// plus delete 0x0002FD60; callers at 0x002256FD 0x0038B200.
void __cdecl operator delete(void *p);
struct MutexClass { struct LockClass { ~LockClass(); }; };
class Rva0009990D
{
public:
	void set(void *p);
	void clear();
private:
	MutexClass::LockClass *m_ptr;
};
void Rva0009990D::set(void *p)
{
	MutexClass::LockClass *old = m_ptr;
	if (p == old)
		return;
	m_ptr = (MutexClass::LockClass *)p;
	if (old == 0)
		return;
	old->~LockClass();
	::operator delete(old);
}
// ?clear@Rva0009990D@@QAEXXZ retail 0x0009990D 26B clear pointer with dtor plus
// delete. Evidence: named pin plus same callees as set; 23 callers.
void Rva0009990D::clear()
{
	MutexClass::LockClass *old = m_ptr;
	m_ptr = 0;
	if (old == 0)
		return;
	old->~LockClass();
	::operator delete(old);
}

class ThreadClass { public: void Stop(); };
// Native scalar-deleting destructor ABI: slot0 takes flags and returns
// the allocation pointer. Keep the original payload type unresolved.
class Rva00550B4CThreadVtable { public: virtual void *destroy(int flags); };
class Rva00550B4C
{
public:
    void rva00550B4C();
private:
    char unknown00[0x64];
    ThreadClass *thread;
    char unknown68[8];
    Rva0009990D lockOwner;
};
// Native550B4C..550B83. Same lock-release/stop/nondeleting-destroy/free
// order as the matched PeerThread endThread; target offsets64/70 and its
// direct Stop/clear calls independently establish this partial view.
void Rva00550B4C::rva00550B4C()
{
    if (thread) {
        lockOwner.clear();
        thread->Stop();
        void *allocation=thread ? ((Rva00550B4CThreadVtable *)thread)->destroy(0) : 0;
        ::operator delete(allocation);
    }
    thread=0;
}
