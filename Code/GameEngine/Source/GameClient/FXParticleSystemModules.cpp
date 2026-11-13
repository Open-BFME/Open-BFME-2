// cl: /O1 /GX- /arch:SSE2 /Ireference/shims/fxparticle_link
#include "ModuleTemplate.h"
#include "../../Include/GameClient/FXConcreteEventModuleTemplate.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

// The module wrappers, kept apart from the module templates themselves.
//
// Retail puts the two in different translation units - the templates around
// 0x003A65xx, the wrappers around 0x003A90xx - and the split is visible in the
// code rather than only in the addresses: a wrapper's default constructor saves
// esi around the call to the base constructor, which is what a caller that has
// only seen a declaration emits. Compiled beside the definitions, MSVC 7.1
// proves the base leaves ecx alone and keeps `this` there instead. So every
// module template here is a complete type - the layout is needed for the
// wrapper's size - with its constructors and assignment declared and not
// defined.

class INI;

#include "../../Include/GameClient/WindModuleInfo.h"
#include "../../Include/GameClient/EmissionVolumeInfo.h"
#include "../../Include/GameClient/DefaultPhysicsModuleInfo.h"
#include "../../Include/GameClient/SphereEmissionVolumeInfo.h"
#include "../../Include/GameClient/LineEmissionVolumeInfo.h"
#include "../../Include/GameClient/EmissionVelocityInfo.h"
#include "../../Include/GameClient/BoxEmissionVolumeInfo.h"
#include "../../Include/GameClient/LightningEmissionInfo.h"
#include "../../Include/GameClient/TerrainFireEmissionInfo.h"
#include "../../Include/GameClient/SphericalEmissionVelocityInfo.h"
#include "../../Include/GameClient/LifeEventModuleInfo.h"
namespace FXParticleSystem
{



template <int CATEGORY>
class CategoryModuleClass;

// Retail's nested category shape (LINK-584): one pure slot, protected non-virtual destructor.
// The slot is getClass (FXParticleSystemFactories.cpp says why).
template <int CATEGORY_ARG>
class CategoryModuleInfo
{
public:
    virtual const CategoryModuleClass<CATEGORY_ARG> &getClass() const = 0;

protected:
    ~CategoryModuleInfo();
};

template <int CATEGORY_ARG>
class CategoryModuleTemplateBase : public ModuleTemplate, public CategoryModuleInfo<CATEGORY_ARG>
{
public:
    CategoryModuleTemplateBase();
    CategoryModuleTemplateBase(const CategoryModuleTemplateBase<CATEGORY_ARG> &that);
};

struct FXCoord3D
{
    float x;
    float y;
    float z;
};





class CylinderEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    float m_radius;
    float m_length;
    float m_radius2;
    FXCoord3D m_axis;
};


// Sizes come from the clone bodies, which push the wrapper's size to operator
// new: 24 for the spherical and hemispherical velocities, 36 for the
// cylindrical and outward ones, 48 for the ortho one.

class HemisphericalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    FXCoord3D m_unknown04;
};

class CylindricalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    CylindricalEmissionVelocityInfo &operator=(const CylindricalEmissionVelocityInfo &that);

    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
};

class OutwardEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    OutwardEmissionVelocityInfo &operator=(const OutwardEmissionVelocityInfo &that);

    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
};

class OrthoEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
    FXCoord3D m_unknown1C;
};


// The remaining info classes, sized off the same clone bodies: 4 bytes for a
// vtable-only one, 36 for the default physics info, 48 for the lightning draw
// and terrain fire ones, 72 for the category 7 default, 104 for the default
// update info, 132 and 144 for the default alpha and color ones, 140 for the
// lightning emission info and 152 for the render object update info.
struct FXKeyframe
{
    FXCoord3D m_value;
    unsigned int m_frame;
};

#define FX_VTABLE_ONLY_INFO(NAME) \
    class NAME : public ::Snapshot \
    { \
    public: \
        virtual ~NAME(); \
        virtual void LoadPostProcess(); \
        virtual const char *GetSnapshotName(); \
        virtual void DoXfer(::Xfer &); \
    };

FX_VTABLE_ONLY_INFO(DefaultDrawModuleInfo)
class RenderObjectDrawModuleInfo : public ::Snapshot
{
public:
    virtual ~RenderObjectDrawModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);

    unsigned int m_unknown04[15];
};

class GpuDrawModuleInfo : public ::Snapshot
{
public:
    virtual ~GpuDrawModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);

    unsigned int m_unknown04[4];
};
FX_VTABLE_ONLY_INFO(TerrainCollisionModuleInfo)

// The three draw modules whose template bodies live in FXParticleSystem.cpp:
// this unit needs their infos only as complete types behind the class tags.
class StreakDrawModuleInfo : public ::Snapshot
{
public:
    virtual ~StreakDrawModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);
};
class QuadDrawModuleInfo : public ::Snapshot
{
public:
    virtual ~QuadDrawModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);
};
class ButterflyDrawModuleInfo : public ::Snapshot
{
public:
    virtual ~ButterflyDrawModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);
};

// The two category 8 templates put their info's vtable at 0x0C rather than
// 0x08: their first base is CategoryModuleTemplate<8>, whose third base is the
// two-flag EventModuleInfo at 0x08 (retail exports ??0EventModuleInfo at
// 0x00001236 and CategoryModuleTemplate<8>'s assignment at 0x0000124F; see
// FXParticleSystem.cpp). Both wrappers' constructors store the info vtable at
// 0x0C after calling the template constructor.
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
class CategoryModuleTemplate<6> : public CategoryModuleTemplateBase<6>
{
public:
    CategoryModuleTemplate();
    CategoryModuleTemplate(const CategoryModuleTemplate<6> &that);
};

template <>
class CategoryModuleTemplate<8> : public CategoryModuleTemplateBase<8>,
                                  public EventModuleInfo
{
public:
    CategoryModuleTemplate();
    CategoryModuleTemplate(const CategoryModuleTemplate &that);
    virtual ModuleTemplate *clone() const = 0;
};

// Category 7 is wind: retail DefaultModuleTemplate<7> copy at 0x003A8CA5 calls
// CategoryModuleTemplate<7> copy at 0x001F44E4 and its assignment at 0x003A8CF1
// calls CategoryModuleTemplate<7> assignment at 0x001F3719 (both rows in
// FXParticleSystem.cpp), and DefaultModuleTemplate<7> derives from the category
// (see FXParticleSystemDefaultTemplateDtor.cpp). The wind info below copies the
// 17-member layout from FXParticleSystem.cpp (14 floats, a bool, 2 floats: 68
// data + vptr = 72, + 8 = 80 = 0x50 retail clone push at 0x003A9499).

template <>
class CategoryModuleTemplate<7> : public CategoryModuleTemplateBase<7>,
                                  public WindModuleInfo
{
public:
    CategoryModuleTemplate();
    CategoryModuleTemplate(const CategoryModuleTemplate &that);
    virtual ~CategoryModuleTemplate();
};


class DefaultCategory7ModuleInfo
{
public:
    virtual ~DefaultCategory7ModuleInfo();
    virtual void v1() = 0;

    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
    FXCoord3D m_unknown1C;
    FXCoord3D m_unknown28;
    FXCoord3D m_unknown34;
    FXCoord3D m_unknown40;
};

