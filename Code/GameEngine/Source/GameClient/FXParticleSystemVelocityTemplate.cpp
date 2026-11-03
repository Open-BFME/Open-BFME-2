// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME1 hemispherical velocity-template constructor transferred to BFME2.
// The three subobjects retain their BFME2 retail vtables after the spherical
// base constructor runs.

extern "C" char HemisphericalEmissionVelocityModuleTemplate_cvtbl0;  // 0x00C1BC60, defined by HemisphericalEmissionVelocityModuleTemplateCopyCtorThunk.cpp

extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[];  // folded, 35 classes

extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@@FXParticleSystem@@@FXParticleSystem@@6BHemisphericalEmissionVelocityInfo@1@@")[];  // folded, 2 classes

extern "C" const void *const __identifier("??_7SphereEmissionVolumeInfo@FXParticleSystem@@6B@")[];

#include "../../Include/GameClient/EmissionVolumeInfo.h"
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


class SphereEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    SphereEmissionVolumeInfo(const SphereEmissionVolumeInfo &that);

    unsigned int m_radius;
};

// ??0HemisphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@XZ
HemisphericalEmissionVelocityModuleTemplate::HemisphericalEmissionVelocityModuleTemplate()
{
    *reinterpret_cast<unsigned int *>(this) = (unsigned int)&HemisphericalEmissionVelocityModuleTemplate_cvtbl0;
    *reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(this) + 4) = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(this) + 8) = ((unsigned int)__identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@@FXParticleSystem@@@FXParticleSystem@@6BHemisphericalEmissionVelocityInfo@1@@"));
}

// ??0SphereEmissionVolumeInfo@FXParticleSystem@@QAE@ABV01@@Z
SphereEmissionVolumeInfo::SphereEmissionVolumeInfo(const SphereEmissionVolumeInfo &that)
    : EmissionVolumeInfo(that)
{
    *reinterpret_cast<unsigned int *>(this) = ((unsigned int)__identifier("??_7SphereEmissionVolumeInfo@FXParticleSystem@@6B@"));
    m_radius = that.m_radius;
}

}
