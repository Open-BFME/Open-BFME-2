// cl: /O1 /GX- /arch:SSE2

struct Region2D
{
    float x_min;
    float y_min;
    float x_max;
    float y_max;
};

// Placement new, used only to force generated copy constructors out; nothing in
// retail allocates through it.
inline void *operator new(unsigned int, void *storage)
{
    return storage;
}

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

// The two module bases are themselves a template. Its default constructor is
// folded into every derived one, but its COPY constructor is a real call - and
// ICF folds the nine instantiations onto one address, since none of them
// depends on the category.
template <int CATEGORY>
class CategoryModuleTemplateBase : public ModuleTemplate, public SecondaryModuleBase
{
public:
    CategoryModuleTemplateBase() {}
    __declspec(noinline) CategoryModuleTemplateBase(const CategoryModuleTemplateBase<CATEGORY> &that);
};

// Kept out of line so the derived copy constructors still call it, which is how
// retail spells them. The body is the generated one: the two base copies fold
// down to their vtable stores, and the derived fixup repeats the second.
template <int CATEGORY>
CategoryModuleTemplateBase<CATEGORY>::CategoryModuleTemplateBase(
    const CategoryModuleTemplateBase<CATEGORY> &)
{
}

template <int CATEGORY>
class CategoryModuleTemplate : public CategoryModuleTemplateBase<CATEGORY>,
                               public CategoryInfo<CATEGORY>::Type
{
public:
    virtual void v1();
};

// The retail instantiations are reached through derived module templates, so
// nothing in this translation unit would emit their constructors on its own.
// A file-scope instance of each is what forces them out.
CategoryModuleTemplate<0> g_categoryModuleTemplate0;
CategoryModuleTemplate<1> g_categoryModuleTemplate1;
CategoryModuleTemplate<2> g_categoryModuleTemplate2;
CategoryModuleTemplate<3> g_categoryModuleTemplate3;
CategoryModuleTemplate<4> g_categoryModuleTemplate4;
CategoryModuleTemplate<5> g_categoryModuleTemplate5;
CategoryModuleTemplate<6> g_categoryModuleTemplate6;
CategoryModuleTemplate<8> g_categoryModuleTemplate8;

typedef CategoryModuleTemplate<8> EventCategoryModuleTemplate;
typedef EventCategoryModuleTemplate &(EventCategoryModuleTemplate::*EventCategoryAssign)(
    const EventCategoryModuleTemplate &);

EventCategoryAssign g_eventCategoryAssign = &EventCategoryModuleTemplate::operator=;

// The generated assignments of every empty category - the two module bases and
// the info base alike - are `mov eax, ecx; ret 4`, so all of them fold onto the
// one address CategoryModuleInfo's assignment already owns. Nothing calls them,
// so a pointer-to-member each is what forces them out.
#define FX_FORCE_CATEGORY_ASSIGN(N)                                                typedef CategoryModuleTemplate<N> &(CategoryModuleTemplate<N>::                     *CategoryModuleTemplateAssign##N)(const CategoryModuleTemplate<N> &);       CategoryModuleTemplateAssign##N g_categoryModuleTemplateAssign##N =                 &CategoryModuleTemplate<N>::operator=;                                      typedef CategoryModuleTemplateBase<N> &(CategoryModuleTemplateBase<N>::             *CategoryModuleTemplateBaseAssign##N)(                                              const CategoryModuleTemplateBase<N> &);                                 CategoryModuleTemplateBaseAssign##N g_categoryModuleTemplateBaseAssign##N =         &CategoryModuleTemplateBase<N>::operator=;

FX_FORCE_CATEGORY_ASSIGN(0)
FX_FORCE_CATEGORY_ASSIGN(1)
FX_FORCE_CATEGORY_ASSIGN(2)
FX_FORCE_CATEGORY_ASSIGN(3)
FX_FORCE_CATEGORY_ASSIGN(4)
FX_FORCE_CATEGORY_ASSIGN(5)
FX_FORCE_CATEGORY_ASSIGN(6)

typedef EventModuleInfo &(EventModuleInfo::*EventModuleInfoAssign)(const EventModuleInfo &);

EventModuleInfoAssign g_eventModuleInfoAssign = &EventModuleInfo::operator=;

// The generated copy constructor is not emitted by the file-scope instances,
// which only ever default-construct; this is what forces it out.
CategoryModuleTemplate<8> *fxCopyEventCategoryModuleTemplate(void *storage,
    const CategoryModuleTemplate<8> &that)
{
    return new (storage) CategoryModuleTemplate<8>(that);
}

// Every category whose info base is the empty ModuleInfo produces the same copy
// constructor - base copy, then the two vtable stores - so ICF folds all seven
// onto 0x0004CB7B. These force each one out.
#define FX_FORCE_CATEGORY_COPY(N)                                                  CategoryModuleTemplate<N> *fxCopyCategoryModuleTemplate##N(void *storage,           const CategoryModuleTemplate<N> &that)                                     {                                                                                  return new (storage) CategoryModuleTemplate<N>(that);                       }

FX_FORCE_CATEGORY_COPY(0)
FX_FORCE_CATEGORY_COPY(1)
FX_FORCE_CATEGORY_COPY(2)
FX_FORCE_CATEGORY_COPY(3)
FX_FORCE_CATEGORY_COPY(4)
FX_FORCE_CATEGORY_COPY(5)
FX_FORCE_CATEGORY_COPY(6)

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

    virtual ~EmissionVolumeInfo() {}
    virtual void v1() = 0;

    bool m_flag;
    virtual const char *GetSnapshotName();
};

const char *EmissionVolumeInfo::GetSnapshotName()
{
    return "EmissionVolumeInfo";
}


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

// Three floats grouped as one member: the generated assignment copies them as a
// twelve-byte block with movsd while the generated copy constructor copies them
// one at a time, which is how MSVC 7.1 tells a sub-object apart from three loose
// scalars.
struct FXCoord3D
{
    float x;
    float y;
    float z;
};

class BoxEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    BoxEmissionVolumeInfo();
    BoxEmissionVolumeInfo(const BoxEmissionVolumeInfo &that);

    FXCoord3D m_half;
};

BoxEmissionVolumeInfo::BoxEmissionVolumeInfo()
{
    m_half.x = 0.0f;
    m_half.y = 0.0f;
    m_half.z = 0.0f;
}

// Written out rather than left to the compiler: the generated copy constructor
// is never emitted without a use, and retail copies the three floats one at a
// time here even though the generated assignment blocks them together.
BoxEmissionVolumeInfo::BoxEmissionVolumeInfo(const BoxEmissionVolumeInfo &that)
    : EmissionVolumeInfo(that)
{
    m_half.x = that.m_half.x;
    m_half.y = that.m_half.y;
    m_half.z = that.m_half.z;
}

class LineEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    LineEmissionVolumeInfo();

    FXCoord3D m_start;
    FXCoord3D m_end;
};

inline LineEmissionVolumeInfo::LineEmissionVolumeInfo()
{
    m_start.x = 0.0f;
    m_start.y = 0.0f;
    m_start.z = 0.0f;
    m_end.x = 0.0f;
    m_end.y = 0.0f;
    m_end.z = 0.0f;
}

class CylinderEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    CylinderEmissionVolumeInfo();

    float m_radius;
    float m_length;
    float m_radius2;
    FXCoord3D m_axis;
};

inline CylinderEmissionVolumeInfo::CylinderEmissionVolumeInfo()
{
    m_radius = 0.0f;
    m_length = 0.0f;
    m_radius2 = 0.0f;
    m_axis.x = 0.0f;
    m_axis.y = 0.0f;
    m_axis.z = 0.0f;
}

typedef BoxEmissionVolumeInfo &(BoxEmissionVolumeInfo::*BoxEmissionVolumeAssign)(
    const BoxEmissionVolumeInfo &);
typedef LineEmissionVolumeInfo &(LineEmissionVolumeInfo::*LineEmissionVolumeAssign)(
    const LineEmissionVolumeInfo &);
typedef CylinderEmissionVolumeInfo &(CylinderEmissionVolumeInfo::*CylinderEmissionVolumeAssign)(
    const CylinderEmissionVolumeInfo &);
BoxEmissionVolumeAssign g_boxEmissionVolumeAssign = &BoxEmissionVolumeInfo::operator=;
LineEmissionVolumeAssign g_lineEmissionVolumeAssign = &LineEmissionVolumeInfo::operator=;
CylinderEmissionVolumeAssign g_cylinderEmissionVolumeAssign =
    &CylinderEmissionVolumeInfo::operator=;

typedef SphereEmissionVolumeInfo &(SphereEmissionVolumeInfo::*SphereEmissionVolumeAssign)(
    const SphereEmissionVolumeInfo &);

SphereEmissionVolumeAssign g_sphereEmissionVolumeAssign = &SphereEmissionVolumeInfo::operator=;

