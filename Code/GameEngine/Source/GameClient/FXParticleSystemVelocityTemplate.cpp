// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME1 hemispherical velocity-template constructor transferred to BFME2.
// The three subobjects retain their BFME2 retail vtables after the spherical
// base constructor runs.

extern "C" const void *const vtbl_00C1C780[];  // folded, 35 classes; via ??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C1C780=??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")

extern "C" const void *const vtbl_00C1C00C[];  // folded, 2 classes; via ??_7?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@@FXParticleSystem@@@FXParticleSystem@@6BHemisphericalEmissionVelocityInfo@1@@
#pragma comment(linker, "/alternatename:_vtbl_00C1C00C=??_7?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@@FXParticleSystem@@@FXParticleSystem@@6BHemisphericalEmissionVelocityInfo@1@@")

extern "C" const void *const vtbl_00C1BB60[];  // ??_7SphereEmissionVolumeInfo@FXParticleSystem@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C1BB60=??_7SphereEmissionVolumeInfo@FXParticleSystem@@6B@")

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
    *reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(this) + 4) = ((unsigned int)vtbl_00C1C780);
    *reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(this) + 8) = ((unsigned int)vtbl_00C1C00C);
}

// ??0SphereEmissionVolumeInfo@FXParticleSystem@@QAE@ABV01@@Z
SphereEmissionVolumeInfo::SphereEmissionVolumeInfo(const SphereEmissionVolumeInfo &that)
    : EmissionVolumeInfo(that)
{
    *reinterpret_cast<unsigned int *>(this) = ((unsigned int)vtbl_00C1BB60);
    m_radius = that.m_radius;
}

}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?construct_from@SphereEmissionVolumeModuleTemplateSubCopyShim@FXParticleSystem@@QAEXPBX@Z=??0SphereEmissionVolumeInfo@FXParticleSystem@@QAE@ABV01@@Z")
