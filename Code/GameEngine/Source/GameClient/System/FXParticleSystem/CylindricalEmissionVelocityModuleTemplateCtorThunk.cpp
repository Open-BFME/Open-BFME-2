// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean-C++ CylindricalEmissionVelocityModuleTemplate default constructor.

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

class CylindricalEmissionVelocityInfo
{
public:
    CylindricalEmissionVelocityInfo();
    virtual ~CylindricalEmissionVelocityInfo();

private:
    unsigned char m_body[0x2c];
};

class CylindricalEmissionVelocityModuleTemplate : public CategoryModuleTemplate<4>,
    public CylindricalEmissionVelocityInfo
{
public:
    CylindricalEmissionVelocityModuleTemplate();
};

// ??0CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@XZ
CylindricalEmissionVelocityModuleTemplate::CylindricalEmissionVelocityModuleTemplate()
    : CategoryModuleTemplate<4>(), CylindricalEmissionVelocityInfo()
{
}

}
