// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean-C++ DefaultModuleTemplate (ledger $00 / N=1) default constructor.

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
    virtual void unusedVirtual();

protected:
    ~CategoryModuleInfo() {}
};

template <int Category>
class CategoryModuleTemplateBase : public ModuleTemplate,
    public CategoryModuleInfo<Category>
{
public:
    CategoryModuleTemplateBase() {}
    virtual ~CategoryModuleTemplateBase() {}
};

template <int Category>
class CategoryModuleTemplate : public CategoryModuleTemplateBase<Category>
{
public:
    CategoryModuleTemplate() {}
    virtual ~CategoryModuleTemplate() {}
};

class DefaultAlphaModuleInfo
{
public:
    DefaultAlphaModuleInfo();
    virtual ~DefaultAlphaModuleInfo();

private:
    unsigned char m_body[0x2c];
};

template <int Category>
class DefaultModuleTemplate : public CategoryModuleTemplate<Category>,
    public DefaultAlphaModuleInfo
{
public:
    DefaultModuleTemplate();
};

// MSVC mangles DefaultModuleTemplate<1> as @$00
// ??0?$DefaultModuleTemplate@$00@FXParticleSystem@@QAE@XZ
template <int Category>
DefaultModuleTemplate<Category>::DefaultModuleTemplate()
    : CategoryModuleTemplate<Category>(), DefaultAlphaModuleInfo()
{
}

template DefaultModuleTemplate<1>::DefaultModuleTemplate();

}
