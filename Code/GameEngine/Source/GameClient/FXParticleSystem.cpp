// cl: /O1 /GX- /arch:SSE2

struct Region2D
{
    float x_min;
    float y_min;
    float x_max;
    float y_max;
};

namespace FXParticleSystem
{

class ParticleSystemTemplate
{
public:
    void setUV(const Region2D *region);

private:
    char m_unknown[0x88];
    Region2D m_uv;
};

void ParticleSystemTemplate::setUV(const Region2D *region)
{
    if (region != 0)
        m_uv = *region;
}

// ModuleTemplate holds nothing but its vtable (0x00BBB52C): the constructors
// install it and the destructor restores it, with no member traffic at all.
class ModuleTemplate
{
public:
    ModuleTemplate();
    ModuleTemplate(const ModuleTemplate &that);

    virtual ~ModuleTemplate();
    virtual void v1() = 0;
};

ModuleTemplate::ModuleTemplate()
{
}

ModuleTemplate::ModuleTemplate(const ModuleTemplate &that)
{
}

ModuleTemplate::~ModuleTemplate()
{
}

// Two independent flags, not one 16-bit field: the CategoryModuleTemplate<8>
// constructor stores 1 into offsets 8 and 9 with two byte moves, while the
// compiler-generated assignment folds them into a single word copy.
class ModuleInfo
{
};

class EventModuleInfo : public ModuleInfo
{
public:
    EventModuleInfo()
    {
        m_first = true;
        m_second = true;
    }

    bool m_first;
    bool m_second;
};

// A second polymorphic base sitting at offset 4: the CategoryModuleTemplate
// constructors store a .rdata vtable there both before and after the primary
// vtable store, which is what a base and derived pair of identical (and so
// COMDAT-folded) tables looks like. Its identity is not recovered yet.
//
// Its destructor has to be defined here, not just declared: the
// CategoryModuleTemplate<1> destructor at 0x00001F18 inlines it down to the one
// vtable store, behind the null-checked +4 adjustment of `this`.
class SecondaryModuleBase
{
public:
    SecondaryModuleBase();

    virtual ~SecondaryModuleBase();
    virtual void v1() = 0;
};

SecondaryModuleBase::SecondaryModuleBase()
{
}

SecondaryModuleBase::~SecondaryModuleBase()
{
}

// EventModuleInfo lands at offset 8, behind both vtables. Its assignment is the
// compiler-generated one, reached only through the generated assignment of a
// derived class - which is exactly what CategoryModuleTemplate<8> at 0x0000124F
// is, right down to the null-checked adjustment of the source pointer by 8.
//
// The category selects the third base: <1> carries the empty ModuleInfo and <8>
// the two-flag EventModuleInfo, which is what makes the <8> constructor at
// 0x00001EF9 the <1> constructor at 0x00001D69 plus the two byte stores.
template <int CATEGORY>
struct CategoryInfo
{
    typedef ModuleInfo Type;
};

template <>
struct CategoryInfo<8>
{
    typedef EventModuleInfo Type;
};

template <int CATEGORY>
class CategoryModuleTemplate : public ModuleTemplate,
                               public SecondaryModuleBase,
                               public CategoryInfo<CATEGORY>::Type
{
public:
    virtual void v1();
};

// The retail instantiations are reached through derived module templates, so
// nothing in this translation unit would emit their constructors on its own.
// A file-scope instance of each is what forces them out.
CategoryModuleTemplate<1> g_categoryModuleTemplate1;
CategoryModuleTemplate<8> g_categoryModuleTemplate8;

typedef CategoryModuleTemplate<8> EventCategoryModuleTemplate;
typedef EventCategoryModuleTemplate &(EventCategoryModuleTemplate::*EventCategoryAssign)(
    const EventCategoryModuleTemplate &);

EventCategoryAssign g_eventCategoryAssign = &EventCategoryModuleTemplate::operator=;

// Every module category has a display name and an INI key, kept side by side in
// one eight-byte table entry; both accessors index it with the category and
// differ only by which half they read.
struct ModuleCategoryNames
{
    const char *m_name;
    const char *m_key;
};

extern const ModuleCategoryNames TheModuleCategoryNames[];

enum ModuleCategory
{
    MODULE_CATEGORY_FIRST
};

const char *GetName(ModuleCategory category)
{
    return TheModuleCategoryNames[category].m_name;
}

const char *GetKey(ModuleCategory category)
{
    return TheModuleCategoryNames[category].m_key;
}

// Both emission info bases carry nothing but a vtable, except that the volume
// one has a single byte behind it which its generated assignment copies on its
// own - the vtable is left alone, as an assignment must.
class EmissionVolumeInfo
{
public:
    EmissionVolumeInfo();
    EmissionVolumeInfo(const EmissionVolumeInfo &that);

