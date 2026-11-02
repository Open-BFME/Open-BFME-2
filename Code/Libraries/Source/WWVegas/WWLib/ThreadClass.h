// Target facts (addresses are RVAs unless marked VA):
//  - Constructor 0x00610430 and destructor 0x00610480 both store VA 0x00C7B6AC at +0; neither calls a parent constructor or destructor.
//  - Table 0x0087B6AC contains deleting destructor 0x00610620, Execute 0x006104B0 and __purecall 0x0003B810. The next word is string data, not a fourth slot.
//  - Callback 0x00610490 dispatches slot +8; derived table 0x0086AB40 binds it to rowed PingThreadClass::Thread_Function (0x005501F4).
//  - Constructor 0x00610430 copies the name to +4, defaults to "No name" from 0x0087B6A4, clears dwords +0x44/+0x48/+0x4C and returns with ret 4.
//  - Execute 0x006104B0 passes +0x44 to _beginthreadex (IAT VA 0x00BBA41C), stores its handle at +0x48 and passes +0x4C to SetThreadPriority (IAT VA 0x00BBA358).
//  - The final constructor write ends at +0x50; derived constructor 0x0054F93F places its first dword at +0x50, fixing the base size at 0x50 with one vptr and no intervening running flag or exception-handler field.
//  - Out-of-line rows are Set_Priority 0x006104F0, Stop(unsigned) 0x00610510, Switch_Thread 0x006105C0, _Get_Current_Thread_ID 0x006105D0, Is_Running 0x006105E0 and Stop() 0x006105F0; both Stop bodies and Is_Running access +0x48.
// Donor facts: Zero Hour WWLib/thread.h names ThreadName, ThreadID, handle, thread_priority and Thread_Function. The corresponding members below retain the matched BFME2 owner's m_name/m_threadId/m_handle/m_priority spellings; the donor's extra fields, two-argument constructor and nonvirtual Execute do not describe retail BFME2.

#pragma once

#ifndef BFME2_THREADCLASS_H
#define BFME2_THREADCLASS_H

#ifndef THREAD_H
#define THREAD_H
#endif

class ThreadClass
{
public:
    ThreadClass(const char *name = 0);
    virtual ~ThreadClass();
    virtual void Execute();

    void Set_Priority(int priority);
    bool Is_Running();
    void Stop();
    void Stop(unsigned ms);
    static void Sleep_Ms(unsigned ms = 0);
    static void Switch_Thread();
    static unsigned _Get_Current_Thread_ID();

protected:
    virtual void Thread_Function() = 0;

private:
    char m_name[64];
    unsigned m_threadId;
    void *m_handle;
    int m_priority;
};

#endif
