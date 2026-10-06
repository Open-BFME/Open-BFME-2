// cl: /MD /EHsc /DNDEBUG
//
// Target evidence: Make001FCBD7 returns the static ParticleSystem at
// 0x00DFDD60. Its first guard constructs a ParticleSystemTemplate at
// 0x00DFDF40 from "--nullsystem" (the exported constructor at 0x001FC1E0);
// the second constructs the system with ID -2 and createSlaves=false using
// 0x001FC701. The registered callbacks at 0x00BB75A6 and 0x00BB759C destroy
// those same two objects. The measured object spacing is 0x1E0 for the system
// and 0xD4 for the template.
//
// Semantic donor: reference/open-bfme-1/game/GameEngine/Source/Common/
// BfmeNullParticleSystemZA.cpp uses the same two-local-static sequence and
// literal. Its ZA names and layouts are not treated as BFME2 facts; the types
// below follow BFME2 constructor/vtable/callback evidence.

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"


namespace FXParticleSystem
{
class ParticleSystemTemplate
{
public:
    ParticleSystemTemplate(const AsciiString &name);
    virtual ~ParticleSystemTemplate(void);

private:
    unsigned char m_unmodelled_004[0xD0];
};
}

enum ParticleSystemID
{
    INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystem
{
public:
    ParticleSystem(const FXParticleSystem::ParticleSystemTemplate *systemTemplate,
                   ParticleSystemID id, bool createSlaves);
    virtual ~ParticleSystem(void);

private:
    unsigned char m_unmodelled_004[0x1DC];
};

// ?Make001FCBD7@@YAPAVParticleSystem@@XZ
ParticleSystem *Make001FCBD7(void)
{
    static FXParticleSystem::ParticleSystemTemplate nullTemplate(
        AsciiString("--nullsystem"));

    static ParticleSystem nullSystem(&nullTemplate,
                                     (ParticleSystemID)-2, false);

    return &nullSystem;
}