class EmissionVelocityInfo
{
public:
    EmissionVelocityInfo();
    EmissionVelocityInfo(const EmissionVelocityInfo &that);

    virtual ~EmissionVelocityInfo() {}
    virtual void v1() = 0;
    virtual const char *GetSnapshotName();
};

const char *EmissionVelocityInfo::GetSnapshotName()
{
    return "EmissionVelocityInfo";
}


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
class CategoryModuleClass;

template <int CATEGORY, int MODULE_COUNT>
class CategoryModuleClassBase
{
public:
    static const CategoryModuleClass<CATEGORY> &getDefault();

protected:
    CategoryModuleClassBase(const CategoryModuleClass<CATEGORY> &that, bool registerIt);
};

// One load of the category's default slot. Unlike almost everything else in
// this family these do NOT fold: each category reads a different global, so
// 0x001F433B and its seven siblings are eight separate six-byte bodies.
template <int CATEGORY, int MODULE_COUNT>
const CategoryModuleClass<CATEGORY> &CategoryModuleClassBase<CATEGORY, MODULE_COUNT>::getDefault()
{
    return *CategoryModuleClass<CATEGORY>::s_instance;
}

// inline, and emitted anyway by the explicit instantiations below: without it
// MSVC 7.1 calls this out of line from the derived constructors, while retail
// folds it in ahead of the vtable store.
template <int CATEGORY, int MODULE_COUNT>
inline CategoryModuleClassBase<CATEGORY, MODULE_COUNT>::CategoryModuleClassBase(
    const CategoryModuleClass<CATEGORY> &that, bool registerIt)
{
    if (registerIt) {
        CategoryModuleClass<CATEGORY>::s_instance = &that;
    }
}

// The second parameter is not a module count but a has-default flag, and 0
// selects a different class rather than a different body: retail spells the
// event category's base constructor QAE, public, where every other category
// spells it IAE. It registers nothing - `mov eax, ecx; ret 8` - because there
// is no default module in that category to register.
template <int CATEGORY>
class CategoryModuleClassBase<CATEGORY, 0>
{
public:
    CategoryModuleClassBase(const CategoryModuleClass<CATEGORY> &that, bool registerIt);
};

template <int CATEGORY>
inline CategoryModuleClassBase<CATEGORY, 0>::CategoryModuleClassBase(
    const CategoryModuleClass<CATEGORY> &, bool)
{
}

template <int CATEGORY>
class CategoryModuleClass : public CategoryModuleClassBase<CATEGORY, 1>
{
public:
    static const CategoryModuleClass<CATEGORY> *getFirst();

    // Offsets 4, 8 and 0xC, one load each. The three accessors ICF-fold across
    // the nine categories, so nine names share three four-byte bodies.
    const char *getKey() const { return m_key; }
    const char *getName() const { return m_name; }
    const CategoryModuleClass<CATEGORY> *getNext() const { return m_next; }

    static const CategoryModuleClass<CATEGORY> *s_instance;
    static CategoryModuleClass<CATEGORY> *s_head;

protected:
    CategoryModuleClass(bool isDefault, const char *key, const char *name);

    // Protected and NOT virtual - retail spells it IAE - even though the class
    // is polymorphic through v1. All it does is restore the vtable.
    ~CategoryModuleClass();
    virtual void v1() = 0;

    const char *m_key;
    const char *m_name;
    CategoryModuleClass<CATEGORY> *m_next;
};

template <int CATEGORY>
const CategoryModuleClass<CATEGORY> *CategoryModuleClass<CATEGORY>::s_instance;

template <int CATEGORY>
CategoryModuleClass<CATEGORY> *CategoryModuleClass<CATEGORY>::s_head;

template <int CATEGORY>
CategoryModuleClass<CATEGORY>::~CategoryModuleClass()
{
}

template <int CATEGORY>
const CategoryModuleClass<CATEGORY> *CategoryModuleClass<CATEGORY>::getFirst()
{
    return s_head;
}


// The four draw-module info classes carry nothing but their own vtable: both
// constructors install it and the copy constructor ignores its argument.
#define FX_VTABLE_ONLY_INFO(NAME)                                                                      class NAME                                                                                         {                                                                                                  public:                                                                                                NAME();                                                                                            NAME(const NAME &that);                                                                                                                                                                               virtual ~NAME();                                                                                    virtual void v1() = 0;                                                                             virtual const char *GetSnapshotName();                                                         };                                                                                                                                                                                                    NAME::NAME() {}                                                                                    NAME::NAME(const NAME &that) {}                                                                                                                                                                       const char *NAME::GetSnapshotName()                                                                {                                                                                                      return #NAME;                                                                                  }

FX_VTABLE_ONLY_INFO(DefaultDrawModuleInfo)
FX_VTABLE_ONLY_INFO(StreakDrawModuleInfo)
FX_VTABLE_ONLY_INFO(QuadDrawModuleInfo)
FX_VTABLE_ONLY_INFO(ButterflyDrawModuleInfo)

// Out of line, one per class: an in-class body is implicitly inline and MSVC
// then folds it into its callers rather than emitting the COMDAT the ledger
// needs to compare.
DefaultDrawModuleInfo::~DefaultDrawModuleInfo() {}
StreakDrawModuleInfo::~StreakDrawModuleInfo() {}
QuadDrawModuleInfo::~QuadDrawModuleInfo() {}
ButterflyDrawModuleInfo::~ButterflyDrawModuleInfo() {}

// These four carry members this file has not recovered, but their assignments
// are real out-of-line functions their module templates call, so they are
// declared rather than defaulted.
#define FX_DECLARED_ASSIGN_INFO(NAME)                                                                  class NAME                                                                                         {                                                                                                  public:                                                                                                NAME();                                                                                            NAME(const NAME &that);                                                                                                                                                                               NAME &operator=(const NAME &that);                                                                                                                                                                    virtual ~NAME();                                                                                   virtual void v1() = 0;                                                                             virtual const char *GetSnapshotName();                                                         };                                                                                                                                                                                                    NAME::NAME() {}                                                                                    NAME::NAME(const NAME &that) {}                                                                                                                                                                       const char *NAME::GetSnapshotName()                                                                {                                                                                                      return #NAME;                                                                                  }

FX_DECLARED_ASSIGN_INFO(RenderObjectDrawModuleInfo)
FX_DECLARED_ASSIGN_INFO(GpuDrawModuleInfo)
FX_DECLARED_ASSIGN_INFO(LifeEventModuleInfo)
FX_DECLARED_ASSIGN_INFO(TerrainCollisionModuleInfo)

RenderObjectDrawModuleInfo::~RenderObjectDrawModuleInfo() {}
GpuDrawModuleInfo::~GpuDrawModuleInfo() {}
LifeEventModuleInfo::~LifeEventModuleInfo() {}
TerrainCollisionModuleInfo::~TerrainCollisionModuleInfo() {}

// The module class itself. Every instantiation registers into two per-category
// tables: the default slot at 0x00DFDD1C, written only when the first argument
// says so, and a singly linked list whose head is at 0x00DFDD3C - the new class
// takes the old head as its next pointer and becomes the head. Category 8 has a
// list head but no default slot, which is why its constructor is twelve bytes
// shorter than the other eight.
template <int CATEGORY>
CategoryModuleClass<CATEGORY>::CategoryModuleClass(bool isDefault, const char *key,
    const char *name)
    : CategoryModuleClassBase<CATEGORY, 1>(*this, isDefault)
{
    m_key = key;
    m_name = name;
    m_next = s_head;
    s_head = this;
}

template class CategoryModuleClassBase<0, 1>;
template class CategoryModuleClassBase<1, 1>;
template class CategoryModuleClassBase<2, 1>;
template class CategoryModuleClassBase<3, 1>;
template class CategoryModuleClassBase<4, 1>;
template class CategoryModuleClassBase<5, 1>;
template class CategoryModuleClassBase<6, 1>;
template class CategoryModuleClassBase<7, 1>;

template class CategoryModuleClass<0>;
template class CategoryModuleClass<1>;
template class CategoryModuleClass<2>;
template class CategoryModuleClass<3>;
template class CategoryModuleClass<4>;
template class CategoryModuleClass<5>;
template class CategoryModuleClass<6>;
template class CategoryModuleClass<7>;

// Category 8 is the odd one out: it has a list head at 0x00DFDD5C but no
// default slot, so it does not derive from CategoryModuleClassBase at all and
// its constructor ignores the flag it is still handed.
template <>
class CategoryModuleClass<8>
{
public:
    static CategoryModuleClass<8> *s_head;

    static const CategoryModuleClass<8> *getFirst();

    const char *getKey() const { return m_key; }
    const char *getName() const { return m_name; }
    const CategoryModuleClass<8> *getNext() const { return m_next; }

protected:
    CategoryModuleClass(bool isDefault, const char *key, const char *name);

    ~CategoryModuleClass();
    virtual void v1() = 0;

