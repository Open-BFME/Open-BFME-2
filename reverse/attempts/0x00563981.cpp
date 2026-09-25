// ??0GpuDrawModuleInfo@FXParticleSystem@@QAE@XZ
// partial score=0.95 date=2026-09-25
// cl: /O1 /GX- /arch:SSE2

// GpuDrawModuleInfo default ctor, retail 0x00563981 (35B). BFME2-new class
// (no BFME1 donor); layout from retail: vtable 0xC1C1E8, two ints set to 1,
// one zeroed with an `and` store (/O1 shape), one float set to 1.0f from
// .rdata. Called by the GpuDrawModuleTemplate default at 0x003A9E58.

namespace FXParticleSystem
{

class GpuDrawModuleInfo
{
public:
    GpuDrawModuleInfo();
    virtual ~GpuDrawModuleInfo();

private:
    int m_unk04;
    int m_unk08;
    int m_unk0C;
    float m_unk10;
};

// ??0GpuDrawModuleInfo@FXParticleSystem@@QAE@XZ
GpuDrawModuleInfo::GpuDrawModuleInfo()
{
    m_unk04 = 1;
    m_unk08 = 1;
    m_unk0C = 0;
    m_unk10 = 1.0f;
}

}
