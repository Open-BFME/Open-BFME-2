// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
// ?rva0005168C@MilesAudioManager@@QAEXEE@Z @0x0005168C 99B
// Flag-gated byte stores under guard over +0x9D4. Evidence: same guard rows as
// 0x0005710F/0x00052917; mutex +0x9D4 proven by StopAudio; next sibling
// MilesAudioManagerBuildProviderList proves MilesAudioManager; retail tests
// flags 1/0x10/2/4/8 to store val to +0x6A1/+0x6A2/+0x69F/+0x6A0/+0x69E.
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
    void rva0005168C(unsigned char val, unsigned char flags);
private:
    char m_pad0[0x69e];
    unsigned char m_69E;
    unsigned char m_69F;
    unsigned char m_6A0;
    unsigned char m_6A1;
    unsigned char m_6A2;
    char m_pad6A3[0x9D4 - 0x6A3];
    int m_mutex9D4;
};

void MilesAudioManager::rva0005168C(unsigned char val, unsigned char flags)
{
    MilesMutexGuard guard(&m_mutex9D4, 0);
    if (flags & 1)
        m_6A1 = val;
    if (flags & 0x10)
        m_6A2 = val;
    if (flags & 2)
        m_69F = val;
    if (flags & 4)
        m_6A0 = val;
    if (flags & 8)
        m_69E = val;
}
