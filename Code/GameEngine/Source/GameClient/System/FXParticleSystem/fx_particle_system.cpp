// cl: /Ireference/shims/moduledata
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"

#include "../../../../Include/GameClient/EventModuleInfo.h"
namespace FXParticleSystem
{

// The constructor and ParticleSystemInfo::GetSnapshotName are rowed in
// FXParticleSystemEarlyInlines.cpp (retail places them among the image's first
// functions).

EventModuleInfo::~EventModuleInfo()
{
}

class ParticleSystemInfo
{
public:
    virtual const char *GetSnapshotName();
};

// LineEmissionVolumeInfo copy ctor, retail 0x003A653B (63B). BFME1 donor
// b1 0x005D5A90: base EmissionVolumeInfo copy (inlined: base vtable +
// flag byte) then the derived vtable and the six float copies. No
// out-of-line calls, so no pins. Snapshot is vtable-only here (4 bytes),
// which seats m_flag at +0x4 and the float block at +0x8 per retail.
class EmissionVolumeInfo : public Snapshot
{
public:
    virtual ~EmissionVolumeInfo() {}
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);

    bool m_flag;
};

class LineEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    LineEmissionVolumeInfo(const LineEmissionVolumeInfo &that);

private:
    float m_unk[6];
};

// ??0LineEmissionVolumeInfo@FXParticleSystem@@QAE@ABV01@@Z
LineEmissionVolumeInfo::LineEmissionVolumeInfo(const LineEmissionVolumeInfo &that)
    : EmissionVolumeInfo(that)
{
    m_unk[0] = that.m_unk[0];
    m_unk[1] = that.m_unk[1];
    m_unk[2] = that.m_unk[2];
    m_unk[3] = that.m_unk[3];
    m_unk[4] = that.m_unk[4];
    m_unk[5] = that.m_unk[5];
}
// Retail export225 identifies the Cylinder copy folded with Line at3A653B.
class CylinderEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    CylinderEmissionVolumeInfo(const CylinderEmissionVolumeInfo &that);

private:
    float m_unk[6];
};

// ??0CylinderEmissionVolumeInfo@FXParticleSystem@@QAE@ABV01@@Z
CylinderEmissionVolumeInfo::CylinderEmissionVolumeInfo(const CylinderEmissionVolumeInfo &that)
    : EmissionVolumeInfo(that)
{
    m_unk[0] = that.m_unk[0];
    m_unk[1] = that.m_unk[1];
    m_unk[2] = that.m_unk[2];
    m_unk[3] = that.m_unk[3];
    m_unk[4] = that.m_unk[4];
    m_unk[5] = that.m_unk[5];
}
}
