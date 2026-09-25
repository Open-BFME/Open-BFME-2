// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean-C++ GpuDrawModuleTemplate default constructor.

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

class GpuDrawModuleInfo
{
public:
    GpuDrawModuleInfo();
    virtual ~GpuDrawModuleInfo();

private:
    unsigned char m_body[0x2c];
};

class GpuDrawModuleTemplate : public CategoryModuleTemplate<6>,
    public GpuDrawModuleInfo
{
public:
    GpuDrawModuleTemplate();
};

// ??0GpuDrawModuleTemplate@FXParticleSystem@@QAE@XZ
GpuDrawModuleTemplate::GpuDrawModuleTemplate()
    : CategoryModuleTemplate<6>(), GpuDrawModuleInfo()
{
}

}
