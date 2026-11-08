// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME1 hemispherical velocity-template constructor transferred to BFME2.
// The three subobjects retain their BFME2 retail vtables after the spherical
// base constructor runs.

extern "C" const void *const __identifier("??_7SphereEmissionVolumeInfo@FXParticleSystem@@6B@")[];

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../Include/GameClient/EmissionVolumeInfo.h"
#include "../../Include/GameClient/SphereEmissionVolumeInfo.h"
#include "../../Include/GameClient/SphericalEmissionVelocityInfo.h"
namespace FXParticleSystem
{

class ModuleTemplate
{
public:
    ModuleTemplate();
    virtual ~ModuleTemplate();
};

// Retail's nested category shape (LINK-584).
template <int CATEGORY_ARG>
class CategoryModuleInfo
{
public:
    virtual void v1() = 0;

protected:
    ~CategoryModuleInfo();
};

template <int CATEGORY_ARG>
class CategoryModuleTemplateBase : public ModuleTemplate, public CategoryModuleInfo<CATEGORY_ARG>
{
public:
    CategoryModuleTemplateBase();
    virtual ~CategoryModuleTemplateBase();
};

class SphericalEmissionVelocityModuleTemplate : public CategoryModuleTemplateBase<4>,
    public SphericalEmissionVelocityInfo
{
public:
    SphericalEmissionVelocityModuleTemplate();
    virtual ~SphericalEmissionVelocityModuleTemplate();
};

class HemisphericalEmissionVelocityModuleTemplate
    : public SphericalEmissionVelocityModuleTemplate
{
public:
    HemisphericalEmissionVelocityModuleTemplate();
    virtual ~HemisphericalEmissionVelocityModuleTemplate();
};

// ??0HemisphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@XZ
HemisphericalEmissionVelocityModuleTemplate::HemisphericalEmissionVelocityModuleTemplate()
{
}

// ??0SphereEmissionVolumeInfo@FXParticleSystem@@QAE@ABV01@@Z
SphereEmissionVolumeInfo::SphereEmissionVolumeInfo(const SphereEmissionVolumeInfo &that)
    : EmissionVolumeInfo(that)
{
    *reinterpret_cast<unsigned int *>(this) = ((unsigned int)__identifier("??_7SphereEmissionVolumeInfo@FXParticleSystem@@6B@"));
    m_radius = that.m_radius;
}

}
