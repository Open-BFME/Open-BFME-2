// cl: /O1
// BFME1 hemispherical velocity-template constructor transferred to BFME2.
// The three subobjects retain their BFME2 retail vtables after the spherical
// base constructor runs.

namespace FXParticleSystem
{

class SphericalEmissionVelocityModuleTemplate
{
public:
    SphericalEmissionVelocityModuleTemplate();
};

class HemisphericalEmissionVelocityModuleTemplate
    : public SphericalEmissionVelocityModuleTemplate
{
public:
    HemisphericalEmissionVelocityModuleTemplate();
};

class EmissionVolumeInfo
{
private:
    unsigned int m_unknown0;
    unsigned int m_unknown4;

public:
    EmissionVolumeInfo(const EmissionVolumeInfo &that);
};

class SphereEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    SphereEmissionVolumeInfo(const SphereEmissionVolumeInfo &that);

    unsigned int m_radius;
};

// ??0HemisphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@XZ
HemisphericalEmissionVelocityModuleTemplate::HemisphericalEmissionVelocityModuleTemplate()
{
    *reinterpret_cast<unsigned int *>(this) = 0x00C1BC60;
    *reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(this) + 4) = 0x00C1C780;
    *reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(this) + 8) = 0x00C1C00C;
}

// ??0SphereEmissionVolumeInfo@FXParticleSystem@@QAE@ABV01@@Z
SphereEmissionVolumeInfo::SphereEmissionVolumeInfo(const SphereEmissionVolumeInfo &that)
    : EmissionVolumeInfo(that)
{
    *reinterpret_cast<unsigned int *>(this) = 0x00C1BB60;
    m_radius = that.m_radius;
}

}