    virtual ~EmissionVolumeInfo();
    virtual void v1() = 0;

    bool m_flag;
};

EmissionVolumeInfo::EmissionVolumeInfo()
{
    m_flag = false;
}

EmissionVolumeInfo::EmissionVolumeInfo(const EmissionVolumeInfo &that)
{
    m_flag = that.m_flag;
}

// One float behind the base's byte. The generated assignment copies both and
// leaves the vtable alone; the constructor zeroes the float with an xorps store
// after the vtable is in place.
class SphereEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    SphereEmissionVolumeInfo();

    float m_radius;
};

SphereEmissionVolumeInfo::SphereEmissionVolumeInfo()
{
    m_radius = 0.0f;
}

typedef SphereEmissionVolumeInfo &(SphereEmissionVolumeInfo::*SphereEmissionVolumeAssign)(
    const SphereEmissionVolumeInfo &);

SphereEmissionVolumeAssign g_sphereEmissionVolumeAssign = &SphereEmissionVolumeInfo::operator=;

class EmissionVelocityInfo
{
public:
    EmissionVelocityInfo();
    EmissionVelocityInfo(const EmissionVelocityInfo &that);

    virtual ~EmissionVelocityInfo();
    virtual void v1() = 0;
};

EmissionVelocityInfo::EmissionVelocityInfo()
{
}

EmissionVelocityInfo::EmissionVelocityInfo(const EmissionVelocityInfo &that)
{
}

// A time and a value, in that order: the constructor zeroes the float with an
// xorps store and the frame with an `and dword ptr, 0`.
class Keyframe
{
public:
    Keyframe();

    float m_value;
    unsigned int m_frame;
};

Keyframe::Keyframe()
{
    m_value = 0.0f;
    m_frame = 0;
}

typedef EmissionVolumeInfo &(EmissionVolumeInfo::*EmissionVolumeAssign)(const EmissionVolumeInfo &);

EmissionVolumeAssign g_emissionVolumeAssign = &EmissionVolumeInfo::operator=;

// One module class per category, registered into a table of eight pointers
// starting at 0x00DFDD1C. The registration is conditional on the second
// constructor argument, and the slot is the only thing that varies across the
// eight instantiations - which is what says the table is indexed by the
// category rather than looked up.
template <int CATEGORY>
class CategoryModuleClass
{
public:
    static const CategoryModuleClass<CATEGORY> *s_instance;
};

template <int CATEGORY>
const CategoryModuleClass<CATEGORY> *CategoryModuleClass<CATEGORY>::s_instance;

template <int CATEGORY, int MODULE_COUNT>
class CategoryModuleClassBase
{
protected:
    CategoryModuleClassBase(const CategoryModuleClass<CATEGORY> &that, bool registerIt);
};

template <int CATEGORY, int MODULE_COUNT>
CategoryModuleClassBase<CATEGORY, MODULE_COUNT>::CategoryModuleClassBase(
    const CategoryModuleClass<CATEGORY> &that, bool registerIt)
{
    if (registerIt) {
        CategoryModuleClass<CATEGORY>::s_instance = &that;
    }
}

template class CategoryModuleClassBase<0, 1>;
template class CategoryModuleClassBase<1, 1>;
template class CategoryModuleClassBase<2, 1>;
template class CategoryModuleClassBase<3, 1>;
template class CategoryModuleClassBase<4, 1>;
template class CategoryModuleClassBase<5, 1>;
template class CategoryModuleClassBase<6, 1>;
template class CategoryModuleClassBase<7, 1>;

// The four draw-module info classes carry nothing but their own vtable: both
// constructors install it and the copy constructor ignores its argument.
#define FX_VTABLE_ONLY_INFO(NAME)                                                                      class NAME                                                                                         {                                                                                                  public:                                                                                                NAME();                                                                                            NAME(const NAME &that);                                                                                                                                                                               virtual ~NAME();                                                                                    virtual void v1() = 0;                                                                         };                                                                                                                                                                                                    NAME::NAME() {}                                                                                    NAME::NAME(const NAME &that) {}

FX_VTABLE_ONLY_INFO(DefaultDrawModuleInfo)
FX_VTABLE_ONLY_INFO(StreakDrawModuleInfo)
FX_VTABLE_ONLY_INFO(QuadDrawModuleInfo)
FX_VTABLE_ONLY_INFO(ButterflyDrawModuleInfo)

}