    const char *m_key;
    const char *m_name;
    CategoryModuleClass<8> *m_next;
};

// The second template parameter is not a module count but a has-default flag.
// The event category spells it 0, and the constructor collapses to
// `mov eax, ecx; ret 8`: there is no default module here to register.
template class CategoryModuleClassBase<8, 0>;

const CategoryModuleClass<8> *CategoryModuleClass<8>::getFirst()
{
    return s_head;
}

CategoryModuleClass<8> *CategoryModuleClass<8>::s_head;

CategoryModuleClass<8>::~CategoryModuleClass()
{
}

// A full specialization emits only the members something names, and nothing in
// this file calls the event category's accessors; these force all three out.
typedef const char *(CategoryModuleClass<8>::*EventCategoryStringAccessor)() const;

EventCategoryStringAccessor g_eventCategoryGetKey = &CategoryModuleClass<8>::getKey;
EventCategoryStringAccessor g_eventCategoryGetName = &CategoryModuleClass<8>::getName;

typedef const CategoryModuleClass<8> *(CategoryModuleClass<8>::*EventCategoryNextAccessor)() const;

EventCategoryNextAccessor g_eventCategoryGetNext = &CategoryModuleClass<8>::getNext;

CategoryModuleClass<8>::CategoryModuleClass(bool isDefault, const char *key, const char *name)
{
    m_key = key;
    m_name = name;
    m_next = s_head;
    s_head = this;
}

// The per-category info base. Every module template carries one, which is what
// the secondary vtable names spell out: CategoryModuleTemplate<0>'s second
// table is "6B?$CategoryModuleInfo@$0A@@1@". The class itself is empty and
// polymorphic - all four of its special members are a vtable store and nothing
// else - so ICF folds each one across the nine categories onto one address.
//
// Its destructor is protected and non-virtual (IAE, not MAE), so the vptr store
// it makes is the one a derived destructor inherits rather than dispatches to.
template <int CATEGORY>
class CategoryModuleInfo
{
public:
    CategoryModuleInfo() {}
    CategoryModuleInfo(const CategoryModuleInfo<CATEGORY> &that);
    CategoryModuleInfo<CATEGORY> &operator=(const CategoryModuleInfo<CATEGORY> &that);

    virtual void v1() = 0;

protected:
    ~CategoryModuleInfo();
};

// Written out rather than left to the compiler: the class is abstract, so
// nothing in this file can name the generated copy constructor to force it out.
// Both bodies are what the generated ones would be - the copy restores the
// vtable it just overwrote, the assignment copies nothing at all.
template <int CATEGORY>
CategoryModuleInfo<CATEGORY>::CategoryModuleInfo(const CategoryModuleInfo<CATEGORY> &)
{
}

template <int CATEGORY>
CategoryModuleInfo<CATEGORY> &CategoryModuleInfo<CATEGORY>::operator=(
    const CategoryModuleInfo<CATEGORY> &)
{
    return *this;
}

template <int CATEGORY>
CategoryModuleInfo<CATEGORY>::~CategoryModuleInfo()
{
}

template class CategoryModuleInfo<0>;
template class CategoryModuleInfo<1>;
template class CategoryModuleInfo<2>;
template class CategoryModuleInfo<3>;
template class CategoryModuleInfo<4>;
template class CategoryModuleInfo<5>;
template class CategoryModuleInfo<6>;
template class CategoryModuleInfo<7>;
template class CategoryModuleInfo<8>;

// Seventeen members and no grouping anywhere: the generated assignment copies
// every one of them with its own move rather than blocking any run together,
// which is what separates loose scalars from a sub-object here.
class WindModuleInfo
{
public:
    // Declared only: retail has a real one at 0x003A53C4 and this file has no
    // claim on it yet, but the file-scope wind template instance needs the name
    // to exist before it can force the destructor out.
    WindModuleInfo();
    WindModuleInfo(const WindModuleInfo &that);

    virtual ~WindModuleInfo();
    virtual void v1() = 0;

    float m_unknown04;
    float m_unknown08;
    float m_unknown0C;
    float m_unknown10;
    float m_unknown14;
    float m_unknown18;
    float m_unknown1C;
    float m_unknown20;
    float m_unknown24;
    float m_unknown28;
    float m_unknown2C;
    float m_unknown30;
    float m_unknown34;
    float m_unknown38;
    bool m_unknown3C;
    float m_unknown40;
    float m_unknown44;
    virtual const char *GetSnapshotName();
};

const char *WindModuleInfo::GetSnapshotName()
{
    return "WindModuleInfo";
}

// Defined, not just declared: the wind template destructor at 0x003A6201 folds
// it down to the one vtable store, behind the null-checked +8 adjustment of
// `this` that a base at offset 8 needs.
WindModuleInfo::~WindModuleInfo()
{
}


WindModuleInfo::WindModuleInfo(const WindModuleInfo &that)
{
    m_unknown04 = that.m_unknown04;
    m_unknown08 = that.m_unknown08;
    m_unknown0C = that.m_unknown0C;
    m_unknown10 = that.m_unknown10;
    m_unknown14 = that.m_unknown14;
    m_unknown18 = that.m_unknown18;
    m_unknown1C = that.m_unknown1C;
    m_unknown20 = that.m_unknown20;
    m_unknown24 = that.m_unknown24;
    m_unknown28 = that.m_unknown28;
    m_unknown2C = that.m_unknown2C;
    m_unknown30 = that.m_unknown30;
    m_unknown34 = that.m_unknown34;
    m_unknown38 = that.m_unknown38;
    m_unknown3C = that.m_unknown3C;
    m_unknown40 = that.m_unknown40;
    m_unknown44 = that.m_unknown44;
}

typedef WindModuleInfo &(WindModuleInfo::*WindModuleAssign)(const WindModuleInfo &);

WindModuleAssign g_windModuleAssign = &WindModuleInfo::operator=;

// Category 7 is wind: its module template copy constructor at 0x001F44E4 copies
// the two module bases, then WindModuleInfo at offset 8, then rewrites all
// three vtables. The specialization has to sit here rather than beside the
// others because WindModuleInfo is only a complete type this far down.
template <>
struct CategoryInfo<7>
{
    typedef WindModuleInfo Type;
};

// After the specialization, not with the others: naming CategoryModuleTemplate<7>
// any earlier instantiates CategoryInfo<7> from the primary template.
CategoryModuleTemplate<7> g_categoryModuleTemplate7;

CategoryModuleTemplate<7> *fxCopyWindCategoryModuleTemplate(void *storage,
    const CategoryModuleTemplate<7> &that)
{
    return new (storage) CategoryModuleTemplate<7>(that);
}

// Three more info classes read straight off their generated assignments: a
// movsd run is a three-float group, a lone dword move is a loose float, and a
// byte move is a flag.
class DefaultPhysicsModuleInfo
{
public:
    DefaultPhysicsModuleInfo(const DefaultPhysicsModuleInfo &that);

    virtual ~DefaultPhysicsModuleInfo();
    virtual void v1() = 0;

    FXCoord3D m_unknown04;
    float m_unknown10;
    FXCoord3D m_unknown14;
    bool m_unknown20;
    bool m_unknown21;
    virtual const char *GetSnapshotName();
};

const char *DefaultPhysicsModuleInfo::GetSnapshotName()
{
    return "DefaultPhysicsModuleInfo";
}


// 0x003A7736 stays unclaimed: identical to retail except that MSVC 7.1 spreads
// the esi and edi saves through the scalar copies where retail groups them.
DefaultPhysicsModuleInfo::DefaultPhysicsModuleInfo(const DefaultPhysicsModuleInfo &that)
{
    m_unknown04.x = that.m_unknown04.x;
    m_unknown04.y = that.m_unknown04.y;
    m_unknown04.z = that.m_unknown04.z;
    m_unknown10 = that.m_unknown10;
    m_unknown14 = that.m_unknown14;
    m_unknown20 = that.m_unknown20;
    m_unknown21 = that.m_unknown21;
}

class LightningDrawModuleInfo
{
public:
    LightningDrawModuleInfo(const LightningDrawModuleInfo &that);

    virtual ~LightningDrawModuleInfo();
    virtual void v1() = 0;

    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
    FXCoord3D m_unknown1C;
    float m_unknown28;
    bool m_unknown2C;
    virtual const char *GetSnapshotName();
};

const char *LightningDrawModuleInfo::GetSnapshotName()
{
    return "LightningDrawModuleInfo";
}


LightningDrawModuleInfo::LightningDrawModuleInfo(const LightningDrawModuleInfo &that)
{
    m_unknown04 = that.m_unknown04;
    m_unknown10 = that.m_unknown10;
    m_unknown1C = that.m_unknown1C;
    m_unknown28 = that.m_unknown28;
    m_unknown2C = that.m_unknown2C;
}

class OrthoEmissionVelocityInfo
{
public:
    virtual ~OrthoEmissionVelocityInfo();
    virtual void v1() = 0;

    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
    FXCoord3D m_unknown1C;
};

