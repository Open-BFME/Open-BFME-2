// cl: /DNDEBUG /MD /GX
// platformsdk
#include <string.h>
#include <windows.h>
// stlport
// Use the native CRT declarations both alone and beside thread.cpp.
#include <stl/_config.h>
#include _STLP_NATIVE_C_HEADER(process.h)

extern "C" unsigned int __stdcall BFMENetworkBackendThreadStart(void *);
// Spelled out because thread.cpp's sweep windows.h shim does not declare it
// (same prototype as the Platform SDK's winbase.h).
extern "C" __declspec(dllimport) unsigned long __stdcall ResumeThread(void *thread);

class ThreadClass
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

// ThreadClass::ThreadClass: defined in ThreadClassCtor.cpp (its row's unit).

void ThreadClass::Set_Priority(int priority)
{
    m_priority = priority;
    if (m_handle)
        SetThreadPriority(m_handle, m_priority);
}

// ??1ThreadClass@@UAE@XZ @0x00610480 7B: resets the vptr to ??_7ThreadClass (0x0087B6AC).
ThreadClass::~ThreadClass()
{
}

#pragma optimize("s", on)
bool ThreadClass::Is_Running()
{
    return m_handle != 0;
}
#pragma optimize("s", off)

void ThreadClass::Stop()
{
    if (m_handle) {
        WaitForSingleObject(m_handle, 0xffffffff);
        m_handle = 0;
        m_threadId = 0;
    }
}

void ThreadClass::Execute()
{
    m_handle = reinterpret_cast<void *>(_beginthreadex(0, 0,
        BFMENetworkBackendThreadStart, this, 4, &m_threadId));
    SetThreadPriority(m_handle, m_priority);
    ResumeThread(m_handle);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?stop@Rva006105F0@@QAEXXZ=?Stop@ThreadClass@@QAEXXZ")
