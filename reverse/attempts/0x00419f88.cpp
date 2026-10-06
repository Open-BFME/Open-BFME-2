// ?rva00419F88@Rva00419F88@@UAEXXZ
// partial score=0.93 date=2026-10-06
// cl: /O1 /arch:SSE /G7 /MD
// ?rva00419F88@Rva00419F88@@UAE? at 0x00419F88 (135 bytes). The vtable
// packet places this body at slot 14; its caller and the adjacent stop method
// establish fields +0x74, +0x78, and +0x80. The class and slot names remain
// address-based. The body creates a LockClass, transfers it through the
// rowed Rva0009990D::set, starts the ThreadClass-derived worker, then invokes
// its first post-destructor virtual slot.
class ThreadClass
{
public:
    ThreadClass(const char *name);
    virtual ~ThreadClass();
    virtual void Execute();
    virtual void Thread_Function() = 0;

private:
    char m_name[0x40];
    unsigned int m_threadId;
    void *m_handle;
    int m_priority;
};

class MutexClass
{
public:
    class LockClass
    {
    public:
        LockClass(MutexClass &mutex, int timeout);
        ~LockClass();

    private:
        char m_storage[8];
    };

private:
    void *m_handle;
    unsigned int m_locked;
};

class Rva0009990D
{
public:
    void set(void *p);
};

class Rva00419CFB : public ThreadClass
{
public:
    Rva00419CFB(void *lock);
    virtual void Thread_Function();
};

class __declspec(novtable) Rva00419F88
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void rva00419F88();
    virtual void v15();

private:
    char m_pad00[0x70];
    ThreadClass *m_thread;
    MutexClass m_mutex;
    Rva0009990D m_ownedLock;
};

void Rva00419F88::rva00419F88()
{
    v15();
    MutexClass::LockClass *lock = new MutexClass::LockClass(m_mutex, -1);
    m_ownedLock.set(lock);
    Rva00419CFB *thread = new Rva00419CFB(lock);
    m_thread = thread;
    thread->Execute();
}
