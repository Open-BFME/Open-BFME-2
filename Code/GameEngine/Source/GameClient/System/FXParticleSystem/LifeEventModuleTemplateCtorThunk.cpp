// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// LifeEventModuleTemplate default constructor @0x3A999C: the base at rowed
// 0x00001EF9, then the info constructor at pinned 0x00564001, then the three
// vtable stores.

#include "../../../../Include/GameClient/EventModuleInfo.h"
namespace FXParticleSystem
{

class ModuleTemplate
{
public:
    virtual ~ModuleTemplate();
};

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
};

#include "../../../../Include/Common/ModuleInfoClass.h"


template <int CATEGORY>
class CategoryModuleTemplate;

template <>
class CategoryModuleTemplate<8> : public CategoryModuleTemplateBase<8>,
                                  public EventModuleInfo
{
public:
    CategoryModuleTemplate();
    // LINK: declaration-only dtor (no body in this TU). The derived
    // LifeEventModuleTemplate ctor's EH references it; with no local body the
    // reference binds the kept copy instead of instantiating this TU's loser
    // copy, and all references are unchanged (same mangled name). The
    // rowed derived ctor is untouched. No flags touched.
    ~CategoryModuleTemplate();
};

class LifeEventModuleInfo
{
public:
    LifeEventModuleInfo();
    virtual ~LifeEventModuleInfo();
};

class LifeEventModuleTemplate : public CategoryModuleTemplate<8>, public LifeEventModuleInfo
{
public:
    LifeEventModuleTemplate();
    virtual ~LifeEventModuleTemplate();
};

// ??0LifeEventModuleTemplate@FXParticleSystem@@QAE@XZ @0x3A999C
LifeEventModuleTemplate::LifeEventModuleTemplate()
    : CategoryModuleTemplate<8>(), LifeEventModuleInfo()
{
}

}
