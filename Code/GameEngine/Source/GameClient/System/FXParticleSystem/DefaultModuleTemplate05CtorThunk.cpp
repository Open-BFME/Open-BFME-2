// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean-C++ DefaultModuleTemplate (ledger $05 / N=6) default constructor.

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

class DefaultDrawModuleInfo
{
public:
    DefaultDrawModuleInfo();
    virtual ~DefaultDrawModuleInfo();

private:
    unsigned char m_body[0x2c];
};

template <int Category>
class DefaultModuleTemplate : public CategoryModuleTemplate<Category>,
    public DefaultDrawModuleInfo
{
public:
    DefaultModuleTemplate();
};

// MSVC mangles DefaultModuleTemplate<6> as @$05
// ??0?$DefaultModuleTemplate@$05@FXParticleSystem@@QAE@XZ
template <int Category>
DefaultModuleTemplate<Category>::DefaultModuleTemplate()
    : CategoryModuleTemplate<Category>(), DefaultDrawModuleInfo()
{
}

template DefaultModuleTemplate<6>::DefaultModuleTemplate();

}
