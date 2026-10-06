// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
// ?rva00052917@MilesAudioManager@@QAEHXZ @0x00052917 51B
// Post-increment counter at +0xD0 under guard over +0x9D4 returning old value.
// Evidence: same MilesMutexGuard ctor/dtor rows as 0x0005710F; mutex +0x9D4
// proven by MilesAudioManagerStopAudio; retail lea/mov/lea/mov plus mov eax esi.
class MilesMutexGuard
{
public:
    MilesMutexGuard(void *mutex, int defer);
    ~MilesMutexGuard();
private:
    void *m_mutex;
    bool m_held;
};

class MilesAudioManager
{
public:
    int rva00052917();
private:
    char m_pad0[0xd0];
    int m_counterD0;
    char m_padD4[0x9D4 - 0xD4];
    int m_mutex9D4;
};

int MilesAudioManager::rva00052917()
{
    MilesMutexGuard guard(&m_mutex9D4, 0);
    int cur = m_counterD0;
    m_counterD0 = cur + 1;
    return cur;
}
