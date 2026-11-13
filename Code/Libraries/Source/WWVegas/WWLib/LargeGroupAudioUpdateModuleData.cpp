// LargeGroupAudioUpdateModuleData: registered factory 0x24F362; native table 0xC549F8.
// cl: /G7 /O1 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include/Common
// stlport
#include <vector>
#include "Common/Snapshot.h"
#include "BfmeModuleData.h"
// Native table has the shared 31-slot ModuleData interface, ending at 0xC54A74.
// Native teardown then restores Snapshot table 0xBBB554; original intermediate
// inheritance and the meaning of the word at +4 remain unrecovered.
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
#include <math.h>
extern float g_parseDurationMsecScale;
struct Rva001408C0Target;
#include "../../../../GameEngine/Include/Common/Rva00E03CE0.h"
// Existing data-ledger owner; use typed views of the one registry datum.
#include "../../../../GameEngine/Include/Common/ModuleKeyRegistryStorage.h"
class Rva003ED94FDtor {
public:
    Rva003ED94FDtor();
    ~Rva003ED94FDtor();
private:
    void *m_words[2];
    unsigned int m_count;
};
class LargeGroupAudioUpdateModuleData : public ModuleData {
public:
    LargeGroupAudioUpdateModuleData(); virtual __declspec(noinline) ~LargeGroupAudioUpdateModuleData();
private:
    unsigned int m_04;
    Rva003ED94FDtor m_keys;
    int m_min; int m_variance; unsigned short m_weight;
};
LargeGroupAudioUpdateModuleData::LargeGroupAudioUpdateModuleData() :
    m_keys()
{
    float f = g_parseDurationMsecScale * 500.0f;
    double d = (double)f;
    m_min = (int)ceil(d);
    m_variance = 1;
    m_weight = 1;
    reinterpret_cast<Rva00E03CE0 *>(&BfmeLargeGroupAudioRegistry)->Rva004ABEAE((Rva001408C0Target *)this);
}
