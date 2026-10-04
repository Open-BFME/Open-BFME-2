// cl: /O1 /MD
// ?rva0073F778@Rva0073F778@@QAE_NP6GIPAX@Z0HIH0@Z @0x0073F778 129B.
// Creates a suspended thread via _beginthreadex, sets priority from an index,
// optionally resumes, and reports success. Evidence: unlock lane packet;
// IAT imports via dllimport; switch maps 0-6 to priorities.
extern "C" __declspec(dllimport) unsigned __cdecl _beginthreadex(void *security, unsigned stackSize, unsigned (__stdcall *start)(void *), void *arglist, unsigned initflag, unsigned *thrdaddr);
extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(void *hThread, int nPriority);
extern "C" __declspec(dllimport) unsigned long __stdcall ResumeThread(void *hThread);
class Rva0073F778 {
    char _pad[4];
    void *m_handle;
public:
    bool rva0073F778(unsigned (__stdcall *start)(void *), void *arglist, int resume, unsigned stackSize, int priority, void *security);
    bool rva0073F83F(int resume, unsigned stackSize, int priority, void *security);
};
unsigned __stdcall Rva0073F833Cb(void *arg);
bool Rva0073F778::rva0073F778(unsigned (__stdcall *start)(void *), void *arglist, int resume, unsigned stackSize, int priority, void *security)
{
    void *h = (void *)_beginthreadex(security, stackSize, start, arglist, 4, (unsigned *)&arglist);
    m_handle = h;
    if (h) {
        switch (priority) {
        case 0: priority = -15; break;
        case 1: priority = -2; break;
        case 2: priority = -1; break;
        case 3: priority = 0; break;
        case 4: priority = 1; break;
        case 5: priority = 2; break;
        case 6: priority = 15; break;
        default: priority = 0; break;
        }
        SetThreadPriority(h, priority);
        if (resume != 0)
            ResumeThread(m_handle);
        return true;
    }
    return false;
}

// ?rva0073F83F@Rva0073F778@@QAE_NHIHPAX@Z @0x0073F83F 30B.
// Forwards to the spawner above with a fixed start routine and this as arg.
// Evidence: chain lane packet; same this; ret 0x10.
bool Rva0073F778::rva0073F83F(int resume, unsigned stackSize, int priority, void *security)
{
    return rva0073F778((unsigned (__stdcall *)(void *))Rva0073F833Cb, this, resume, stackSize, priority, security);
}

// ?Rva0073F833Cb@@YGIPAX@Z @0x0073F833 12B. Thread-start thunk calling virtual slot 3 on its arg.
// Evidence: LINK BONUS 159B in this file; gap between 0x0073F778 and 0x0073F83F; same /O1 /MD TU; indirect call needs no callee row.
struct Rva0073F833If {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual unsigned v3();
};
unsigned __stdcall Rva0073F833Cb(void *arg)
{
    return ((Rva0073F833If *)arg)->v3();
}
