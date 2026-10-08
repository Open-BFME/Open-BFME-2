// ??0LargeGroupAudioUpdateModuleData@@QAE@XZ
// partial score=0.99 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc /O1 /D_STLP_USE_STATIC_LIB /Ireference/shims/moduledata
// stlport
#include <vector>
#include "Common/Snapshot.h"
extern "C" __declspec(dllimport) double __cdecl ceil(double);
extern float g_parseDurationMsecScale;
struct Rva001408C0Target;
struct Rva00E03CE0 { void Rva004ABEAE(Rva001408C0Target *); };
extern Rva00E03CE0 g_00E03CE0;
class LargeGroupAudioKeyMap : public _STL::vector<unsigned> {
public: LargeGroupAudioKeyMap(); ~LargeGroupAudioKeyMap();
};
LargeGroupAudioKeyMap::LargeGroupAudioKeyMap() : _STL::vector<unsigned>() {}
class LargeGroupAudioUpdateModuleData : public Snapshot {
public:
    LargeGroupAudioUpdateModuleData(); virtual ~LargeGroupAudioUpdateModuleData();
protected:
    virtual void loadPostProcess(); virtual void crc(Xfer *); virtual void xfer(Xfer *);
private:
    unsigned int m_04;
    LargeGroupAudioKeyMap m_keys;
    int m_min; int m_variance; unsigned short m_weight;
};
LargeGroupAudioUpdateModuleData::LargeGroupAudioUpdateModuleData() :
    m_keys(), m_min((int)ceil(g_parseDurationMsecScale * 500.0f)), m_variance(1), m_weight(1)
{
    g_00E03CE0.Rva004ABEAE((Rva001408C0Target *)this);
}
