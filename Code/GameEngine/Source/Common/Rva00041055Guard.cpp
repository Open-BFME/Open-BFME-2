// cl: /MD
// ?rva00041055@MilesMutexGuard@@QAE_NXZ @0x00041055 35B
// Guard-state query: if m_held, refresh it from slot-1 virtual of the +0
// mutex object (neg/sbb/inc normalizes the uchar result), return m_held.
// Evidence: dtor 0x0004122F (pinned ??1MilesMutexGuard@@QAE@XZ, LINK BONUS)
// tail-jmps here when +4 set; callers at 0x0005D9C2 0x000A8371 0x000A840C;
// call dword ptr [eax+4] is an indirect virtual slot so no callee row/pin
// is needed. Class proven by dtor pin; method name honest address-derived
// (cf. Object::rva0028AF76). Slot-1 target unidentified: TU-local filler.
class Rva00041055Mutex
{
public:
    virtual void vf0();
    virtual unsigned char vf1();
};

class MilesMutexGuard
{
public:
    ~MilesMutexGuard();
    bool rva00041055();
private:
    Rva00041055Mutex *m_mutex; // +0
    bool m_flag; // +4: nonzero means re-query the mutex on next call
};

bool MilesMutexGuard::rva00041055()
{
    if (m_flag)
        m_flag = !m_mutex->vf1();
    return m_flag == 0;
}

// @0x0004122F 12B: LINK BONUS name; 40+ callers including MilesAudioManager
// sites; tail-jmps to rva00041055 when the flag is set.
MilesMutexGuard::~MilesMutexGuard()
{
    if (m_flag)
        rva00041055();
}
