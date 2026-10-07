// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHs-c- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Target evidence for the wrapper is in retail; the receiver association is
// inferred from the +0x9D4 mutex and +0x12C/0x1C4 record array. The five-float
// setter at 0x0005230D remains address-derived.

class MilesMutexGuard
{
public:
    MilesMutexGuard(void *mutex, int defer);
    ~MilesMutexGuard();

private:
    void *m_mutex;
    bool m_held;
};

class Rva0005230D
{
public:
    void rva0005230D(float a, float b, float c, float d, float e);
};

class MilesAudioManager
{
public:
    void rva000537F4(float a, float b, float c, float d, float e, int index);

private:
    char at00[0x9D4];
    void *m_mutex;
};

void MilesAudioManager::rva000537F4(float a, float b, float c, float d,
                                    float e, int index)
{
    MilesMutexGuard guard(&m_mutex, 0);
    Rva0005230D *record = reinterpret_cast<Rva0005230D *>(
        reinterpret_cast<char *>(this) + 0x12C + index * 0x1C4);
    record->rva0005230D(a, b, c, d, e);
}