class DefaultUpdateModuleInfo : public ::Snapshot
{
public:
    virtual ~DefaultUpdateModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);

    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
    FXCoord3D m_unknown1C;
    FXCoord3D m_unknown28;
    FXCoord3D m_unknown34;
    float m_unknown40;
    FXCoord3D m_unknown44;
    FXCoord3D m_unknown50;
    FXCoord3D m_unknown5C;
};

class DefaultAlphaModuleInfo : public ::Snapshot
{
public:
    virtual ~DefaultAlphaModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);

    FXKeyframe m_keys[8];
};

class DefaultColorModuleInfo : public ::Snapshot
{
public:
    virtual ~DefaultColorModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);

    FXKeyframe m_keys[8];
    FXCoord3D m_unknown84;
};

class LightningDrawModuleInfo : public ::Snapshot
{
public:
    virtual ~LightningDrawModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);

    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
    FXCoord3D m_unknown1C;
    float m_unknown28;
    bool m_unknown2C;
};

class RenderObjectUpdateModuleInfo : public ::Snapshot
{
public:
    virtual ~RenderObjectUpdateModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);

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
};



#define FX_MODULE_TEMPLATE(NAME, INFO, CAT)                                                             \
    class NAME : public CategoryModuleTemplateBase<CAT>, public INFO                    \
    {                                                                                              \
    public:                                                                                        \
        NAME();                                                                                    \
        NAME(const NAME &that);                                                                    \
        virtual ~NAME();                                                                           \
                                                                                                   \
        NAME &operator=(const NAME &that);                                                         \
    };

FX_MODULE_TEMPLATE(PointEmissionVolumeModuleTemplate, EmissionVolumeInfo, 5)
FX_MODULE_TEMPLATE(SphereEmissionVolumeModuleTemplate, SphereEmissionVolumeInfo, 5)
FX_MODULE_TEMPLATE(BoxEmissionVolumeModuleTemplate, BoxEmissionVolumeInfo, 5)
FX_MODULE_TEMPLATE(LineEmissionVolumeModuleTemplate, LineEmissionVolumeInfo, 5)
FX_MODULE_TEMPLATE(CylinderEmissionVolumeModuleTemplate, CylinderEmissionVolumeInfo, 5)
FX_MODULE_TEMPLATE(SphericalEmissionVelocityModuleTemplate, SphericalEmissionVelocityInfo, 4)
FX_MODULE_TEMPLATE(HemisphericalEmissionVelocityModuleTemplate, HemisphericalEmissionVelocityInfo, 4)
FX_MODULE_TEMPLATE(CylindricalEmissionVelocityModuleTemplate, CylindricalEmissionVelocityInfo, 4)
FX_MODULE_TEMPLATE(OutwardEmissionVelocityModuleTemplate, OutwardEmissionVelocityInfo, 4)
FX_MODULE_TEMPLATE(OrthoEmissionVelocityModuleTemplate, OrthoEmissionVelocityInfo, 4)
FX_MODULE_TEMPLATE(LightningDrawModuleTemplate, LightningDrawModuleInfo, 6)
FX_MODULE_TEMPLATE(TerrainFireEmissionModuleTemplate, TerrainFireEmissionInfo, 5)
FX_MODULE_TEMPLATE(LightningEmissionModuleTemplate, LightningEmissionInfo, 5)
FX_MODULE_TEMPLATE(RenderObjectUpdateModuleTemplate, RenderObjectUpdateModuleInfo, 2)
#define FX_DRAW_MODULE_TEMPLATE(NAME, INFO) \
    class NAME : public CategoryModuleTemplate<6>, public INFO \
    { \
    public: \
        NAME(); \
        NAME(const NAME &that); \
        virtual ~NAME(); \
        NAME &operator=(const NAME &that); \
    };

FX_DRAW_MODULE_TEMPLATE(RenderObjectDrawModuleTemplate, RenderObjectDrawModuleInfo)
FX_DRAW_MODULE_TEMPLATE(GpuDrawModuleTemplate, GpuDrawModuleInfo)

// Complete declarations only, exactly as in FXParticleSystem.cpp (no
// assignment: this unit never assigns a template, it only news them). The
// class instantiation below needs the templates complete; their bodies stay
// over there.
class StreakDrawModule;

class StreakDrawModuleTemplate : public CategoryModuleTemplateBase<6>,
                                 public StreakDrawModuleInfo
{
public:
    StreakDrawModuleTemplate();
    StreakDrawModuleTemplate(const StreakDrawModuleTemplate &that);
    virtual ~StreakDrawModuleTemplate();
};

class QuadDrawModule;

class QuadDrawModuleTemplate : public CategoryModuleTemplateBase<6>,
                               public QuadDrawModuleInfo
{
public:
    QuadDrawModuleTemplate();
    QuadDrawModuleTemplate(const QuadDrawModuleTemplate &that);
    virtual ~QuadDrawModuleTemplate();
};

class ButterflyDrawModule;

class ButterflyDrawModuleTemplate : public CategoryModuleTemplateBase<6>,
                                    public ButterflyDrawModuleInfo
{
public:
    ButterflyDrawModuleTemplate();
    ButterflyDrawModuleTemplate(const ButterflyDrawModuleTemplate &that);
    virtual ~ButterflyDrawModuleTemplate();
};

class LifeEventModule;
class TerrainCollisionModule;

#define FX_EVENT_MODULE_TEMPLATE(NAME, INFO, MODULE)                                                       \
    class NAME : public CategoryModuleTemplate<8>, public INFO                                     \
    {                                                                                              \
    public:                                                                                        \
        NAME();                                                                                    \
        NAME(const NAME &that);                                                                    \
        virtual ~NAME();                                                                           \
                                                                                                   \
        NAME &operator=(const NAME &that);                                                         \
        virtual MODULE *createModule(TrackingPtr<ParticleSystem> &system) = 0; \
        virtual void writeINI(File &file, unsigned int indent) const; \
    };

FX_EVENT_MODULE_TEMPLATE(LifeEventModuleTemplate, LifeEventModuleInfo, LifeEventModule)
FX_EVENT_MODULE_TEMPLATE(TerrainCollisionModuleTemplate, TerrainCollisionModuleInfo, TerrainCollisionModule)

template <int CATEGORY>
class DefaultParticleModule;

// The template assignment hands the info subobject over with a null-preserving
// source: a null `that` reaches the info assignment as a null sub pointer,
// which is the neg/sbb/and idiom retail keeps.
CylindricalEmissionVelocityModuleTemplate &CylindricalEmissionVelocityModuleTemplate::operator=(
    const CylindricalEmissionVelocityModuleTemplate &that)
{
    const void *src = &that;
    const void *sub_src = src ? (const char *)src + 8 : 0;
    ((CylindricalEmissionVelocityInfo *)((char *)this + 8))->operator=(
        *(const CylindricalEmissionVelocityInfo *)sub_src);
    return *this;
}

OutwardEmissionVelocityModuleTemplate &OutwardEmissionVelocityModuleTemplate::operator=(
    const OutwardEmissionVelocityModuleTemplate &that)
{
    const void *src = &that;
    const void *sub_src = src ? (const char *)src + 8 : 0;
    ((OutwardEmissionVelocityInfo *)((char *)this + 8))->operator=(
        *(const OutwardEmissionVelocityInfo *)sub_src);
    return *this;
}

