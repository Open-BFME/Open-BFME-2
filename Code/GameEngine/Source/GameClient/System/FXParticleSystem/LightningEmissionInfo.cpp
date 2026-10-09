// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ob1 /Ireference/shims/moduledata
// Native 0055D9A5..0055DB41: LightningEmissionInfo default constructor.
// The named template constructor at 003A6C59 calls this body. Its target
// vtable C1BBA0 contains deleting dtor 003A6C0B (element size 8C), empty
// post-process 000B3FD0, EmissionVolumeInfo::GetSnapshotName 001F354A,
// and the folded empty DoXfer override at 0047A69C. These four slots also
// establish the selected canonical base surface independently of donor headers.
// Target stores prove flag04, coordinates08/14, and nine 12-byte random
// variables20..80; their setRange calls resolve to 002341E7. Member names
// below retain uncertainty about the individual variables' purposes.
// Existing DefaultUpdateModuleInfo supplies the default-range idiom.
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"

class GameClientRandomVariable
{
public:
    enum DistributionType
    {
        CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
    };
    GameClientRandomVariable() : m_type(CONSTANT), m_low(0.0f), m_high(0.0f) {}
    void setRange(float low, float high, DistributionType type = UNIFORM);
private:
    DistributionType m_type;
    float m_low, m_high;
};

namespace FXParticleSystem
{
class EmissionVolumeInfo : public Snapshot
{
public:
    EmissionVolumeInfo() { m_flag = false; }
    virtual ~EmissionVolumeInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(Xfer &);
    bool m_flag;
};

// The inline zero operation keeps coordinate initialization as two complete
// operations. Its assignment order reproduces retail's x/y/z stores and the
// compiler's interleaving of EH state and the first setRange arguments.
struct LightningCoordInfo
{
    float x, y, z;
    LightningCoordInfo() {}
    LightningCoordInfo(const LightningCoordInfo &p) { assign(p); }
    void assign(const LightningCoordInfo &p) { x = p.x; y = p.y; z = p.z; }
    void zero() { z = y = x = 0.0f; }
};

class LightningEmissionInfo : public EmissionVolumeInfo
{
public:
    LightningEmissionInfo();
    LightningEmissionInfo(const LightningEmissionInfo &that);
    virtual ~LightningEmissionInfo();
    LightningCoordInfo m_unknown08, m_unknown14;
    GameClientRandomVariable m_unknown20, m_unknown2C, m_unknown38;
    GameClientRandomVariable m_unknown44, m_unknown50, m_unknown5C;
    GameClientRandomVariable m_unknown68, m_unknown74, m_unknown80;
};
typedef char LightningEmissionInfoSizeCheck[sizeof(LightningEmissionInfo) == 0x8C ? 1 : -1];

LightningEmissionInfo::LightningEmissionInfo()
{
    m_unknown08.zero();
    m_unknown14.zero();
    m_unknown20.setRange(0.0f, 0.0f);
    m_unknown2C.setRange(0.0f, 0.0f);
    m_unknown38.setRange(0.0f, 0.0f);
    m_unknown44.setRange(0.0f, 0.0f);
    m_unknown50.setRange(0.0f, 0.0f);
    m_unknown5C.setRange(0.0f, 0.0f);
    m_unknown68.setRange(0.0f, 0.0f);
    m_unknown74.setRange(0.0f, 0.0f);
    m_unknown80.setRange(0.0f, 0.0f);
}
// Native003A6AF5..003A6B8F: the coordinate copy operation is inline and
// scalar; the nine random-variable copies use their three-dword implicit
// constructors. Initializing members avoids running their zero defaults.
LightningEmissionInfo::LightningEmissionInfo(const LightningEmissionInfo &that)
    : EmissionVolumeInfo(that),
      m_unknown08(that.m_unknown08), m_unknown14(that.m_unknown14),
      m_unknown20(that.m_unknown20), m_unknown2C(that.m_unknown2C),
      m_unknown38(that.m_unknown38), m_unknown44(that.m_unknown44),
      m_unknown50(that.m_unknown50), m_unknown5C(that.m_unknown5C),
      m_unknown68(that.m_unknown68), m_unknown74(that.m_unknown74),
      m_unknown80(that.m_unknown80)
{
}
}