typedef DefaultPhysicsModuleInfo &(DefaultPhysicsModuleInfo::*DefaultPhysicsAssign)(
    const DefaultPhysicsModuleInfo &);
typedef LightningDrawModuleInfo &(LightningDrawModuleInfo::*LightningDrawAssign)(
    const LightningDrawModuleInfo &);
typedef OrthoEmissionVelocityInfo &(OrthoEmissionVelocityInfo::*OrthoEmissionVelocityAssign)(
    const OrthoEmissionVelocityInfo &);

DefaultPhysicsAssign g_defaultPhysicsAssign = &DefaultPhysicsModuleInfo::operator=;
LightningDrawAssign g_lightningDrawAssign = &LightningDrawModuleInfo::operator=;
OrthoEmissionVelocityAssign g_orthoEmissionVelocityAssign = &OrthoEmissionVelocityInfo::operator=;

class TerrainFireEmissionInfo : public EmissionVolumeInfo
{
public:
    virtual ~TerrainFireEmissionInfo();

    FXCoord3D m_unknown08;
    FXCoord3D m_unknown14;
    FXCoord3D m_unknown20;
    float m_unknown2C;
};

class LightningEmissionInfo : public EmissionVolumeInfo
{
public:
    LightningEmissionInfo(const LightningEmissionInfo &that);

    virtual ~LightningEmissionInfo();

    FXCoord3D m_unknown08;
    FXCoord3D m_unknown14;
    FXCoord3D m_unknown20;
    FXCoord3D m_unknown2C;
    FXCoord3D m_unknown38;
    FXCoord3D m_unknown44;
    FXCoord3D m_unknown50;
    FXCoord3D m_unknown5C;
    FXCoord3D m_unknown68;
    FXCoord3D m_unknown74;
    FXCoord3D m_unknown80;
};

// 0x003A6AF5 stays unclaimed. The generated copy constructor expands the first
// two groups one float at a time and blocks the remaining nine, which this
// reproduces; the only difference is where the edi save lands - MSVC 7.1 puts it
// one scalar earlier than retail, the same scheduling gap that leaves
// DefaultPhysicsModuleInfo's copy constructor unclaimed.
LightningEmissionInfo::LightningEmissionInfo(const LightningEmissionInfo &that)
    : EmissionVolumeInfo(that)
{
    m_unknown08.x = that.m_unknown08.x;
    m_unknown08.y = that.m_unknown08.y;
    m_unknown08.z = that.m_unknown08.z;
    m_unknown14.x = that.m_unknown14.x;
    m_unknown14.y = that.m_unknown14.y;
    m_unknown14.z = that.m_unknown14.z;
    m_unknown20 = that.m_unknown20;
    m_unknown2C = that.m_unknown2C;
    m_unknown38 = that.m_unknown38;
    m_unknown44 = that.m_unknown44;
    m_unknown50 = that.m_unknown50;
    m_unknown5C = that.m_unknown5C;
    m_unknown68 = that.m_unknown68;
    m_unknown74 = that.m_unknown74;
    m_unknown80 = that.m_unknown80;
}

class DefaultUpdateModuleInfo
{
public:
    DefaultUpdateModuleInfo(const DefaultUpdateModuleInfo &that);

    virtual ~DefaultUpdateModuleInfo();
    virtual void v1() = 0;

    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
    FXCoord3D m_unknown1C;
    FXCoord3D m_unknown28;
    FXCoord3D m_unknown34;
    float m_unknown40;
    FXCoord3D m_unknown44;
    FXCoord3D m_unknown50;
    FXCoord3D m_unknown5C;
    virtual const char *GetSnapshotName();
};

const char *DefaultUpdateModuleInfo::GetSnapshotName()
{
    return "DefaultUpdateModuleInfo";
}


DefaultUpdateModuleInfo::DefaultUpdateModuleInfo(const DefaultUpdateModuleInfo &that)
{
    m_unknown04 = that.m_unknown04;
    m_unknown10 = that.m_unknown10;
    m_unknown1C = that.m_unknown1C;
    m_unknown28 = that.m_unknown28;
    m_unknown34 = that.m_unknown34;
    m_unknown40 = that.m_unknown40;
    m_unknown44 = that.m_unknown44;
    m_unknown50 = that.m_unknown50;
    m_unknown5C = that.m_unknown5C;
}

typedef TerrainFireEmissionInfo &(TerrainFireEmissionInfo::*TerrainFireEmissionAssign)(
    const TerrainFireEmissionInfo &);
typedef LightningEmissionInfo &(LightningEmissionInfo::*LightningEmissionAssign)(
    const LightningEmissionInfo &);
typedef DefaultUpdateModuleInfo &(DefaultUpdateModuleInfo::*DefaultUpdateAssign)(
    const DefaultUpdateModuleInfo &);

TerrainFireEmissionAssign g_terrainFireEmissionAssign = &TerrainFireEmissionInfo::operator=;
LightningEmissionAssign g_lightningEmissionAssign = &LightningEmissionInfo::operator=;
DefaultUpdateAssign g_defaultUpdateAssign = &DefaultUpdateModuleInfo::operator=;

class RenderObjectUpdateModuleInfo
{
public:
    RenderObjectUpdateModuleInfo(const RenderObjectUpdateModuleInfo &that);

    virtual ~RenderObjectUpdateModuleInfo();
    virtual void v1() = 0;

    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
    FXCoord3D m_unknown1C;
    FXCoord3D m_unknown28;
    FXCoord3D m_unknown34;
    FXCoord3D m_unknown40;
    FXCoord3D m_unknown4C;
    FXCoord3D m_unknown58;
    FXCoord3D m_unknown64;
    FXCoord3D m_unknown70;
    FXCoord3D m_unknown7C;
    FXCoord3D m_unknown88;
    float m_unknown94;
    virtual const char *GetSnapshotName();
};

const char *RenderObjectUpdateModuleInfo::GetSnapshotName()
{
    return "RenderObjectUpdateModuleInfo";
}


// An eight-element array of a group-plus-scalar pair: the generated assignment
// walks it one element at a time because the element type has an assignment of
// its own, while the generated copy constructor blocks all 128 bytes at once.
struct FXKeyframe
{
    FXCoord3D m_value;
    unsigned int m_frame;
};

class DefaultAlphaModuleInfo
{
public:
    virtual ~DefaultAlphaModuleInfo();
    virtual void v1();

    FXKeyframe m_keys[8];
    virtual const char *GetSnapshotName();
};

const char *DefaultAlphaModuleInfo::GetSnapshotName()
{
    return "DefaultAlphaModuleInfo";
}


// The copy constructor has to be the GENERATED one - it block-copies all 128
// bytes with a single rep movsd, where a hand-written per-element loop walks the
// array the way the assignment does. Nothing in this unit would emit it, so a
// placement-new helper forces it out.

DefaultAlphaModuleInfo *fxCopyDefaultAlphaModuleInfo(void *storage,
    const DefaultAlphaModuleInfo &that)
{
    return new (storage) DefaultAlphaModuleInfo(that);
}

class DefaultColorModuleInfo
{
public:
    virtual ~DefaultColorModuleInfo();
    virtual void v1();

    FXKeyframe m_keys[8];
    FXCoord3D m_unknown84;
    virtual const char *GetSnapshotName();
};

const char *DefaultColorModuleInfo::GetSnapshotName()
{
    return "DefaultColorModuleInfo";
}


typedef RenderObjectUpdateModuleInfo &(
    RenderObjectUpdateModuleInfo::*RenderObjectUpdateAssign)(const RenderObjectUpdateModuleInfo &);
typedef DefaultAlphaModuleInfo &(DefaultAlphaModuleInfo::*DefaultAlphaAssign)(
    const DefaultAlphaModuleInfo &);
typedef DefaultColorModuleInfo &(DefaultColorModuleInfo::*DefaultColorAssign)(
    const DefaultColorModuleInfo &);

RenderObjectUpdateAssign g_renderObjectUpdateAssign = &RenderObjectUpdateModuleInfo::operator=;
DefaultAlphaAssign g_defaultAlphaAssign = &DefaultAlphaModuleInfo::operator=;
DefaultColorAssign g_defaultColorAssign = &DefaultColorModuleInfo::operator=;

class SphericalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    FXCoord3D m_unknown04;
};

DefaultColorModuleInfo *fxCopyDefaultColorModuleInfo(void *storage,
    const DefaultColorModuleInfo &that)
{
    return new (storage) DefaultColorModuleInfo(that);
}

