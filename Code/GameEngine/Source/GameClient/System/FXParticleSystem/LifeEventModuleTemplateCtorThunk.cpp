// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// LifeEventModuleTemplate default constructor @0x3A999C: the base at rowed
// 0x00001EF9, then the info constructor at pinned 0x00564001, then the three
// vtable stores.

namespace FXParticleSystem
{

class ModuleTemplate
{
public:
    virtual ~ModuleTemplate();
};

class SecondaryModuleBase
{
public:
    virtual ~SecondaryModuleBase();
};

class ModuleInfo
{
};

class EventModuleInfo : public ModuleInfo
{
public:
    EventModuleInfo() {}

    bool m_first;
    bool m_second;
};

template <int CATEGORY>
class CategoryModuleTemplate;

template <>
class CategoryModuleTemplate<8> : public ModuleTemplate, public SecondaryModuleBase,
                                  public EventModuleInfo
{
public:
    CategoryModuleTemplate();
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
