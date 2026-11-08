// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: DefaultModuleTemplate (ledger $06 / N=7) ctor
// Retail: the category constructor, then three vtbl stores at +0/+4/+8.

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/WindModuleInfo.h"

namespace FXParticleSystem
{

class ModuleTemplate
{
public:
    ModuleTemplate();
    ModuleTemplate(const ModuleTemplate &that);
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
    CategoryModuleTemplateBase(const CategoryModuleTemplateBase<CATEGORY_ARG> &that);
    virtual ~CategoryModuleTemplateBase();
};

template <int CATEGORY>
class CategoryModuleTemplate;

template <>
class CategoryModuleTemplate<7> : public CategoryModuleTemplateBase<7>, public WindModuleInfo
{
public:
    CategoryModuleTemplate();
    CategoryModuleTemplate(const CategoryModuleTemplate<7> &that);
    virtual ~CategoryModuleTemplate();
};

template <int N>
class DefaultModuleTemplate;

template <>
class DefaultModuleTemplate<7> : public CategoryModuleTemplate<7>
{
public:
    DefaultModuleTemplate();
    DefaultModuleTemplate(const DefaultModuleTemplate<7> &that);
    virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<7>::DefaultModuleTemplate()
{
}
}