// The module class the wrappers register into. Its constructor hands the key and
// name the tag carries to the per-category base, along with a flag that is set
// only for the two tags that are their category's default.
template <int CATEGORY>
class CategoryModuleClass
{
protected:
    CategoryModuleClass(bool isDefault, const char *key, const char *name);

    // Protected and non-virtual, as FXParticleSystem.cpp proves from the IAE in
    // its own decorated name. That is what makes every wrapper's destructor
    // public and non-virtual too - retail spells them QAE.
    ~CategoryModuleClass() {}
    virtual ModuleTemplate *createTemplate() const = 0;
    virtual ModuleTemplate *createTemplate(::INI *ini) const = 0;
};

// The category numbers' enum (FXParticleSystem.cpp's spelling), the type retail's exported
// ModuleTag<...>::CATEGORY constants carry (W4ModuleCategory@FXParticleSystem@@).
enum ModuleCategory
{
    MODULE_CATEGORY_FIRST
};

template <int CATEGORY_ARG, const char *const &Key, const char *const &Name, class MODULE,
    class TEMPLATE, class DEFAULT>
class ModuleTag
{
public:
    // Retail exports both as data, every IS_DEFAULT false (a default category's own tag is
    // DefaultModuleTag). Retail folds these constants onto shared addresses; /OPT:NOICF keeps
    // each one apart here (LINK-584).
    static const bool IS_DEFAULT = false;
    static const ModuleCategory CATEGORY = (ModuleCategory)CATEGORY_ARG;

    typedef TEMPLATE TemplateType;
    typedef CategoryModuleClass<CATEGORY_ARG> ClassBase;

    // Static REFERENCES, not accessors: MSVC 7.1 gives each one a hidden
    // pointer global, so reading them is a load of that pointer and a load
    // through it - which is the double indirection retail does here.
    static const char *const &KEY;
    static const char *const &NAME;
    static __declspec(dllimport) __forceinline const char *const &keyReference() { return KEY; }
    static __declspec(dllimport) __forceinline const char *const &nameReference() { return NAME; }
};

template <int CATEGORY_ARG, const char *const &Key, const char *const &Name, class MODULE,
    class TEMPLATE, class DEFAULT>
const char *const &ModuleTag<CATEGORY_ARG, Key, Name, MODULE, TEMPLATE, DEFAULT>::KEY = Key;

template <int CATEGORY_ARG, const char *const &Key, const char *const &Name, class MODULE,
    class TEMPLATE, class DEFAULT>
const char *const &ModuleTag<CATEGORY_ARG, Key, Name, MODULE, TEMPLATE, DEFAULT>::NAME = Name;

template <int CATEGORY_ARG, const char *const &Key, const char *const &Name, class MODULE,
    class TEMPLATE, class DEFAULT>
const bool ModuleTag<CATEGORY_ARG, Key, Name, MODULE, TEMPLATE, DEFAULT>::IS_DEFAULT;

template <int CATEGORY_ARG, const char *const &Key, const char *const &Name, class MODULE,
    class TEMPLATE, class DEFAULT>
const ModuleCategory ModuleTag<CATEGORY_ARG, Key, Name, MODULE, TEMPLATE, DEFAULT>::CATEGORY;

template <class TAG>
class ConcreteModuleClass;

template <class TAG>
class ConcreteModuleTemplate : public TAG::TemplateType
{
public:
    ConcreteModuleTemplate();
    __declspec(noinline) ConcreteModuleTemplate(const ConcreteModuleTemplate<TAG> &that);

    virtual const ConcreteModuleClass<TAG> &getClass() const;
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
typename TAG::TemplateType *ConcreteModuleTemplate<TAG>::clone() const
{
    return new ConcreteModuleTemplate<TAG>(*this);
}

// The module class that builds them. createTemplate is one operator new for the
// wrapper's size and a tail jump into its default constructor.
template <class TAG>
class ConcreteModuleClass : public TAG::ClassBase
{
public:
    virtual typename TAG::TemplateType *createTemplate() const;
    virtual typename TAG::TemplateType *createTemplate(::INI *ini) const;

    // Retail's instance is a function-local static in getInstance
    // (NamedModuleClassInstances.cpp), whose atexit thunk calls this.
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<TAG> &getInstance();

private:
    // Private: its callers are getInstance's, built lazily from staticInitModules.
    ConcreteModuleClass();
};

template <class TAG>
ConcreteModuleClass<TAG>::~ConcreteModuleClass()
{
}

template <class TAG>
ConcreteModuleClass<TAG>::ConcreteModuleClass()
    : TAG::ClassBase(TAG::IS_DEFAULT != 0, TAG::keyReference(), TAG::nameReference())
{
}

template <class TAG>
typename TAG::TemplateType *ConcreteModuleClass<TAG>::createTemplate() const
{
    return new ConcreteModuleTemplate<TAG>();
}

#define FX_WRAPPER(CATEGORY, KEY, MOD, TMPL)                                                      \
    extern const char *const KEY##_MODULE_KEY;                                                    \
    extern const char *const KEY##_MODULE_NAME;                                                   \
                                                                                                  \
    class MOD;                                                                                    \
                                                                                                  \
    typedef ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL,                   \
        DefaultParticleModule<CATEGORY> >                                                         \
        MOD##Tag;                                                                                 \
                                                                                                  \
    typedef ConcreteModuleTemplate<MOD##Tag> MOD##Concrete;                                       \
    typedef ConcreteModuleClass<MOD##Tag> MOD##ClassConcrete;                                     \
                                                                                                  \
    template <> __declspec(noinline) MOD##Concrete::~ConcreteModuleTemplate();                 \
    MOD##Concrete g_##MOD##Concrete;                                                              \
    template class ConcreteModuleClass<MOD##Tag>;                                                                                                                                                       MOD##Tag &(MOD##Tag::*g_##MOD##TagAssign)(const MOD##Tag &) = &MOD##Tag::operator=;

// Factory bodies retail kept from the /EHsc factory unit
// (FXParticleSystemFactories.cpp): this unit's vtables only reference them,
// and its exception-free copies are not retail's. Declared, not defined, so
// the factory unit's copies are the only ones linked. Each declaration sits
// right before its class's explicit instantiation: declaring a member
// instantiates ConcreteModuleClass<TAG> there, and that order is the order of
// the tags' KEY/NAME dynamic initializers (_$E<n>, which the
// ledger binds by number).
#define FX_FACTORY_ELSEWHERE(CATEGORY, KEY, MOD, TMPL, DFLT)                                    \
    extern const char *const KEY##_MODULE_KEY;                                                  \
    extern const char *const KEY##_MODULE_NAME;                                                 \
    class MOD;                                                                                  \
    template <> TMPL *ConcreteModuleClass<                                                      \
        ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL, DFLT > >::createTemplate() const;
#define FX_CLONE_ELSEWHERE(CATEGORY, KEY, MOD, TMPL, DFLT)                                      \
    template <> TMPL *ConcreteModuleTemplate<                                                   \
        ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL, DFLT > >::clone() const;

// The point volume's tag is a plain struct rather than a ModuleTag
// instantiation - the U rather than V in the decorated name is what says so.
extern const char *const POINT_EMISSION_VOLUME_MODULE_KEY;
extern const char *const POINT_EMISSION_VOLUME_MODULE_NAME;

// Keep the plain class tag's ABI. This specialization owns only its exported references.
class PointEmissionVolumeModule;
template <> class ModuleTag<5, POINT_EMISSION_VOLUME_MODULE_KEY, POINT_EMISSION_VOLUME_MODULE_NAME,
    PointEmissionVolumeModule, PointEmissionVolumeModuleTemplate, DefaultParticleModule<5> >
{
public:
    static const char *const &KEY;
    static const char *const &NAME;
    static const bool IS_DEFAULT = false;
    static const ModuleCategory CATEGORY = (ModuleCategory)5;
};
typedef ModuleTag<5, POINT_EMISSION_VOLUME_MODULE_KEY, POINT_EMISSION_VOLUME_MODULE_NAME,
    PointEmissionVolumeModule, PointEmissionVolumeModuleTemplate, DefaultParticleModule<5> > PointEmissionVolumeModuleReferenceTag;

struct PointEmissionVolumeModuleTag
{
    enum { IS_DEFAULT = 1 };

