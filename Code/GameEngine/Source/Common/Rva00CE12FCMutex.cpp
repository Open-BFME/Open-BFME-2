// cl: /EHs-c- /Ob2
// BFME1 BfmeConv1033 semantic reference, reconciled with the BFME2 PE imports.
// Address-based class names preserve the proven identity without inventing an
// original application name. Base vtable VA CE1E14 has four pure virtual slots;
// derived vtable VA CE12FC supplies Sleep, GetTickCount, wait and release.
// The constructor creates a mutex at +4. Complete destruction closes that
// handle, then restores the base vtable through its genuine destructor65D180.
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);
extern "C" __declspec(dllimport) void *__stdcall CreateMutexA(void *, int, const char *);

class Rva00CE1E14Base {
public:
    Rva00CE1E14Base();
    virtual ~Rva00CE1E14Base();
    virtual void sleep(unsigned long) = 0;
    virtual unsigned long ticks() = 0;
    virtual void wait() = 0;
    virtual void release() = 0;
};
class Rva00CE12FCMutex : public Rva00CE1E14Base {
public:
    Rva00CE12FCMutex();
    virtual ~Rva00CE12FCMutex();
    virtual void sleep(unsigned long);
    virtual unsigned long ticks();
    virtual void wait();
    virtual void release();
private:
    void *m_handle;
};

Rva00CE12FCMutex::Rva00CE12FCMutex()
    : m_handle(CreateMutexA(0, 0, 0))
{
}

Rva00CE12FCMutex::~Rva00CE12FCMutex()
{
    if (m_handle != 0)
        CloseHandle(m_handle);
}

// Retail global object VA E09F9C; its mutex handle occupies E09FA0.
// The real C++ definition emits initializer49B and registered cleanup36B.
Rva00CE12FCMutex g_rva00CE12FCMutex;

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?ticks@Rva00CE12FCMutex@@UAEKXZ=_current_time")
#pragma comment(linker, "/alternatename:?wait@Rva00CE12FCMutex@@UAEXXZ=?bfmeGo1037H@BfmeH1037@@QAEXXZ")
#pragma comment(linker, "/alternatename:?release@Rva00CE12FCMutex@@UAEXXZ=?bfmeGo1038D@BfmeD1038@@QAEXXZ")
