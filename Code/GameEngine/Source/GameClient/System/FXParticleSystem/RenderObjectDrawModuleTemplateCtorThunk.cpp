// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean-C++ RenderObjectDrawModuleTemplate default constructor.

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/RenderObjectDrawModuleInfo.h"
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


class RenderObjectDrawModuleTemplate : public CategoryModuleTemplate<6>,
    public RenderObjectDrawModuleInfo
{
public:
    RenderObjectDrawModuleTemplate();
    virtual ~RenderObjectDrawModuleTemplate();
};

// ??0RenderObjectDrawModuleTemplate@FXParticleSystem@@QAE@XZ
RenderObjectDrawModuleTemplate::RenderObjectDrawModuleTemplate()
    : CategoryModuleTemplate<6>(), RenderObjectDrawModuleInfo()
{
}

}
