// cl: /O1 /MD
// ?set@Rva0009990D@@QAEXPAX@Z retail 0x000998EA 35B guarded pointer swap with
// LockClass dtor plus delete. Evidence: named pin plus rowed dtor 0x00613AC0
// plus delete 0x0002FD60; callers at 0x002256FD 0x0038B200.
#include <new>
struct MutexClass { struct LockClass { ~LockClass(); }; };
class Rva0009990D
{
public:
	void clear();
	~Rva0009990D(){clear();}
	void set(void *p);
	MutexClass::LockClass *m_ptr; // +0x00
};

class ThreadClass
{
public:
	ThreadClass(const char *name);
	void Stop();
	virtual ~ThreadClass();
	virtual void Execute();
protected:
	virtual void Thread_Function() = 0;
private:
	char m_name[0x40]; // +0x04
	unsigned int m_threadId; // +0x44
	void *m_handle; // +0x48
	int m_priority; // +0x4C
};
// Native scalar-deleting destructor ABI: slot0 takes flags and returns
// the allocation pointer. Keep the original payload type unresolved.
class Rva00550B4CThreadVtable { public: virtual void *destroy(int flags); };
class Rva00550B4C
{
public:
	void rva00550B4C();
	char m_pad00[0x64];
private:
	ThreadClass *thread; // +0x64
	char m_pad68[0x8];
	Rva0009990D lockOwner; // +0x70
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