RenderObjectUpdateModuleInfo::RenderObjectUpdateModuleInfo(
    const RenderObjectUpdateModuleInfo &that)
{
    m_unknown04 = that.m_unknown04;
    m_unknown10 = that.m_unknown10;
    m_unknown1C = that.m_unknown1C;
    m_unknown28 = that.m_unknown28;
    m_unknown34 = that.m_unknown34;
    m_unknown40 = that.m_unknown40;
    m_unknown4C = that.m_unknown4C;
    m_unknown58 = that.m_unknown58;
    m_unknown64 = that.m_unknown64;
    m_unknown70 = that.m_unknown70;
    m_unknown7C = that.m_unknown7C;
    m_unknown88 = that.m_unknown88;
    m_unknown94 = that.m_unknown94;
}

typedef SphericalEmissionVelocityInfo &(
    SphericalEmissionVelocityInfo::*SphericalEmissionVelocityAssign)(
    const SphericalEmissionVelocityInfo &);

SphericalEmissionVelocityAssign g_sphericalEmissionVelocityAssign =
    &SphericalEmissionVelocityInfo::operator=;

// The concrete module templates are the CategoryModuleTemplate shape with a
// real info class as the third base: the primary ModuleTemplate vtable at 0, the
// secondary at 4, and the info's own vtable and members from 8 on. Each
// constructor stores the secondary table twice, before and after the primary,
// exactly as the category templates do.

class PointEmissionVolumeModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public EmissionVolumeInfo
{
public:
    virtual void v1();
};

PointEmissionVolumeModuleTemplate g_pointEmissionVolumeModuleTemplate;

class SphereEmissionVolumeModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public SphereEmissionVolumeInfo
{
public:
    virtual void v1();
};

SphereEmissionVolumeModuleTemplate g_sphereEmissionVolumeModuleTemplate;

class BoxEmissionVolumeModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public BoxEmissionVolumeInfo
{
public:
    BoxEmissionVolumeModuleTemplate();
    BoxEmissionVolumeModuleTemplate(const BoxEmissionVolumeModuleTemplate &that);

    virtual void v1();
};

// The copy constructor stays a declaration: the wrapper calls it out of line.
BoxEmissionVolumeModuleTemplate::BoxEmissionVolumeModuleTemplate()
{
}


BoxEmissionVolumeModuleTemplate g_boxEmissionVolumeModuleTemplate;

class LineEmissionVolumeModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public LineEmissionVolumeInfo
{
public:
    LineEmissionVolumeModuleTemplate();
    LineEmissionVolumeModuleTemplate(const LineEmissionVolumeModuleTemplate &that);

    virtual void v1();
};

// The copy constructor stays a declaration: the wrapper calls it out of line.
LineEmissionVolumeModuleTemplate::LineEmissionVolumeModuleTemplate()
{
}


LineEmissionVolumeModuleTemplate g_lineEmissionVolumeModuleTemplate;

class CylinderEmissionVolumeModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public CylinderEmissionVolumeInfo
{
public:
    CylinderEmissionVolumeModuleTemplate();
    CylinderEmissionVolumeModuleTemplate(const CylinderEmissionVolumeModuleTemplate &that);

    virtual void v1();
};

// The copy constructor stays a declaration: the wrapper calls it out of line.
CylinderEmissionVolumeModuleTemplate::CylinderEmissionVolumeModuleTemplate()
{
}


CylinderEmissionVolumeModuleTemplate g_cylinderEmissionVolumeModuleTemplate;

class SphericalEmissionVelocityModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public SphericalEmissionVelocityInfo
{
public:
    virtual void v1();
};

SphericalEmissionVelocityModuleTemplate g_sphericalEmissionVelocityModuleTemplate;

typedef PointEmissionVolumeModuleTemplate &(PointEmissionVolumeModuleTemplate::*PointEmissionVolumeModuleTemplateAssign)(const PointEmissionVolumeModuleTemplate &);

PointEmissionVolumeModuleTemplateAssign g_pointEmissionVolumeModuleTemplateAssign = &PointEmissionVolumeModuleTemplate::operator=;

typedef SphereEmissionVolumeModuleTemplate &(SphereEmissionVolumeModuleTemplate::*SphereEmissionVolumeModuleTemplateAssign)(const SphereEmissionVolumeModuleTemplate &);

SphereEmissionVolumeModuleTemplateAssign g_sphereEmissionVolumeModuleTemplateAssign = &SphereEmissionVolumeModuleTemplate::operator=;

typedef BoxEmissionVolumeModuleTemplate &(BoxEmissionVolumeModuleTemplate::*BoxEmissionVolumeModuleTemplateAssign)(const BoxEmissionVolumeModuleTemplate &);

BoxEmissionVolumeModuleTemplateAssign g_boxEmissionVolumeModuleTemplateAssign = &BoxEmissionVolumeModuleTemplate::operator=;

typedef LineEmissionVolumeModuleTemplate &(LineEmissionVolumeModuleTemplate::*LineEmissionVolumeModuleTemplateAssign)(const LineEmissionVolumeModuleTemplate &);

LineEmissionVolumeModuleTemplateAssign g_lineEmissionVolumeModuleTemplateAssign = &LineEmissionVolumeModuleTemplate::operator=;

typedef CylinderEmissionVolumeModuleTemplate &(CylinderEmissionVolumeModuleTemplate::*CylinderEmissionVolumeModuleTemplateAssign)(const CylinderEmissionVolumeModuleTemplate &);

CylinderEmissionVolumeModuleTemplateAssign g_cylinderEmissionVolumeModuleTemplateAssign = &CylinderEmissionVolumeModuleTemplate::operator=;

typedef SphericalEmissionVelocityModuleTemplate &(SphericalEmissionVelocityModuleTemplate::*SphericalEmissionVelocityModuleTemplateAssign)(const SphericalEmissionVelocityModuleTemplate &);

SphericalEmissionVelocityModuleTemplateAssign g_sphericalEmissionVelocityModuleTemplateAssign = &SphericalEmissionVelocityModuleTemplate::operator=;

// The module tag: a category, the INI key and display name it registers under,
// the module and template classes it builds, and the default module for its
// category. Only the tag's identity reaches the decorated names, so the classes
// it names need declaring but not defining, and ConcreteModuleTemplate derives
// from the template class the tag carries - which is what makes its generated
// assignment one forwarding call.
template <int CATEGORY>
class DefaultParticleModule;

template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE,
    class TEMPLATE, class DEFAULT>
class ModuleTag
{
public:
    typedef TEMPLATE TemplateType;
};

template <class TAG>
class ConcreteModuleTemplate : public TAG::TemplateType
{
public:
    ConcreteModuleTemplate();
    __declspec(noinline) ConcreteModuleTemplate(const ConcreteModuleTemplate<TAG> &that);

    virtual void v1();
    virtual typename TAG::TemplateType *clone() const;
};

template <class TAG>
ConcreteModuleTemplate<TAG>::ConcreteModuleTemplate()
{
}

template <class TAG>
ConcreteModuleTemplate<TAG>::ConcreteModuleTemplate(const ConcreteModuleTemplate<TAG> &that)
    : TAG::TemplateType(that)
{
}

template <class TAG>
void ConcreteModuleTemplate<TAG>::v1()
{
}

// clone is one operator new and one call to the copy constructor. Keeping that
// call is what the __declspec(noinline) above is for: retail does not inline the
// copy constructor into clone, and MSVC 7.1 does at every optimization and
// inline setting tried - /Ob1 breaks eleven other bodies in this unit and /EHsc
// drags an unwind frame into clone that retail has not got. The marker stands in
// for whatever kept retail's compiler out of it.
template <class TAG>
typename TAG::TemplateType *ConcreteModuleTemplate<TAG>::clone() const
{
    return new ConcreteModuleTemplate<TAG>(*this);
}

extern const char *const RENDEROBJECT_DRAW_MODULE_KEY;
extern const char *const RENDEROBJECT_DRAW_MODULE_NAME;

class RenderObjectDrawModule;

class RenderObjectDrawModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public RenderObjectDrawModuleInfo
{
};

typedef ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6> > >
    RenderObjectDrawModuleConcrete;
typedef RenderObjectDrawModuleConcrete &(RenderObjectDrawModuleConcrete::*RenderObjectDrawModuleConcreteAssign)(const RenderObjectDrawModuleConcrete &);

RenderObjectDrawModuleConcreteAssign g_renderObjectDrawModuleConcreteAssign = &RenderObjectDrawModuleConcrete::operator=;

extern const char *const LIGHTNING_DRAW_MODULE_KEY;
extern const char *const LIGHTNING_DRAW_MODULE_NAME;

class LightningDrawModule;

class LightningDrawModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public LightningDrawModuleInfo
{
public:
    LightningDrawModuleTemplate();
    LightningDrawModuleTemplate(const LightningDrawModuleTemplate &that);
};

typedef ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6> > >
    LightningDrawModuleConcrete;
typedef LightningDrawModuleConcrete &(LightningDrawModuleConcrete::*LightningDrawModuleConcreteAssign)(const LightningDrawModuleConcrete &);

LightningDrawModuleConcreteAssign g_lightningDrawModuleConcreteAssign = &LightningDrawModuleConcrete::operator=;