    typedef PointEmissionVolumeModuleTemplate TemplateType;
    typedef CategoryModuleClass<5> ClassBase;

    static __declspec(dllimport) __forceinline const char *const &keyReference()
    {
        return PointEmissionVolumeModuleReferenceTag::KEY;
    }
    static __declspec(dllimport) __forceinline const char *const &nameReference()
    {
        return PointEmissionVolumeModuleReferenceTag::NAME;
    }
};

typedef ConcreteModuleTemplate<PointEmissionVolumeModuleTag> PointEmissionVolumeModuleConcrete;
typedef ConcreteModuleClass<PointEmissionVolumeModuleTag> PointEmissionVolumeModuleClassConcrete;

PointEmissionVolumeModuleConcrete g_pointEmissionVolumeModuleConcrete;

// Defined after the concrete global: retail initialises both references at
// run time (0x007AF6B1 and 0x007AF6BC store the key and name pointers), and
// cl 7.1 only does that once a dynamic initializer precedes them in the unit.
// Ahead of every dynamic initializer it binds them statically in .data.
const char *const &PointEmissionVolumeModuleReferenceTag::KEY = POINT_EMISSION_VOLUME_MODULE_KEY;
const char *const &PointEmissionVolumeModuleReferenceTag::NAME = POINT_EMISSION_VOLUME_MODULE_NAME;
template class ConcreteModuleClass<PointEmissionVolumeModuleTag>;

// Same empty-tag fold as the ortho tag above.
PointEmissionVolumeModuleTag &(PointEmissionVolumeModuleTag::*g_pointEmissionVolumeModuleTagAssign)(
    const PointEmissionVolumeModuleTag &) = &PointEmissionVolumeModuleTag::operator=;

FX_WRAPPER(5, SPHERE_EMISSION_VOLUME, SphereEmissionVolumeModule,
    SphereEmissionVolumeModuleTemplate)
FX_WRAPPER(5, BOX_EMISSION_VOLUME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate)
FX_WRAPPER(5, LINE_EMISSION_VOLUME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate)
FX_WRAPPER(5, CYLINDER_EMISSION_VOLUME, CylinderEmissionVolumeModule,
    CylinderEmissionVolumeModuleTemplate)

FX_FACTORY_ELSEWHERE(4, SPHERICAL_EMISSION_VELOCITY, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>)
FX_WRAPPER(4, SPHERICAL_EMISSION_VELOCITY, SphericalEmissionVelocityModule,
    SphericalEmissionVelocityModuleTemplate)
FX_FACTORY_ELSEWHERE(4, HEMISPHERICAL_EMISSION_VELOCITY, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>)
FX_WRAPPER(4, HEMISPHERICAL_EMISSION_VELOCITY, HemisphericalEmissionVelocityModule,
    HemisphericalEmissionVelocityModuleTemplate)
FX_FACTORY_ELSEWHERE(4, CYLINDRICAL_EMISSION_VELOCITY, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>)
FX_WRAPPER(4, CYLINDRICAL_EMISSION_VELOCITY, CylindricalEmissionVelocityModule,
    CylindricalEmissionVelocityModuleTemplate)
FX_FACTORY_ELSEWHERE(4, OUTWARD_EMISSION_VELOCITY, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>)
FX_WRAPPER(4, OUTWARD_EMISSION_VELOCITY, OutwardEmissionVelocityModule,
    OutwardEmissionVelocityModuleTemplate)

// The ortho velocity tag is the other plain struct.
extern const char *const ORTHO_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const ORTHO_EMISSION_VELOCITY_MODULE_NAME;

class OrthoEmissionVelocityModule;
template <> class ModuleTag<4, ORTHO_EMISSION_VELOCITY_MODULE_KEY, ORTHO_EMISSION_VELOCITY_MODULE_NAME,
    OrthoEmissionVelocityModule, OrthoEmissionVelocityModuleTemplate, DefaultParticleModule<4> >
{
public:
    static const char *const &KEY;
    static const char *const &NAME;
    static const bool IS_DEFAULT = false;
    static const ModuleCategory CATEGORY = (ModuleCategory)4;
};
typedef ModuleTag<4, ORTHO_EMISSION_VELOCITY_MODULE_KEY, ORTHO_EMISSION_VELOCITY_MODULE_NAME,
    OrthoEmissionVelocityModule, OrthoEmissionVelocityModuleTemplate, DefaultParticleModule<4> > OrthoEmissionVelocityModuleReferenceTag;

struct OrthoEmissionVelocityModuleTag
{
    enum { IS_DEFAULT = 1 };

    typedef OrthoEmissionVelocityModuleTemplate TemplateType;
    typedef CategoryModuleClass<4> ClassBase;

