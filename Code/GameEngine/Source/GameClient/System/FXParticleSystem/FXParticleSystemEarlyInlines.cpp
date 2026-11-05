// cl: /Ireference/shims/moduledata
// FXParticleSystem::EventModuleInfo's constructor (0x00001236, 10 bytes) and
// ParticleSystemInfo::GetSnapshotName (0x00001272, 6 bytes), both exported by
// name. They sit among the first functions of the image, beside the
// ModuleTemplate bodies FXParticleSystem.cpp rows at 0x000011B4..0x00001278:
// the first objects in retail's link order emitted them. They are rowed here,
// in a unit that emits nothing else, not in fx_particle_system.cpp, where these
// two early rows placed that unit first in link order, so the link kept its
// copies of Snapshot's inline functions (its ??_GSnapshot is not retail's).

namespace FXParticleSystem
{
class EventModuleInfo
{
public:
    EventModuleInfo()
    {
        m_unk0 = true;
        m_unk1 = true;
    }

private:
    bool m_unk0;
    bool m_unk1;
};

class ParticleSystemInfo
{
public:
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
};

// Exported empty post-load callback: ICF folds it onto the shared RET at 0x000B3FD0.
void ParticleSystemInfo::LoadPostProcess()
{
}

const char *ParticleSystemInfo::GetSnapshotName()
{
    return "FXParticleSystemInfo";
}
}

// The constructor is a header inline: FXParticleSystem.cpp's view emits it as a
// select-any copy, which an ordinary definition here would duplicate. The anchor
// keeps this unit's copy for the row; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeEventModuleInfoAnchor@@YAXPAVEventModuleInfo@FXParticleSystem@@@Z absent-from-retail
void _bfmeEventModuleInfoAnchor(FXParticleSystem::EventModuleInfo *info)
{
    info->FXParticleSystem::EventModuleInfo::EventModuleInfo();
}
#pragma inline_depth()