extern const char *const GPU_DRAW_MODULE_KEY;
extern const char *const GPU_DRAW_MODULE_NAME;

class GpuDrawModule;

class GpuDrawModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public GpuDrawModuleInfo
{
};

typedef ConcreteModuleTemplate<ModuleTag<6, GPU_DRAW_MODULE_KEY, GPU_DRAW_MODULE_NAME, GpuDrawModule, GpuDrawModuleTemplate, DefaultParticleModule<6> > >
    GpuDrawModuleConcrete;
typedef GpuDrawModuleConcrete &(GpuDrawModuleConcrete::*GpuDrawModuleConcreteAssign)(const GpuDrawModuleConcrete &);

GpuDrawModuleConcreteAssign g_gpuDrawModuleConcreteAssign = &GpuDrawModuleConcrete::operator=;

extern const char *const LINE_EMISSION_VOLUME_MODULE_KEY;
extern const char *const LINE_EMISSION_VOLUME_MODULE_NAME;

class LineEmissionVolumeModule;

typedef ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5> > >
    LineEmissionVolumeModuleConcrete;
typedef LineEmissionVolumeModuleConcrete &(LineEmissionVolumeModuleConcrete::*LineEmissionVolumeModuleConcreteAssign)(const LineEmissionVolumeModuleConcrete &);

LineEmissionVolumeModuleConcreteAssign g_lineEmissionVolumeModuleConcreteAssign = &LineEmissionVolumeModuleConcrete::operator=;

LineEmissionVolumeModuleConcrete g_lineEmissionVolumeModuleConcrete;

extern const char *const BOX_EMISSION_VOLUME_MODULE_KEY;
extern const char *const BOX_EMISSION_VOLUME_MODULE_NAME;

class BoxEmissionVolumeModule;

typedef ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5> > >
    BoxEmissionVolumeModuleConcrete;
typedef BoxEmissionVolumeModuleConcrete &(BoxEmissionVolumeModuleConcrete::*BoxEmissionVolumeModuleConcreteAssign)(const BoxEmissionVolumeModuleConcrete &);

BoxEmissionVolumeModuleConcreteAssign g_boxEmissionVolumeModuleConcreteAssign = &BoxEmissionVolumeModuleConcrete::operator=;

BoxEmissionVolumeModuleConcrete g_boxEmissionVolumeModuleConcrete;

extern const char *const CYLINDER_EMISSION_VOLUME_MODULE_KEY;
extern const char *const CYLINDER_EMISSION_VOLUME_MODULE_NAME;

class CylinderEmissionVolumeModule;

typedef ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5> > >
    CylinderEmissionVolumeModuleConcrete;
typedef CylinderEmissionVolumeModuleConcrete &(CylinderEmissionVolumeModuleConcrete::*CylinderEmissionVolumeModuleConcreteAssign)(const CylinderEmissionVolumeModuleConcrete &);

CylinderEmissionVolumeModuleConcreteAssign g_cylinderEmissionVolumeModuleConcreteAssign = &CylinderEmissionVolumeModuleConcrete::operator=;

CylinderEmissionVolumeModuleConcrete g_cylinderEmissionVolumeModuleConcrete;

extern const char *const LIGHTNING_EMISSION_MODULE_KEY;
extern const char *const LIGHTNING_EMISSION_MODULE_NAME;

class LightningEmissionModule;

class LightningEmissionModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public LightningEmissionInfo
{
public:
    LightningEmissionModuleTemplate();
    LightningEmissionModuleTemplate(const LightningEmissionModuleTemplate &that);
};

typedef ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5> > >
    LightningEmissionModuleConcrete;
typedef LightningEmissionModuleConcrete &(LightningEmissionModuleConcrete::*LightningEmissionModuleConcreteAssign)(const LightningEmissionModuleConcrete &);

LightningEmissionModuleConcreteAssign g_lightningEmissionModuleConcreteAssign = &LightningEmissionModuleConcrete::operator=;

extern const char *const TERRAIN_FIRE_EMISSION_MODULE_KEY;
extern const char *const TERRAIN_FIRE_EMISSION_MODULE_NAME;

class TerrainFireEmissionModule;

class TerrainFireEmissionModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public TerrainFireEmissionInfo
{
public:
    TerrainFireEmissionModuleTemplate();
    TerrainFireEmissionModuleTemplate(const TerrainFireEmissionModuleTemplate &that);
};

typedef ConcreteModuleTemplate<ModuleTag<5, TERRAIN_FIRE_EMISSION_MODULE_KEY, TERRAIN_FIRE_EMISSION_MODULE_NAME, TerrainFireEmissionModule, TerrainFireEmissionModuleTemplate, DefaultParticleModule<5> > >
    TerrainFireEmissionModuleConcrete;
typedef TerrainFireEmissionModuleConcrete &(TerrainFireEmissionModuleConcrete::*TerrainFireEmissionModuleConcreteAssign)(const TerrainFireEmissionModuleConcrete &);

TerrainFireEmissionModuleConcreteAssign g_terrainFireEmissionModuleConcreteAssign = &TerrainFireEmissionModuleConcrete::operator=;

extern const char *const LIFE_EVENT_MODULE_KEY;
extern const char *const LIFE_EVENT_MODULE_NAME;

class LifeEventModule;
class ParticleLifeEventModule;

// Four bases, not three: retail copies a word at offset 8 before forwarding to
// the info's assignment at 0x0C, and the wrapper stores its third vtable at
// [esi+0x0C] rather than [esi+0x08]. So the two EventModuleInfo flags are at 8
// and the module's own info starts at 0x0C - but MSVC 7.1 hoists the polymorphic
// base ahead of the flags and lands them the other way round, which is what
// leaves 0x003A7A7F and 0x003A81E2 unclaimed. Whatever keeps retail's order is
// the missing piece.
class LifeEventModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public EventModuleInfo,
           public LifeEventModuleInfo
{
};

typedef ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule> >
    LifeEventModuleConcrete;
typedef LifeEventModuleConcrete &(LifeEventModuleConcrete::*LifeEventModuleConcreteAssign)(const LifeEventModuleConcrete &);

LifeEventModuleConcreteAssign g_lifeEventModuleConcreteAssign = &LifeEventModuleConcrete::operator=;

extern const char *const RENDEROBJECT_UPDATE_MODULE_KEY;
extern const char *const RENDEROBJECT_UPDATE_MODULE_NAME;

class RenderObjectUpdateModule;
class RenderObjectParticleUpdateModule;

class RenderObjectUpdateModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public RenderObjectUpdateModuleInfo
{
public:
    RenderObjectUpdateModuleTemplate();
    RenderObjectUpdateModuleTemplate(const RenderObjectUpdateModuleTemplate &that);
};

typedef ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule> >
    RenderObjectUpdateModuleConcrete;
typedef RenderObjectUpdateModuleConcrete &(RenderObjectUpdateModuleConcrete::*RenderObjectUpdateModuleConcreteAssign)(const RenderObjectUpdateModuleConcrete &);

RenderObjectUpdateModuleConcreteAssign g_renderObjectUpdateModuleConcreteAssign = &RenderObjectUpdateModuleConcrete::operator=;

extern const char *const TERRAIN_COLLISION_MODULE_KEY;
extern const char *const TERRAIN_COLLISION_MODULE_NAME;

class TerrainCollisionModule;
class ParticleTerrainCollisionModule;

// Four bases, not three: retail copies a word at offset 8 before forwarding to
// the info's assignment at 0x0C, and the wrapper stores its third vtable at
// [esi+0x0C] rather than [esi+0x08]. So the two EventModuleInfo flags are at 8
// and the module's own info starts at 0x0C - but MSVC 7.1 hoists the polymorphic
// base ahead of the flags and lands them the other way round, which is what
// leaves 0x003A7A7F and 0x003A81E2 unclaimed. Whatever keeps retail's order is
// the missing piece.
class TerrainCollisionModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public EventModuleInfo,
           public TerrainCollisionModuleInfo
{
};

typedef ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule> >
    TerrainCollisionModuleConcrete;
typedef TerrainCollisionModuleConcrete &(TerrainCollisionModuleConcrete::*TerrainCollisionModuleConcreteAssign)(const TerrainCollisionModuleConcrete &);

TerrainCollisionModuleConcreteAssign g_terrainCollisionModuleConcreteAssign = &TerrainCollisionModuleConcrete::operator=;

// The default modules use a tag with nothing but a category in it.
// The default modules' info class is per category and not recovered yet; what
// matters for the wrappers is that it carries a vtable of its own, which is what
// keeps the template's three tables at 0, 4 and 8.
class DefaultModuleInfoBase
{
public:
    virtual ~DefaultModuleInfoBase() {}
    virtual void v1() = 0;
};

template <int CATEGORY>
class DefaultModuleTemplate : public ModuleTemplate, public SecondaryModuleBase,
                              public DefaultModuleInfoBase
{
};

