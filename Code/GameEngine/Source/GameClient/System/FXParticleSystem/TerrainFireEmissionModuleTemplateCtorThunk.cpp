// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean-C++ TerrainFireEmissionModuleTemplate default constructor.

#include "../../../../Include/GameClient/TerrainFireEmissionInfo.h"
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


class TerrainFireEmissionModuleTemplate : public CategoryModuleTemplate<5>,
    public TerrainFireEmissionInfo
{
public:
    TerrainFireEmissionModuleTemplate();
    virtual ~TerrainFireEmissionModuleTemplate();
};

// ??0TerrainFireEmissionModuleTemplate@FXParticleSystem@@QAE@XZ
TerrainFireEmissionModuleTemplate::TerrainFireEmissionModuleTemplate()
    : CategoryModuleTemplate<5>(), TerrainFireEmissionInfo()
{
}

}
