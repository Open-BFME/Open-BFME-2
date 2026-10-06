// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0005710F@MilesAudioManager@@QAEXXZ @0x0005710F 66B
// Guarded clear of vector<BfmePod8> at +0xB54 with flag at +0x6AA. Evidence:
// mutex at +0x9D4 proven by MilesAudioManagerStopAudio (+0x9D4) and
// Rva00053CE1 (guard over +0x9D4); callees rowed MilesMutexGuard ctor/dtor and
// vector<BfmePod8>::erase range; retail cmp/je plus erase(start,finish).
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmePod8 { int a[2]; };

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
    void rva0005710F();
private:
    char m_pad0[0x6aa];
    bool m_flag6AA;
    char m_pad6AB[0x9D4 - 0x6AB];
    int m_mutex9D4;
    char m_pad9D8[0xB54 - 0x9D8];
    _STL::vector<BfmePod8> m_vecB54;
};

void MilesAudioManager::rva0005710F()
{
    MilesMutexGuard guard(&m_mutex9D4, 0);
    _STL::vector<BfmePod8> &v = m_vecB54;
    if (!v.empty()) {
        m_flag6AA = true;
        _ReadWriteBarrier();
        v.erase(v.begin(), v.end());
    }
}
