// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// TerrainCollisionModuleTemplate default constructor @0x3AA078: the base at
// rowed 0x00001EF9, then the info constructor at pinned 0x0056459E, then the
// three vtable stores.

#include "../../../../Include/GameClient/TerrainCollisionModuleInfo.h"
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
    ~CategoryModuleTemplate();
};


class TerrainCollisionModuleTemplate : public CategoryModuleTemplate<8>,
                                       public TerrainCollisionModuleInfo
{
public:
    TerrainCollisionModuleTemplate();
    virtual ~TerrainCollisionModuleTemplate();
};

// ??0TerrainCollisionModuleTemplate@FXParticleSystem@@QAE@XZ @0x3AA078
TerrainCollisionModuleTemplate::TerrainCollisionModuleTemplate()
    : CategoryModuleTemplate<8>(), TerrainCollisionModuleInfo()
{
}

}