// Each category's default template is over that category's own info class, and
// its generated assignment forwards to that info's - which is what identifies
// the four: colour for category 0, alpha for 1, update for 2, physics for 3.
#define FX_DEFAULT_TEMPLATE_SPEC(CATEGORY, INFO)                                                       template <>                                                                                        class DefaultModuleTemplate<CATEGORY> : public ModuleTemplate, public SecondaryModuleBase,                                                 public INFO                                                {                                                                                                  };                                                                                                                                                                                                    typedef DefaultModuleTemplate<CATEGORY> &(DefaultModuleTemplate<CATEGORY>::*                           DefaultModuleTemplate##CATEGORY##Assign)(const DefaultModuleTemplate<CATEGORY> &);                                                                                                                DefaultModuleTemplate##CATEGORY##Assign g_defaultModuleTemplate##CATEGORY##Assign =                    &DefaultModuleTemplate<CATEGORY>::operator=;

FX_DEFAULT_TEMPLATE_SPEC(0, DefaultColorModuleInfo)
FX_DEFAULT_TEMPLATE_SPEC(1, DefaultAlphaModuleInfo)
FX_DEFAULT_TEMPLATE_SPEC(2, DefaultUpdateModuleInfo)
FX_DEFAULT_TEMPLATE_SPEC(3, DefaultPhysicsModuleInfo)

template <int CATEGORY>
class DefaultModuleTag
{
public:
    typedef DefaultModuleTemplate<CATEGORY> TemplateType;
};

typedef ConcreteModuleTemplate<DefaultModuleTag<1> > DefaultConcrete1;
typedef DefaultConcrete1 &(DefaultConcrete1::*DefaultConcrete1Assign)(const DefaultConcrete1 &);

DefaultConcrete1Assign g_defaultConcrete1Assign = &DefaultConcrete1::operator=;

typedef ConcreteModuleTemplate<DefaultModuleTag<0> > DefaultConcrete0;
typedef DefaultConcrete0 &(DefaultConcrete0::*DefaultConcrete0Assign)(const DefaultConcrete0 &);

DefaultConcrete0Assign g_defaultConcrete0Assign = &DefaultConcrete0::operator=;

typedef ConcreteModuleTemplate<DefaultModuleTag<3> > DefaultConcrete3;
typedef DefaultConcrete3 &(DefaultConcrete3::*DefaultConcrete3Assign)(const DefaultConcrete3 &);

DefaultConcrete3Assign g_defaultConcrete3Assign = &DefaultConcrete3::operator=;

typedef ConcreteModuleTemplate<DefaultModuleTag<2> > DefaultConcrete2;
typedef DefaultConcrete2 &(DefaultConcrete2::*DefaultConcrete2Assign)(const DefaultConcrete2 &);

DefaultConcrete2Assign g_defaultConcrete2Assign = &DefaultConcrete2::operator=;

// One tag is a plain struct rather than an instantiation.
class OrthoEmissionVelocityModuleTemplate;

struct OrthoEmissionVelocityModuleTag
{
    typedef OrthoEmissionVelocityModuleTemplate TemplateType;
};

class OrthoEmissionVelocityModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public OrthoEmissionVelocityInfo
{
public:
    OrthoEmissionVelocityModuleTemplate();
    OrthoEmissionVelocityModuleTemplate(const OrthoEmissionVelocityModuleTemplate &that);
};

typedef ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> OrthoEmissionVelocityConcrete;
typedef OrthoEmissionVelocityConcrete &(
    OrthoEmissionVelocityConcrete::*OrthoEmissionVelocityConcreteAssign)(
    const OrthoEmissionVelocityConcrete &);

OrthoEmissionVelocityConcreteAssign g_orthoEmissionVelocityConcreteAssign =
    &OrthoEmissionVelocityConcrete::operator=;

// The concrete templates that carry a clone. ConcreteModuleTemplate overrides
// virtuals of all three of its base's tables, so its constructors install three
// vtables of their own after the base constructor runs, and clone is
// operator new followed by its own copy constructor.
template <class TAG>
class ConcreteModuleTemplateWithClone;

extern const char *const STREAK_DRAW_MODULE_KEY;
extern const char *const STREAK_DRAW_MODULE_NAME;

class StreakDrawModule;

class StreakDrawModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public StreakDrawModuleInfo
{
public:
    StreakDrawModuleTemplate();
    StreakDrawModuleTemplate(const StreakDrawModuleTemplate &that);
};

typedef ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6> > >
    StreakDrawModuleConcrete;

StreakDrawModuleConcrete g_streakDrawModuleConcrete;

extern const char *const QUAD_DRAW_MODULE_KEY;
extern const char *const QUAD_DRAW_MODULE_NAME;

class QuadDrawModule;

class QuadDrawModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public QuadDrawModuleInfo
{
public:
    QuadDrawModuleTemplate();
    QuadDrawModuleTemplate(const QuadDrawModuleTemplate &that);
};

typedef ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6> > >
    QuadDrawModuleConcrete;

QuadDrawModuleConcrete g_quadDrawModuleConcrete;

extern const char *const BUTTERFLY_DRAW_MODULE_KEY;
extern const char *const BUTTERFLY_DRAW_MODULE_NAME;

class ButterflyDrawModule;

class ButterflyDrawModuleTemplate : public ModuleTemplate, public SecondaryModuleBase, public ButterflyDrawModuleInfo
{
public:
    ButterflyDrawModuleTemplate();
    ButterflyDrawModuleTemplate(const ButterflyDrawModuleTemplate &that);
};

typedef ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6> > >
    ButterflyDrawModuleConcrete;

ButterflyDrawModuleConcrete g_butterflyDrawModuleConcrete;

// The module templates' own generated assignments. Each adjusts the source by 8
// with the null-checked neg/sbb/and idiom and hands it to the info base's
// assignment, which is what a base at offset 8 looks like from the outside.

typedef RenderObjectDrawModuleTemplate &(RenderObjectDrawModuleTemplate::*RenderObjectDrawModuleTemplateAssign)(const RenderObjectDrawModuleTemplate &);

RenderObjectDrawModuleTemplateAssign g_renderObjectDrawModuleTemplateAssign = &RenderObjectDrawModuleTemplate::operator=;

typedef LightningDrawModuleTemplate &(LightningDrawModuleTemplate::*LightningDrawModuleTemplateAssign)(const LightningDrawModuleTemplate &);

LightningDrawModuleTemplateAssign g_lightningDrawModuleTemplateAssign = &LightningDrawModuleTemplate::operator=;

typedef GpuDrawModuleTemplate &(GpuDrawModuleTemplate::*GpuDrawModuleTemplateAssign)(const GpuDrawModuleTemplate &);

GpuDrawModuleTemplateAssign g_gpuDrawModuleTemplateAssign = &GpuDrawModuleTemplate::operator=;

typedef LightningEmissionModuleTemplate &(LightningEmissionModuleTemplate::*LightningEmissionModuleTemplateAssign)(const LightningEmissionModuleTemplate &);

LightningEmissionModuleTemplateAssign g_lightningEmissionModuleTemplateAssign = &LightningEmissionModuleTemplate::operator=;

typedef TerrainFireEmissionModuleTemplate &(TerrainFireEmissionModuleTemplate::*TerrainFireEmissionModuleTemplateAssign)(const TerrainFireEmissionModuleTemplate &);

TerrainFireEmissionModuleTemplateAssign g_terrainFireEmissionModuleTemplateAssign = &TerrainFireEmissionModuleTemplate::operator=;

typedef LifeEventModuleTemplate &(LifeEventModuleTemplate::*LifeEventModuleTemplateAssign)(const LifeEventModuleTemplate &);

LifeEventModuleTemplateAssign g_lifeEventModuleTemplateAssign = &LifeEventModuleTemplate::operator=;

typedef RenderObjectUpdateModuleTemplate &(RenderObjectUpdateModuleTemplate::*RenderObjectUpdateModuleTemplateAssign)(const RenderObjectUpdateModuleTemplate &);

RenderObjectUpdateModuleTemplateAssign g_renderObjectUpdateModuleTemplateAssign = &RenderObjectUpdateModuleTemplate::operator=;

typedef TerrainCollisionModuleTemplate &(TerrainCollisionModuleTemplate::*TerrainCollisionModuleTemplateAssign)(const TerrainCollisionModuleTemplate &);

TerrainCollisionModuleTemplateAssign g_terrainCollisionModuleTemplateAssign = &TerrainCollisionModuleTemplate::operator=;

typedef OrthoEmissionVelocityModuleTemplate &(OrthoEmissionVelocityModuleTemplate::*OrthoEmissionVelocityModuleTemplateAssign)(const OrthoEmissionVelocityModuleTemplate &);

OrthoEmissionVelocityModuleTemplateAssign g_orthoEmissionVelocityModuleTemplateAssign = &OrthoEmissionVelocityModuleTemplate::operator=;


