// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean-C++ SphericalEmissionVelocityModuleTemplate default constructor.

#include "../../../../Include/GameClient/SphericalEmissionVelocityInfo.h"
namespace FXParticleSystem
{

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
class ModuleTemplate
{
public:
    ModuleTemplate() {}
    virtual ~ModuleTemplate() {}
};

template <int Category>
class CategoryModuleInfo
{
public:
    CategoryModuleInfo() {}
    virtual void unusedVirtual() = 0;

protected:
    ~CategoryModuleInfo() {}
};

template <int Category>
class CategoryModuleTemplateBase : public ModuleTemplate,
    public CategoryModuleInfo<Category>
{
public:
    __declspec(dllimport) __forceinline CategoryModuleTemplateBase() {}
    __declspec(dllimport) __forceinline virtual ~CategoryModuleTemplateBase() {}
};

template <int Category>
class CategoryModuleTemplate : public CategoryModuleTemplateBase<Category>
{
public:
    __declspec(dllimport) __forceinline CategoryModuleTemplate() {}
    virtual ~CategoryModuleTemplate();
};


class SphericalEmissionVelocityModuleTemplate : public CategoryModuleTemplate<4>,
    public SphericalEmissionVelocityInfo
{
public:
    SphericalEmissionVelocityModuleTemplate();
    virtual ~SphericalEmissionVelocityModuleTemplate();
};

// ??0SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@XZ
SphericalEmissionVelocityModuleTemplate::SphericalEmissionVelocityModuleTemplate()
    : CategoryModuleTemplate<4>(), SphericalEmissionVelocityInfo()
{
}

}

