// cl: /DNDEBUG /MD /GX /G7
// ThreadClass 1-arg ctor, retail 0x00610430 (72 bytes). Dedicated TU:
// ThreadClassLifecycle.cpp already holds 3 matched rows without /G7, and
// /G7 flips the strcpy-loop increment from inc-edx to retail add-edx-1
// (Begin_Scene_Inner/Check precedent: /G7 fixes INC-to-ADD walls).
// Source verbatim from that TU (1-arg, no exception handler): three null
// stores (m_threadId/m_handle/m_priority at +0x44/+0x48/+0x4C behind
// m_name[0x40] at +0x04) plus strcpy-or-"No name" memcpy.
#include <string.h>

// Retail vtable VA 0x0087B6AC (packet: no name yet). Referenced, never emitted
// here, so this TU contributes no vftable and no ??_G of its own.
extern const void *const g_00C7B6AC[];

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

// ??0ThreadClass@@QAE@PBD@Z
ThreadClass::ThreadClass(const char *name)
{
    *(const void **)this = g_00C7B6AC;
    m_handle = 0;
    m_priority = 0;
    m_threadId = 0;
    if (name)
        strcpy(m_name, name);
    else
        memcpy(m_name, "No name", 8);
}