    static __declspec(dllimport) __forceinline const char *const &keyReference()
    {
        return OrthoEmissionVelocityModuleReferenceTag::KEY;
    }
    static __declspec(dllimport) __forceinline const char *const &nameReference()
    {
        return OrthoEmissionVelocityModuleReferenceTag::NAME;
    }
};

const char *const &OrthoEmissionVelocityModuleReferenceTag::KEY = ORTHO_EMISSION_VELOCITY_MODULE_KEY;
const char *const &OrthoEmissionVelocityModuleReferenceTag::NAME = ORTHO_EMISSION_VELOCITY_MODULE_NAME;

typedef ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> OrthoEmissionVelocityModuleConcrete;

template <> __declspec(noinline) OrthoEmissionVelocityModuleConcrete::~ConcreteModuleTemplate();
typedef ConcreteModuleClass<OrthoEmissionVelocityModuleTag>
    OrthoEmissionVelocityModuleClassConcrete;

OrthoEmissionVelocityModuleConcrete g_orthoEmissionVelocityModuleConcrete;
template <> OrthoEmissionVelocityModuleTemplate *
ConcreteModuleClass<OrthoEmissionVelocityModuleTag>::createTemplate() const;
template class ConcreteModuleClass<OrthoEmissionVelocityModuleTag>;

// Nothing assigns a tag - they carry only statics - so the generated copy is
// `mov eax, ecx; ret 4`, folded with every other empty assignment in the game.
OrthoEmissionVelocityModuleTag &(OrthoEmissionVelocityModuleTag::*g_orthoEmissionVelocityModuleTagAssign)(
    const OrthoEmissionVelocityModuleTag &) = &OrthoEmissionVelocityModuleTag::operator=;

// The per-category default templates, each over the info its own category uses.
#define FX_DEFAULT_TEMPLATE(CATEGORY, INFO)                                                            template <>                                                                                        class DefaultModuleTemplate<CATEGORY> : public CategoryModuleTemplateBase<CATEGORY>,                                                 public INFO                                                {                                                                                                  public:                                                                                                DefaultModuleTemplate();                                                                           DefaultModuleTemplate(const DefaultModuleTemplate<CATEGORY> &that); virtual ~DefaultModuleTemplate();                            };

template <int CATEGORY>
class DefaultModuleTemplate;

FX_DEFAULT_TEMPLATE(0, DefaultColorModuleInfo)
FX_DEFAULT_TEMPLATE(1, DefaultAlphaModuleInfo)
FX_DEFAULT_TEMPLATE(2, DefaultUpdateModuleInfo)
FX_DEFAULT_TEMPLATE(3, DefaultPhysicsModuleInfo)
FX_DEFAULT_TEMPLATE(6, DefaultDrawModuleInfo)
// Default 7 is not a triple over DefaultCategory7ModuleInfo (which would be
// 76 + 8 = 84 = 0x54): it derives from CategoryModuleTemplate<7> above, giving
// 72 + 8 = 80 = 0x50 as retail 0x003A9499 pushes. The unused
// DefaultCategory7ModuleInfo above is kept only to minimise the diff.
template <>
class DefaultModuleTemplate<7> : public CategoryModuleTemplate<7>
{
public:
    DefaultModuleTemplate();
    DefaultModuleTemplate(const DefaultModuleTemplate<7> &that);
};

template <int CATEGORY>
struct DefaultModuleKey
{
    static const char *const VALUE;
};

template <int CATEGORY>
struct DefaultModuleName
{
    static const char *const VALUE;
};

template <int CATEGORY>
class DefaultModule;

// A default tag's key and name are the plain ModuleTag's over the category's default key and
// name, from the accessors in FXParticleSystemDefaults.cpp: retail exports them as that
// ModuleTag's KEY and NAME (LINK-584). MSVC 7.1 refuses DefaultModuleKey<CATEGORY>::VALUE as a
// dependent template argument, so each category names its base.
template <int CATEGORY>
struct DefaultModuleTagBase;

#define FX_DEFAULT_TAG_BASE(CATEGORY)                                                              \
    template <>                                                                                    \
    struct DefaultModuleTagBase<CATEGORY>                                                          \
    {                                                                                              \
        typedef ModuleTag<CATEGORY, DefaultModuleKey<CATEGORY>::VALUE,                             \
            DefaultModuleName<CATEGORY>::VALUE, DefaultModule<CATEGORY>,                           \
            DefaultModuleTemplate<CATEGORY>, DefaultParticleModule<CATEGORY> > Type;               \
    };

FX_DEFAULT_TAG_BASE(0)
FX_DEFAULT_TAG_BASE(1)
FX_DEFAULT_TAG_BASE(2)
FX_DEFAULT_TAG_BASE(3)
FX_DEFAULT_TAG_BASE(6)
FX_DEFAULT_TAG_BASE(7)

template <int CATEGORY>
class DefaultModuleTag : public DefaultModuleTagBase<CATEGORY>::Type
{
public:
    // The default tag of a category, and the one whose registration flag is set.
    enum { IS_DEFAULT = 1 };