// The registry base's assignment folds onto the same address as every other
// empty one: no members, no vtable, nothing to copy. Nothing calls them, so a
// pointer-to-member each is what forces them out.

typedef CategoryModuleClassBase<0, 1> &(CategoryModuleClassBase<0, 1>::*CategoryModuleClassBaseAssign0)(const CategoryModuleClassBase<0, 1> &);

CategoryModuleClassBaseAssign0 g_categoryModuleClassBaseAssign0 = &CategoryModuleClassBase<0, 1>::operator=;

typedef CategoryModuleClassBase<1, 1> &(CategoryModuleClassBase<1, 1>::*CategoryModuleClassBaseAssign1)(const CategoryModuleClassBase<1, 1> &);

CategoryModuleClassBaseAssign1 g_categoryModuleClassBaseAssign1 = &CategoryModuleClassBase<1, 1>::operator=;

typedef CategoryModuleClassBase<2, 1> &(CategoryModuleClassBase<2, 1>::*CategoryModuleClassBaseAssign2)(const CategoryModuleClassBase<2, 1> &);

CategoryModuleClassBaseAssign2 g_categoryModuleClassBaseAssign2 = &CategoryModuleClassBase<2, 1>::operator=;

typedef CategoryModuleClassBase<3, 1> &(CategoryModuleClassBase<3, 1>::*CategoryModuleClassBaseAssign3)(const CategoryModuleClassBase<3, 1> &);

CategoryModuleClassBaseAssign3 g_categoryModuleClassBaseAssign3 = &CategoryModuleClassBase<3, 1>::operator=;

typedef CategoryModuleClassBase<4, 1> &(CategoryModuleClassBase<4, 1>::*CategoryModuleClassBaseAssign4)(const CategoryModuleClassBase<4, 1> &);

CategoryModuleClassBaseAssign4 g_categoryModuleClassBaseAssign4 = &CategoryModuleClassBase<4, 1>::operator=;

typedef CategoryModuleClassBase<5, 1> &(CategoryModuleClassBase<5, 1>::*CategoryModuleClassBaseAssign5)(const CategoryModuleClassBase<5, 1> &);

CategoryModuleClassBaseAssign5 g_categoryModuleClassBaseAssign5 = &CategoryModuleClassBase<5, 1>::operator=;

typedef CategoryModuleClassBase<6, 1> &(CategoryModuleClassBase<6, 1>::*CategoryModuleClassBaseAssign6)(const CategoryModuleClassBase<6, 1> &);

CategoryModuleClassBaseAssign6 g_categoryModuleClassBaseAssign6 = &CategoryModuleClassBase<6, 1>::operator=;

typedef CategoryModuleClassBase<7, 1> &(CategoryModuleClassBase<7, 1>::*CategoryModuleClassBaseAssign7)(const CategoryModuleClassBase<7, 1> &);

CategoryModuleClassBaseAssign7 g_categoryModuleClassBaseAssign7 = &CategoryModuleClassBase<7, 1>::operator=;

typedef CategoryModuleClassBase<8, 0> &(CategoryModuleClassBase<8, 0>::*CategoryModuleClassBaseAssign8)(const CategoryModuleClassBase<8, 0> &);

CategoryModuleClassBaseAssign8 g_categoryModuleClassBaseAssign8 = &CategoryModuleClassBase<8, 0>::operator=;


// Every module template destructor is the same three vtable stores, walked back
// through the bases with the null-checked adjustment each offset needs, so ICF
// folds all of them onto 0x003A6201. Nothing here constructs one, so an
// explicit destructor call per class is what forces them out.

void fxDestroyBoxEmissionVolumeModuleTemplate(BoxEmissionVolumeModuleTemplate *p) { p->~BoxEmissionVolumeModuleTemplate(); }

void fxDestroyButterflyDrawModuleTemplate(ButterflyDrawModuleTemplate *p) { p->~ButterflyDrawModuleTemplate(); }

void fxDestroyCylinderEmissionVolumeModuleTemplate(CylinderEmissionVolumeModuleTemplate *p) { p->~CylinderEmissionVolumeModuleTemplate(); }

// Not claimed: with the destructor left implicit MSVC never emits it, and
// declaring one out of line drops the null-checked base adjustment retail
// keeps, so this body is the ICF alias that cannot yet be proven.
void fxDestroyLightningDrawModuleTemplate(LightningDrawModuleTemplate *p) { p->~LightningDrawModuleTemplate(); }

// Not claimed: with the destructor left implicit MSVC never emits it, and
// declaring one out of line drops the null-checked base adjustment retail
// keeps, so this body is the ICF alias that cannot yet be proven.
void fxDestroyLightningEmissionModuleTemplate(LightningEmissionModuleTemplate *p) { p->~LightningEmissionModuleTemplate(); }

void fxDestroyLineEmissionVolumeModuleTemplate(LineEmissionVolumeModuleTemplate *p) { p->~LineEmissionVolumeModuleTemplate(); }

// Not claimed: with the destructor left implicit MSVC never emits it, and
// declaring one out of line drops the null-checked base adjustment retail
// keeps, so this body is the ICF alias that cannot yet be proven.
void fxDestroyOrthoEmissionVelocityModuleTemplate(OrthoEmissionVelocityModuleTemplate *p) { p->~OrthoEmissionVelocityModuleTemplate(); }

void fxDestroyPointEmissionVolumeModuleTemplate(PointEmissionVolumeModuleTemplate *p) { p->~PointEmissionVolumeModuleTemplate(); }

void fxDestroyQuadDrawModuleTemplate(QuadDrawModuleTemplate *p) { p->~QuadDrawModuleTemplate(); }

// Not claimed: with the destructor left implicit MSVC never emits it, and
// declaring one out of line drops the null-checked base adjustment retail
// keeps, so this body is the ICF alias that cannot yet be proven.
void fxDestroyRenderObjectUpdateModuleTemplate(RenderObjectUpdateModuleTemplate *p) { p->~RenderObjectUpdateModuleTemplate(); }

void fxDestroySphereEmissionVolumeModuleTemplate(SphereEmissionVolumeModuleTemplate *p) { p->~SphereEmissionVolumeModuleTemplate(); }

void fxDestroySphericalEmissionVelocityModuleTemplate(SphericalEmissionVelocityModuleTemplate *p) { p->~SphericalEmissionVelocityModuleTemplate(); }

void fxDestroyStreakDrawModuleTemplate(StreakDrawModuleTemplate *p) { p->~StreakDrawModuleTemplate(); }

// Not claimed: with the destructor left implicit MSVC never emits it, and
// declaring one out of line drops the null-checked base adjustment retail
// keeps, so this body is the ICF alias that cannot yet be proven.
void fxDestroyTerrainFireEmissionModuleTemplate(TerrainFireEmissionModuleTemplate *p) { p->~TerrainFireEmissionModuleTemplate(); }


// Every info destructor is one vtable store, and the linker folds all of them
// onto 0x0049B47C - Snapshot's own destructor among them. Nothing here destroys
// one, so an explicit call per class is what forces them out.

void fxDestroyInfoBoxEmissionVolumeInfo(BoxEmissionVolumeInfo *p) { p->~BoxEmissionVolumeInfo(); }

void fxDestroyInfoCylinderEmissionVolumeInfo(CylinderEmissionVolumeInfo *p) { p->~CylinderEmissionVolumeInfo(); }

DefaultAlphaModuleInfo::~DefaultAlphaModuleInfo() {}

DefaultColorModuleInfo::~DefaultColorModuleInfo() {}

DefaultPhysicsModuleInfo::~DefaultPhysicsModuleInfo() {}

DefaultUpdateModuleInfo::~DefaultUpdateModuleInfo() {}

void fxDestroyInfoEmissionVelocityInfo(EmissionVelocityInfo *p) { p->~EmissionVelocityInfo(); }

void fxDestroyInfoEmissionVolumeInfo(EmissionVolumeInfo *p) { p->~EmissionVolumeInfo(); }

LightningDrawModuleInfo::~LightningDrawModuleInfo() {}

LightningEmissionInfo::~LightningEmissionInfo() {}

void fxDestroyInfoLineEmissionVolumeInfo(LineEmissionVolumeInfo *p) { p->~LineEmissionVolumeInfo(); }

OrthoEmissionVelocityInfo::~OrthoEmissionVelocityInfo() {}

RenderObjectUpdateModuleInfo::~RenderObjectUpdateModuleInfo() {}

void fxDestroyInfoSphereEmissionVolumeInfo(SphereEmissionVolumeInfo *p) { p->~SphereEmissionVolumeInfo(); }

void fxDestroyInfoSphericalEmissionVelocityInfo(SphericalEmissionVelocityInfo *p) { p->~SphericalEmissionVelocityInfo(); }

TerrainFireEmissionInfo::~TerrainFireEmissionInfo() {}

void fxDestroyInfoWindModuleInfo(WindModuleInfo *p) { p->~WindModuleInfo(); }

}
