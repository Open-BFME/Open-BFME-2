// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// TerrainCollisionModuleTemplate default constructor @0x3AA078: the base at
// rowed 0x00001EF9, then the info constructor at pinned 0x0056459E, then the
// three vtable stores.

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
    EventModuleInfo();

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
    ~CategoryModuleTemplate();
};

class TerrainCollisionModuleInfo
{
public:
    TerrainCollisionModuleInfo();
    virtual ~TerrainCollisionModuleInfo();
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