    typedef DefaultModuleTemplate<CATEGORY> TemplateType;
    typedef CategoryModuleClass<CATEGORY> ClassBase;
};

#define FX_DEFAULT_WRAPPER(CATEGORY)                                                                   typedef ConcreteModuleTemplate<DefaultModuleTag<CATEGORY> > DefaultConcrete##CATEGORY;                                                                                                                template <> __declspec(noinline) DefaultConcrete##CATEGORY::~ConcreteModuleTemplate(); DefaultConcrete##CATEGORY g_defaultConcrete##CATEGORY;                                                                                                                                                              template class ConcreteModuleClass<DefaultModuleTag<CATEGORY> >;

template <> DefaultModuleTemplate<0> *ConcreteModuleClass<DefaultModuleTag<0> >::createTemplate() const;
template <> DefaultModuleTemplate<1> *ConcreteModuleClass<DefaultModuleTag<1> >::createTemplate() const;
template <> DefaultModuleTemplate<2> *ConcreteModuleClass<DefaultModuleTag<2> >::createTemplate() const;
template <> DefaultModuleTemplate<3> *ConcreteModuleClass<DefaultModuleTag<3> >::createTemplate() const;
template <> DefaultModuleTemplate<6> *ConcreteModuleClass<DefaultModuleTag<6> >::createTemplate() const;
template <> DefaultModuleTemplate<7> *ConcreteModuleClass<DefaultModuleTag<7> >::createTemplate() const;

FX_DEFAULT_WRAPPER(0)
FX_DEFAULT_WRAPPER(1)
FX_DEFAULT_WRAPPER(2)
FX_DEFAULT_WRAPPER(3)
FX_DEFAULT_WRAPPER(6)
FX_DEFAULT_WRAPPER(7)

FX_FACTORY_ELSEWHERE(6, LIGHTNING_DRAW, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>)
FX_WRAPPER(6, LIGHTNING_DRAW, LightningDrawModule, LightningDrawModuleTemplate)
FX_FACTORY_ELSEWHERE(5, TERRAIN_FIRE_EMISSION, TerrainFireEmissionModule, TerrainFireEmissionModuleTemplate, DefaultParticleModule<5>)
FX_WRAPPER(5, TERRAIN_FIRE_EMISSION, TerrainFireEmissionModule, TerrainFireEmissionModuleTemplate)
FX_FACTORY_ELSEWHERE(5, LIGHTNING_EMISSION, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>)
FX_WRAPPER(5, LIGHTNING_EMISSION, LightningEmissionModule, LightningEmissionModuleTemplate)
extern const char *const RENDEROBJECT_UPDATE_MODULE_KEY;
extern const char *const RENDEROBJECT_UPDATE_MODULE_NAME;
class RenderObjectUpdateModule;

template <> RenderObjectUpdateModuleTemplate *ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, DefaultParticleModule<2> > >::createTemplate() const;

// This DefaultParticleModule<2> spelling of the update tag is this unit's, not retail's: retail
// folded its constructor into the named update wrapper's (0x003A8D15), so its tables are that
// wrapper's and its getClass is the named getClass, a tail jump into the named class's
// getInstance (0x003AD131). Defined after the named class's explicit instantiation below.
template <> const ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, DefaultParticleModule<2> > > &
ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, DefaultParticleModule<2> > >::getClass() const;
FX_WRAPPER(2, RENDEROBJECT_UPDATE, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate)

// The draw wrappers' factory declarations come before the named wrappers: declaring a named
// wrapper's member instantiates its template and, through getClass's covariant return, its
// class, so these keep the draw tags' KEY/NAME initializers ahead of the named tags', as the
// FX_FACTORY_ELSEWHERE note above requires.
FX_FACTORY_ELSEWHERE(6, RENDEROBJECT_DRAW, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>)
FX_FACTORY_ELSEWHERE(6, GPU_DRAW, GpuDrawModule, GpuDrawModuleTemplate, DefaultParticleModule<6>)
FX_FACTORY_ELSEWHERE(6, STREAK_DRAW, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>)
FX_FACTORY_ELSEWHERE(6, QUAD_DRAW, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>)
FX_FACTORY_ELSEWHERE(6, BUTTERFLY_DRAW, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>)

// Five tags whose sixth argument is a plain class rather than a
// DefaultParticleModule instantiation. Only the constructors are claimed from
// them; their clones carry an EH prologue and are a separate problem.
#define FX_NAMED_WRAPPER(CATEGORY, KEY, MOD, TMPL, DFLT)                                               extern const char *const KEY##_MODULE_KEY;                                                         extern const char *const KEY##_MODULE_NAME;                                                                                                                                                           class MOD;                                                                                         class DFLT;                                                                                                                                                                                           typedef ConcreteModuleTemplate<                                                                        ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL, DFLT> >                        MOD##NamedConcrete;                                                                                                                                                                               MOD##NamedConcrete g_##MOD##NamedConcrete;                                                                                                                                                               typedef ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL, DFLT>                     MOD##NamedTag;                                                                                                                                                                                  MOD##NamedTag &(MOD##NamedTag::*g_##MOD##NamedTagAssign)(const MOD##NamedTag &) =                     &MOD##NamedTag::operator=;

class RenderObjectParticleUpdateModule;
// The named wrappers' deleting destructors call the wrapper destructor out of
// line, as retail's (FXParticleSystemFactories.cpp rows 0x003AA1EA, 0x003AB92A)
// do; inlined, the 5-byte wrapper destructor would become a direct call to the
// module template's. This one is also this unit's 0x003A9397 row.
template <> __declspec(noinline) inline ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY,
    RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate,
    RenderObjectParticleUpdateModule> >::~ConcreteModuleTemplate() {}
FX_NAMED_WRAPPER(2, RENDEROBJECT_UPDATE, RenderObjectUpdateModule,
    RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule)
extern const char *const LIFE_EVENT_MODULE_KEY;
extern const char *const LIFE_EVENT_MODULE_NAME;
class LifeEventModule;
class ParticleLifeEventModule;
BFME_FX_EVENT_CONCRETE(LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME)
FX_CLONE_ELSEWHERE(8, LIFE_EVENT, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule)
template <> __declspec(noinline) ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY,
    LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule> >::~ConcreteModuleTemplate();
FX_NAMED_WRAPPER(8, LIFE_EVENT, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule)
extern const char *const TERRAIN_COLLISION_MODULE_KEY;
extern const char *const TERRAIN_COLLISION_MODULE_NAME;
class TerrainCollisionModule;
class ParticleTerrainCollisionModule;
typedef ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME,
    TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule>
    TerrainCollisionModuleNamedTag;
BFME_FX_EVENT_CONCRETE(TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME)
template <> TerrainCollisionModuleTemplate *ConcreteModuleTemplate<TerrainCollisionModuleNamedTag>::clone() const;
template <> __declspec(dllimport) __forceinline ConcreteModuleTemplate<TerrainCollisionModuleNamedTag>::~ConcreteModuleTemplate();
FX_NAMED_WRAPPER(8, TERRAIN_COLLISION, TerrainCollisionModule, TerrainCollisionModuleTemplate,
    ParticleTerrainCollisionModule)

FX_CLONE_ELSEWHERE(6, RENDEROBJECT_DRAW, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>)
FX_WRAPPER(6, RENDEROBJECT_DRAW, RenderObjectDrawModule, RenderObjectDrawModuleTemplate)
FX_CLONE_ELSEWHERE(6, GPU_DRAW, GpuDrawModule, GpuDrawModuleTemplate, DefaultParticleModule<6>)
FX_WRAPPER(6, GPU_DRAW, GpuDrawModule, GpuDrawModuleTemplate)
// Their clones are declared above, so the copy constructors (this unit's
// rows) are instantiated explicitly.
template ConcreteModuleTemplate<RenderObjectDrawModuleTag>::ConcreteModuleTemplate(
    const ConcreteModuleTemplate<RenderObjectDrawModuleTag> &that);
template ConcreteModuleTemplate<GpuDrawModuleTag>::ConcreteModuleTemplate(
    const ConcreteModuleTemplate<GpuDrawModuleTag> &that);

// The classes whose template bodies live elsewhere: this unit emits only the
// class constructors, over the same tags. A full FX_WRAPPER would also define
// the template's global and duplicate the bodies FXParticleSystem.cpp owns.
#define FX_CLASS_WRAPPER(CATEGORY, KEY, MOD, TMPL, DFLT)                                        \
    extern const char *const KEY##_MODULE_KEY;                                                  \
    extern const char *const KEY##_MODULE_NAME;                                                 \
    typedef ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL, DFLT >            \
        MOD##ClassTag;                                                                          \
    template <> __declspec(noinline) ConcreteModuleTemplate<MOD##ClassTag>::~ConcreteModuleTemplate(); \
    template class ConcreteModuleClass<MOD##ClassTag>;

FX_CLASS_WRAPPER(6, STREAK_DRAW, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>)
FX_CLASS_WRAPPER(6, QUAD_DRAW, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>)
FX_CLASS_WRAPPER(6, BUTTERFLY_DRAW, ButterflyDrawModule, ButterflyDrawModuleTemplate,
    DefaultParticleModule<6>)

// The named-tag classes: same treatment, over the tags FX_NAMED_WRAPPER made.
// Their factory specializations are declared here, beside each explicit
// instantiation, not with the wrappers above: declaring a member of
// ConcreteModuleClass<TAG> instantiates the class, and that point fixes where
// its tag's KEY/NAME dynamic initializers fall in the
// unit's _$E sequence (retail: after the three FX_CLASS_WRAPPER tags).
template <> RenderObjectUpdateModuleTemplate *
ConcreteModuleClass<RenderObjectUpdateModuleNamedTag>::createTemplate() const;
template class ConcreteModuleClass<RenderObjectUpdateModuleNamedTag>;
template <> const ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, DefaultParticleModule<2> > > &
ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, DefaultParticleModule<2> > >::getClass() const
{
    return reinterpret_cast<const ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, DefaultParticleModule<2> > > &>(
        ConcreteModuleClass<RenderObjectUpdateModuleNamedTag>::getInstance());
}
template <> LifeEventModuleTemplate *ConcreteModuleClass<LifeEventModuleNamedTag>::createTemplate() const;
template class ConcreteModuleClass<LifeEventModuleNamedTag>;
template ConcreteModuleTemplate<LifeEventModuleNamedTag>::ConcreteModuleTemplate(const ConcreteModuleTemplate<LifeEventModuleNamedTag> &that);
template ConcreteModuleTemplate<TerrainCollisionModuleNamedTag>::ConcreteModuleTemplate(const ConcreteModuleTemplate<TerrainCollisionModuleNamedTag> &that);
template <> TerrainCollisionModuleTemplate *
ConcreteModuleClass<TerrainCollisionModuleNamedTag>::createTemplate() const;
template class ConcreteModuleClass<TerrainCollisionModuleNamedTag>;

// The wrappers' generated assignments. They forward to the module template's own
// assignment, which this unit only declares - beside the definitions MSVC 7.1
// inlines it instead.

typedef PointEmissionVolumeModuleConcrete &(PointEmissionVolumeModuleConcrete::*PointEmissionVolumeModuleConcreteAssign)(const PointEmissionVolumeModuleConcrete &);

PointEmissionVolumeModuleConcreteAssign g_pointEmissionVolumeModuleConcreteAssign = &PointEmissionVolumeModuleConcrete::operator=;

typedef SphereEmissionVolumeModuleConcrete &(SphereEmissionVolumeModuleConcrete::*SphereEmissionVolumeModuleConcreteAssign)(const SphereEmissionVolumeModuleConcrete &);

SphereEmissionVolumeModuleConcreteAssign g_sphereEmissionVolumeModuleConcreteAssign = &SphereEmissionVolumeModuleConcrete::operator=;

typedef BoxEmissionVolumeModuleConcrete &(BoxEmissionVolumeModuleConcrete::*BoxEmissionVolumeModuleConcreteAssign)(const BoxEmissionVolumeModuleConcrete &);

extern BoxEmissionVolumeModuleConcreteAssign g_boxEmissionVolumeModuleConcreteAssign;

typedef LineEmissionVolumeModuleConcrete &(LineEmissionVolumeModuleConcrete::*LineEmissionVolumeModuleConcreteAssign)(const LineEmissionVolumeModuleConcrete &);

extern LineEmissionVolumeModuleConcreteAssign g_lineEmissionVolumeModuleConcreteAssign;

typedef CylinderEmissionVolumeModuleConcrete &(CylinderEmissionVolumeModuleConcrete::*CylinderEmissionVolumeModuleConcreteAssign)(const CylinderEmissionVolumeModuleConcrete &);

extern CylinderEmissionVolumeModuleConcreteAssign g_cylinderEmissionVolumeModuleConcreteAssign;

typedef OrthoEmissionVelocityModuleConcrete &(OrthoEmissionVelocityModuleConcrete::*OrthoEmissionVelocityModuleConcreteAssign)(const OrthoEmissionVelocityModuleConcrete &);

OrthoEmissionVelocityModuleConcreteAssign g_orthoEmissionVelocityModuleConcreteAssign = &OrthoEmissionVelocityModuleConcrete::operator=;

typedef CylindricalEmissionVelocityModuleConcrete &(CylindricalEmissionVelocityModuleConcrete::*CylindricalEmissionVelocityModuleConcreteAssign)(const CylindricalEmissionVelocityModuleConcrete &);

CylindricalEmissionVelocityModuleConcreteAssign g_cylindricalEmissionVelocityModuleConcreteAssign = &CylindricalEmissionVelocityModuleConcrete::operator=;

typedef OutwardEmissionVelocityModuleConcrete &(OutwardEmissionVelocityModuleConcrete::*OutwardEmissionVelocityModuleConcreteAssign)(const OutwardEmissionVelocityModuleConcrete &);

OutwardEmissionVelocityModuleConcreteAssign g_outwardEmissionVelocityModuleConcreteAssign = &OutwardEmissionVelocityModuleConcrete::operator=;

typedef SphericalEmissionVelocityModuleConcrete &(SphericalEmissionVelocityModuleConcrete::*SphericalEmissionVelocityModuleConcreteAssign)(const SphericalEmissionVelocityModuleConcrete &);

SphericalEmissionVelocityModuleConcreteAssign g_sphericalEmissionVelocityModuleConcreteAssign = &SphericalEmissionVelocityModuleConcrete::operator=;

typedef LightningDrawModuleConcrete &(LightningDrawModuleConcrete::*LightningDrawModuleConcreteAssign)(const LightningDrawModuleConcrete &);

extern LightningDrawModuleConcreteAssign g_lightningDrawModuleConcreteAssign;

typedef TerrainFireEmissionModuleConcrete &(TerrainFireEmissionModuleConcrete::*TerrainFireEmissionModuleConcreteAssign)(const TerrainFireEmissionModuleConcrete &);

extern TerrainFireEmissionModuleConcreteAssign g_terrainFireEmissionModuleConcreteAssign;

typedef LightningEmissionModuleConcrete &(LightningEmissionModuleConcrete::*LightningEmissionModuleConcreteAssign)(const LightningEmissionModuleConcrete &);

extern LightningEmissionModuleConcreteAssign g_lightningEmissionModuleConcreteAssign;

typedef RenderObjectUpdateModuleConcrete &(RenderObjectUpdateModuleConcrete::*RenderObjectUpdateModuleConcreteAssign)(const RenderObjectUpdateModuleConcrete &);

RenderObjectUpdateModuleConcreteAssign g_renderObjectUpdateModuleConcreteAssign = &RenderObjectUpdateModuleConcrete::operator=;

typedef RenderObjectDrawModuleConcrete &(RenderObjectDrawModuleConcrete::*RenderObjectDrawModuleConcreteAssign)(const RenderObjectDrawModuleConcrete &);

extern RenderObjectDrawModuleConcreteAssign g_renderObjectDrawModuleConcreteAssign;

typedef GpuDrawModuleConcrete &(GpuDrawModuleConcrete::*GpuDrawModuleConcreteAssign)(const GpuDrawModuleConcrete &);

extern GpuDrawModuleConcreteAssign g_gpuDrawModuleConcreteAssign;

typedef DefaultConcrete0 &(DefaultConcrete0::*DefaultConcrete0Assign)(const DefaultConcrete0 &);

extern DefaultConcrete0Assign g_defaultConcrete0Assign;

typedef DefaultConcrete1 &(DefaultConcrete1::*DefaultConcrete1Assign)(const DefaultConcrete1 &);

extern DefaultConcrete1Assign g_defaultConcrete1Assign;

typedef DefaultConcrete2 &(DefaultConcrete2::*DefaultConcrete2Assign)(const DefaultConcrete2 &);

extern DefaultConcrete2Assign g_defaultConcrete2Assign;

typedef DefaultConcrete3 &(DefaultConcrete3::*DefaultConcrete3Assign)(const DefaultConcrete3 &);

extern DefaultConcrete3Assign g_defaultConcrete3Assign;

typedef DefaultConcrete6 &(DefaultConcrete6::*DefaultConcrete6Assign)(const DefaultConcrete6 &);

DefaultConcrete6Assign g_defaultConcrete6Assign = &DefaultConcrete6::operator=;

// The underlying template's own generated copy, the same empty five bytes.
typedef DefaultModuleTemplate<6> &(DefaultModuleTemplate<6>::*DefaultModuleTemplate6Assign)(
    const DefaultModuleTemplate<6> &);

DefaultModuleTemplate6Assign g_defaultModuleTemplate6Assign = &DefaultModuleTemplate<6>::operator=;

typedef RenderObjectUpdateModuleNamedConcrete &(RenderObjectUpdateModuleNamedConcrete::*RenderObjectUpdateModuleNamedConcreteAssign)(const RenderObjectUpdateModuleNamedConcrete &);

RenderObjectUpdateModuleNamedConcreteAssign g_renderObjectUpdateModuleNamedConcreteAssign = &RenderObjectUpdateModuleNamedConcrete::operator=;

typedef LifeEventModuleNamedConcrete &(LifeEventModuleNamedConcrete::*LifeEventModuleNamedConcreteAssign)(const LifeEventModuleNamedConcrete &);

LifeEventModuleNamedConcreteAssign g_lifeEventModuleNamedConcreteAssign = &LifeEventModuleNamedConcrete::operator=;

typedef TerrainCollisionModuleNamedConcrete &(TerrainCollisionModuleNamedConcrete::*TerrainCollisionModuleNamedConcreteAssign)(const TerrainCollisionModuleNamedConcrete &);

TerrainCollisionModuleNamedConcreteAssign g_terrainCollisionModuleNamedConcreteAssign = &TerrainCollisionModuleNamedConcrete::operator=;

#pragma inline_depth(0)
// ?bfmeEmitFXParticleSystemModulesAssign@@YAXXZ present-unmatched
void bfmeEmitFXParticleSystemModulesAssign()
{
    (void)&BoxEmissionVolumeModuleConcrete::operator=;
    (void)&LineEmissionVolumeModuleConcrete::operator=;
    (void)&CylinderEmissionVolumeModuleConcrete::operator=;
    (void)&LightningDrawModuleConcrete::operator=;
    (void)&TerrainFireEmissionModuleConcrete::operator=;
    (void)&LightningEmissionModuleConcrete::operator=;
    (void)&RenderObjectDrawModuleConcrete::operator=;
    (void)&GpuDrawModuleConcrete::operator=;
    (void)&DefaultConcrete0::operator=;
    (void)&DefaultConcrete1::operator=;
    (void)&DefaultConcrete2::operator=;
    (void)&DefaultConcrete3::operator=;
}
#pragma inline_depth()


// Retail's exported ModuleTag<...>::IS_DEFAULT and CATEGORY constants (LINK-584): one definition
// each, for the tags retail exports them for, the six default categories' own ModuleTag included.
template <int CATEGORY_ARG> class DefaultModule;
typedef ModuleTag<0, DefaultModuleKey<0>::VALUE, DefaultModuleName<0>::VALUE, DefaultModule<0>, DefaultModuleTemplate<0>, DefaultParticleModule<0> > DefaultModuleExportTag0;
typedef ModuleTag<1, DefaultModuleKey<1>::VALUE, DefaultModuleName<1>::VALUE, DefaultModule<1>, DefaultModuleTemplate<1>, DefaultParticleModule<1> > DefaultModuleExportTag1;
typedef ModuleTag<2, DefaultModuleKey<2>::VALUE, DefaultModuleName<2>::VALUE, DefaultModule<2>, DefaultModuleTemplate<2>, DefaultParticleModule<2> > DefaultModuleExportTag2;
typedef ModuleTag<3, DefaultModuleKey<3>::VALUE, DefaultModuleName<3>::VALUE, DefaultModule<3>, DefaultModuleTemplate<3>, DefaultParticleModule<3> > DefaultModuleExportTag3;
typedef ModuleTag<6, DefaultModuleKey<6>::VALUE, DefaultModuleName<6>::VALUE, DefaultModule<6>, DefaultModuleTemplate<6>, DefaultParticleModule<6> > DefaultModuleExportTag6;
typedef ModuleTag<7, DefaultModuleKey<7>::VALUE, DefaultModuleName<7>::VALUE, DefaultModule<7>, DefaultModuleTemplate<7>, DefaultParticleModule<7> > DefaultModuleExportTag7;
template const bool SphereEmissionVolumeModuleTag::IS_DEFAULT;
template const ModuleCategory SphereEmissionVolumeModuleTag::CATEGORY;
template const bool BoxEmissionVolumeModuleTag::IS_DEFAULT;
template const ModuleCategory BoxEmissionVolumeModuleTag::CATEGORY;
template const bool LineEmissionVolumeModuleTag::IS_DEFAULT;
template const ModuleCategory LineEmissionVolumeModuleTag::CATEGORY;
template const bool CylinderEmissionVolumeModuleTag::IS_DEFAULT;
template const ModuleCategory CylinderEmissionVolumeModuleTag::CATEGORY;
template const bool SphericalEmissionVelocityModuleTag::IS_DEFAULT;
template const ModuleCategory SphericalEmissionVelocityModuleTag::CATEGORY;
template const bool HemisphericalEmissionVelocityModuleTag::IS_DEFAULT;
template const ModuleCategory HemisphericalEmissionVelocityModuleTag::CATEGORY;
template const bool CylindricalEmissionVelocityModuleTag::IS_DEFAULT;
template const ModuleCategory CylindricalEmissionVelocityModuleTag::CATEGORY;
template const bool OutwardEmissionVelocityModuleTag::IS_DEFAULT;
template const ModuleCategory OutwardEmissionVelocityModuleTag::CATEGORY;
template const bool LightningDrawModuleTag::IS_DEFAULT;
template const ModuleCategory LightningDrawModuleTag::CATEGORY;
template const bool TerrainFireEmissionModuleTag::IS_DEFAULT;
template const ModuleCategory TerrainFireEmissionModuleTag::CATEGORY;
template const bool LightningEmissionModuleTag::IS_DEFAULT;
template const ModuleCategory LightningEmissionModuleTag::CATEGORY;
template const bool RenderObjectDrawModuleTag::IS_DEFAULT;
template const ModuleCategory RenderObjectDrawModuleTag::CATEGORY;
template const bool GpuDrawModuleTag::IS_DEFAULT;
template const ModuleCategory GpuDrawModuleTag::CATEGORY;
template const bool RenderObjectUpdateModuleNamedTag::IS_DEFAULT;
template const ModuleCategory RenderObjectUpdateModuleNamedTag::CATEGORY;
template const bool LifeEventModuleNamedTag::IS_DEFAULT;
template const ModuleCategory LifeEventModuleNamedTag::CATEGORY;
template const bool TerrainCollisionModuleNamedTag::IS_DEFAULT;
template const ModuleCategory TerrainCollisionModuleNamedTag::CATEGORY;
template const bool StreakDrawModuleClassTag::IS_DEFAULT;
template const ModuleCategory StreakDrawModuleClassTag::CATEGORY;
template const bool QuadDrawModuleClassTag::IS_DEFAULT;
template const ModuleCategory QuadDrawModuleClassTag::CATEGORY;
template const bool ButterflyDrawModuleClassTag::IS_DEFAULT;
template const ModuleCategory ButterflyDrawModuleClassTag::CATEGORY;
const bool PointEmissionVolumeModuleReferenceTag::IS_DEFAULT;
const ModuleCategory PointEmissionVolumeModuleReferenceTag::CATEGORY;
const bool OrthoEmissionVelocityModuleReferenceTag::IS_DEFAULT;
const ModuleCategory OrthoEmissionVelocityModuleReferenceTag::CATEGORY;
template const bool DefaultModuleExportTag0::IS_DEFAULT;
template const ModuleCategory DefaultModuleExportTag0::CATEGORY;
template const bool DefaultModuleExportTag1::IS_DEFAULT;
template const ModuleCategory DefaultModuleExportTag1::CATEGORY;
template const bool DefaultModuleExportTag2::IS_DEFAULT;
template const ModuleCategory DefaultModuleExportTag2::CATEGORY;
template const bool DefaultModuleExportTag3::IS_DEFAULT;
template const ModuleCategory DefaultModuleExportTag3::CATEGORY;
template const bool DefaultModuleExportTag6::IS_DEFAULT;
template const ModuleCategory DefaultModuleExportTag6::CATEGORY;
template const bool DefaultModuleExportTag7::IS_DEFAULT;
template const ModuleCategory DefaultModuleExportTag7::CATEGORY;
}
