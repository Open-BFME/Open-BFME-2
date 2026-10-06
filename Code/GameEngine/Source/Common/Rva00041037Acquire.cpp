// cl: /MD
// ?rva00041037@MilesMutexGuard@@QAE_NH@Z @0x00041037 30B
// Guarded acquire: if m_flag set return false else call slot-0 virtual of
// +0 mutex with int arg store result to +4 and return it. Evidence: ctor
// 0x0004120E (pinned ??0MilesMutexGuard@@QAE@PAXH@Z) inits +0/+4 then calls
// here with -1; neighbours Rva00041004Lock.cpp Rva00041055Guard.cpp share
// /O1 /MD; layout +0 mutex +4 flag proven by ctor/dtor pins.
class Rva00041037Mutex
{
public:
    virtual bool vf0(int x);
};

class MilesMutexGuard
{
public:
    MilesMutexGuard(void *m, int x);
    bool rva00041037(int x);
private:
    Rva00041037Mutex *m_mutex; // +0
    bool m_flag; // +4
};

MilesMutexGuard::MilesMutexGuard(void *m, int x) : m_mutex((Rva00041037Mutex *)m), m_flag(0)
{
    if (x == 0)
        rva00041037(-1);
}

bool MilesMutexGuard::rva00041037(int x)
{
    if (m_flag)
        return false;
    m_flag = m_mutex->vf0(x);
    return m_flag;
}
