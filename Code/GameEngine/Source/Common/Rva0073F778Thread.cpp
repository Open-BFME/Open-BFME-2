// cl: /MD
// platformsdk
// ?createThread@Rva0073F778@@QAE_NP6GIPAX@Z0HIH0@Z @0x0073F778 129B.
// Creates a suspended thread via _beginthreadex, sets priority from an index,
// optionally resumes, and reports success. Evidence: unlock lane packet;
// IAT imports via dllimport; switch maps 0-6 to priorities.
#include <windows.h>
#include <process.h>
class Rva0073F778 {
    char _pad[4];
    void *m_handle;
public:
    bool createThread(unsigned (__stdcall *start)(void *), void *arglist, int resume, unsigned stackSize, int priority, void *security);
    bool startThread(int resume, unsigned stackSize, int priority, void *security);
    int resume();
    bool suspend();
};
unsigned __stdcall Rva0073F833Cb(void *arg);
bool Rva0073F778::createThread(unsigned (__stdcall *start)(void *), void *arglist, int resume, unsigned stackSize, int priority, void *security)
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

// ?startThread@Rva0073F778@@QAE_NHIHPAX@Z @0x0073F83F 30B.
// Forwards to the spawner above with a fixed start routine and this as arg.
// Evidence: chain lane packet; same this; ret 0x10.
bool Rva0073F778::startThread(int resume, unsigned stackSize, int priority, void *security)
{
    return createThread((unsigned (__stdcall *)(void *))Rva0073F833Cb, this, resume, stackSize, priority, security);
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

// ?resume@Rva0073F778@@QAEHXZ @0x0073F7F9 38B and ?suspend@Rva0073F778@@QAE_NXZ
// @0x0073F81F 20B: the thread handle at +4 through ResumeThread and
// SuspendThread (IAT 0x00BBA248 / 0x00BBA258). Resume folds the previous
// suspend count into 0, 1, 2 (still suspended) or 3 (failure); suspend reports
// success. Method names are descriptive of the calls only.
int Rva0073F778::resume()
{
    switch (ResumeThread(m_handle)) {
    case 0: return 0;
    case 1: return 1;
    case 0xFFFFFFFF: return 3;
    default: return 2;
    }
}

bool Rva0073F778::suspend()
{
    return SuspendThread(m_handle) != 0xFFFFFFFF;
}
