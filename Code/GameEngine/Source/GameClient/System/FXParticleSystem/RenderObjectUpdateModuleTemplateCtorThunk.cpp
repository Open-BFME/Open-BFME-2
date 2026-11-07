// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean-C++ RenderObjectUpdateModuleTemplate default constructor.

// Retail exports spell the info's slots LoadPostProcess and DoXfer(Xfer &).
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/RenderObjectUpdateModuleInfo.h"
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


class RenderObjectUpdateModuleTemplate : public CategoryModuleTemplate<2>,
    public RenderObjectUpdateModuleInfo
{
public:
    RenderObjectUpdateModuleTemplate();
    virtual ~RenderObjectUpdateModuleTemplate();
};

// ??0RenderObjectUpdateModuleTemplate@FXParticleSystem@@QAE@XZ
RenderObjectUpdateModuleTemplate::RenderObjectUpdateModuleTemplate()
    : CategoryModuleTemplate<2>(), RenderObjectUpdateModuleInfo()
{
}

}
