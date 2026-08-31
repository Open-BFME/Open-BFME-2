// cl: /O1 /GX-

namespace FXParticleSystem
{

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

}
