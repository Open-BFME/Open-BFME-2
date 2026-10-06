// cl: /O1 /arch:SSE /G7 /MD
// ??0Rva00419CFB@@QAE@PAX@Z at 0x00419CFB (29 bytes). The caller allocates
// 0x54 bytes and passes its LockClass address; retail calls the ThreadClass
// null-name constructor, stores that pointer at +0x50, and installs vtable
// 0x0083AD60. The class identity is unknown; its base and layout follow the
// target constructor and caller rather than donor naming.
extern const void *const g_00C3AD60[];

class __declspec(novtable) ThreadClass
{
public:
    ThreadClass(const char *name);
    virtual ~ThreadClass();
    virtual void Execute();
    void Set_Priority(int priority);
    __declspec(noinline) bool Is_Running();
    __declspec(noinline) void Stop();

protected:
    virtual void Thread_Function() = 0;

private:
    char m_name[0x40];
    unsigned int m_threadId;
    void *m_handle;
    int m_priority;
};

class __declspec(novtable) Rva00419CFB : public ThreadClass
{
public:
    Rva00419CFB(void *lock);

private:
    void *m_lock;
};

Rva00419CFB::Rva00419CFB(void *lock) : ThreadClass(0)
{
    m_lock = lock;
    *(const void **)this = g_00C3AD60;
}
