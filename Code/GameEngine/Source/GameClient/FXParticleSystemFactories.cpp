// cl: /EHsc /Ireference/shims/fxparticle_link
#include "ModuleTemplate.h"

// Declared so a vector deleting destructor frees through operator delete[]
// (0x0002FD80) as retail does; left undeclared, cl falls back to scalar delete.
void operator delete[](void *p);
#include <memory>

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

// The module factories, split out of FXParticleSystemModules.cpp for one flag.
// createTemplate allocates, so its body sits inside an unwind region and opens
// with __EH_prolog; the clone bodies in the other unit are compiled without
// exceptions and break the moment /EHsc is turned on there. Same declarations,
// different build - which is the same split the string library needed between
// /O1 and /O2.

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

// Global scope, not the FXParticleSystem namespace: retail spells the parameter
// PAVINI@@ rather than PAVINI@2@.
class INI;

namespace FXParticleSystem
{

// The draw-template destructors inline both base vptr restores in retail.
inline ModuleTemplate::~ModuleTemplate() {}

class SecondaryModuleBase
{
public:
    virtual ~SecondaryModuleBase() {}
    virtual void v1() = 0;
};

struct FXCoord3D
{
    float x;
    float y;
    float z;
};

class EmissionVolumeInfo : public ::Snapshot
{
public:
    virtual ~EmissionVolumeInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(Xfer &xfer);

    bool m_flag;
};

class SphereEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    float m_radius;
};

class BoxEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    FXCoord3D m_half;
};

class LineEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    FXCoord3D m_start;
    FXCoord3D m_end;
};

class CylinderEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
    float m_radius;
    float m_length;
    float m_radius2;
    FXCoord3D m_axis;
};

class EmissionVelocityInfo
{
public:
    virtual ~EmissionVelocityInfo();
    virtual void v1() = 0;
};

// Sizes come from the clone bodies, which push the wrapper's size to operator
// new: 24 for the spherical and hemispherical velocities, 36 for the
// cylindrical and outward ones, 48 for the ortho one.
class SphericalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    FXCoord3D m_unknown04;
};

class HemisphericalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    FXCoord3D m_unknown04;
};

class CylindricalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
};

class OutwardEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
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


// Retail clone/createTemplate immediates put the complete GPU- and
// RenderObject-draw wrappers at 0x1c and 0x48 bytes. Their first two bases are
// 4 bytes each, so the info subobjects are 0x14 and 0x40 bytes respectively;
// their otherwise opaque payloads are kept as padding. The remaining info
// classes are sized off the same clone bodies: 4 bytes for vtable-only ones,
// 36 for the default physics info, 48 for the lightning draw and terrain fire
// ones, 72 for the category 7 default, 104 for the default update info, 132
// and 144 for the default alpha and color ones, 140 for the lightning emission
// info and 152 for the render object update info.
struct FXKeyframe
{
    FXCoord3D m_value;
    unsigned int m_frame;
};

#define FX_VTABLE_ONLY_INFO(NAME)                                                                      class NAME                                                                                         {                                                                                                  public:                                                                                                virtual ~NAME();                                                                                   virtual void v1() = 0;                                                                         };

FX_VTABLE_ONLY_INFO(DefaultDrawModuleInfo)
class QuadDrawModuleInfo
{
public:
    virtual ~QuadDrawModuleInfo();
    virtual void v1() = 0;
    virtual const char *GetSnapshotName();
};
class StreakDrawModuleInfo
{
public:
    virtual ~StreakDrawModuleInfo();
    virtual void v1() = 0;
    virtual const char *GetSnapshotName();
};
class ButterflyDrawModuleInfo
{
public:
    virtual ~ButterflyDrawModuleInfo();
    virtual void v1() = 0;
    virtual const char *GetSnapshotName();
};

class RenderObjectDrawModuleInfo
{
public:
    virtual ~RenderObjectDrawModuleInfo();
    virtual void v1() = 0;

    unsigned int m_unknown04[15];
};

class GpuDrawModuleInfo
{
public:
    virtual ~GpuDrawModuleInfo();
    virtual void v1() = 0;

    unsigned int m_unknown04[4];
};

typedef char RenderObjectDrawModuleInfo_size[
    (sizeof(RenderObjectDrawModuleInfo) == 0x40) ? 1 : -1];
typedef char GpuDrawModuleInfo_size[(sizeof(GpuDrawModuleInfo) == 0x14) ? 1 : -1];

// Category 8 (LifeEvent and TerrainCollision) puts its info's vtable at 0x0C
// rather than 0x08: the first base is CategoryModuleTemplate<8>, whose third
// base is the two-flag EventModuleInfo at 0x08. The infos themselves carry
// data, sized off their copy-ctor thunks: 24 for LifeEvent (string + 12B
// values + event type) and 28 for TerrainCollision (string + 12B time + flag
// + cached), giving wrappers of 0x24 and 0x28.
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
class CategoryModuleTemplate<6> : public ModuleTemplate, public SecondaryModuleBase
{
public:
    CategoryModuleTemplate();
    CategoryModuleTemplate(const CategoryModuleTemplate<6> &that);
};

template <>
class CategoryModuleTemplate<8> : public ModuleTemplate, public SecondaryModuleBase,
                                  public EventModuleInfo
{
public:
    CategoryModuleTemplate();
    CategoryModuleTemplate(const CategoryModuleTemplate &that);
};

class LifeEventModuleInfo
{
public:
    virtual ~LifeEventModuleInfo();
    virtual void v1() = 0;

    void *m_name;
    unsigned int m_values[3];
    unsigned int m_eventType;
};

class TerrainCollisionModuleInfo
{
public:
    virtual ~TerrainCollisionModuleInfo();
    virtual void v1() = 0;

    void *m_eventName;
    unsigned int m_eventTime[3];
    bool m_flag;
    unsigned int m_cached;
};

class DefaultPhysicsModuleInfo
{
public:
    virtual ~DefaultPhysicsModuleInfo();
    virtual void v1() = 0;

    FXCoord3D m_unknown04;
    float m_unknown10;
    FXCoord3D m_unknown14;
    bool m_unknown20;
    bool m_unknown21;
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
    float m_unknown40[2];
};
// 72 bytes, as the comment above records: the category-7 default wrapper's
// createTemplate (0x003AC757 / 0x003AC7A5) allocates 0x50 = two 4-byte bases
// plus this info.
typedef char DefaultCategory7ModuleInfo_size[(sizeof(DefaultCategory7ModuleInfo) == 72) ? 1 : -1];

class DefaultUpdateModuleInfo
{
public:
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
};

class DefaultAlphaModuleInfo
{
public:
    virtual ~DefaultAlphaModuleInfo();
    virtual void v1() = 0;

    FXKeyframe m_keys[8];
};

class DefaultColorModuleInfo
{
public:
    virtual ~DefaultColorModuleInfo();
    virtual void v1() = 0;

    FXKeyframe m_keys[8];
    FXCoord3D m_unknown84;
};

class LightningDrawModuleInfo
{
public:
    virtual ~LightningDrawModuleInfo();
    virtual void v1() = 0;

    FXCoord3D m_unknown04;
    FXCoord3D m_unknown10;
    FXCoord3D m_unknown1C;
    float m_unknown28;
    bool m_unknown2C;
};

class RenderObjectUpdateModuleInfo
{
public:
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
};

class TerrainFireEmissionInfo : public EmissionVolumeInfo
{
public:
    FXCoord3D m_unknown08;
    FXCoord3D m_unknown14;
    FXCoord3D m_unknown20;
    float m_unknown2C;
};

class LightningEmissionInfo : public EmissionVolumeInfo
{
public:
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

#define FX_MODULE_TEMPLATE(NAME, INFO)                                                             \
    class NAME : public ModuleTemplate, public SecondaryModuleBase, public INFO                    \
    {                                                                                              \
    public:                                                                                        \
        NAME();                                                                                    \
        virtual ~NAME();                                                                           \
        NAME(const NAME &that);                                                                    \
                                                                                                   \
        NAME &operator=(const NAME &that);                                                         \
                                                                                                   \
        void parse(INI *ini);                                      \
    };

FX_MODULE_TEMPLATE(PointEmissionVolumeModuleTemplate, EmissionVolumeInfo)
FX_MODULE_TEMPLATE(SphereEmissionVolumeModuleTemplate, SphereEmissionVolumeInfo)
FX_MODULE_TEMPLATE(BoxEmissionVolumeModuleTemplate, BoxEmissionVolumeInfo)
FX_MODULE_TEMPLATE(LineEmissionVolumeModuleTemplate, LineEmissionVolumeInfo)
FX_MODULE_TEMPLATE(CylinderEmissionVolumeModuleTemplate, CylinderEmissionVolumeInfo)
FX_MODULE_TEMPLATE(SphericalEmissionVelocityModuleTemplate, SphericalEmissionVelocityInfo)
class HemisphericalEmissionVelocityModuleTemplate : public ModuleTemplate,
    public SecondaryModuleBase, public HemisphericalEmissionVelocityInfo
{
public:
    HemisphericalEmissionVelocityModuleTemplate();
    HemisphericalEmissionVelocityModuleTemplate(const HemisphericalEmissionVelocityModuleTemplate &);
    HemisphericalEmissionVelocityModuleTemplate &operator=(const HemisphericalEmissionVelocityModuleTemplate &);
    void parse(INI *ini);
};
FX_MODULE_TEMPLATE(CylindricalEmissionVelocityModuleTemplate, CylindricalEmissionVelocityInfo)
FX_MODULE_TEMPLATE(OutwardEmissionVelocityModuleTemplate, OutwardEmissionVelocityInfo)
FX_MODULE_TEMPLATE(OrthoEmissionVelocityModuleTemplate, OrthoEmissionVelocityInfo)
FX_MODULE_TEMPLATE(LightningDrawModuleTemplate, LightningDrawModuleInfo)
FX_MODULE_TEMPLATE(TerrainFireEmissionModuleTemplate, TerrainFireEmissionInfo)
FX_MODULE_TEMPLATE(LightningEmissionModuleTemplate, LightningEmissionInfo)
FX_MODULE_TEMPLATE(RenderObjectUpdateModuleTemplate, RenderObjectUpdateModuleInfo)

#define FX_DRAW_MODULE_TEMPLATE(NAME, INFO)                                                        \
    /* Retail derives draw templates through CategoryModuleTemplate<6>; keeping \
       that intermediate base is required for its destructor EH-state shape. */ \
    class NAME : public CategoryModuleTemplate<6>, public INFO                                     \
    {                                                                                              \
    public:                                                                                        \
        NAME();                                                                                    \
        NAME(const NAME &that);                                                                    \
                                                                                                   \
        NAME &operator=(const NAME &that);                                                         \
                                                                                                   \
        void parse(INI *ini);                                                                      \
    };

FX_DRAW_MODULE_TEMPLATE(RenderObjectDrawModuleTemplate, RenderObjectDrawModuleInfo)
FX_DRAW_MODULE_TEMPLATE(GpuDrawModuleTemplate, GpuDrawModuleInfo)

FX_MODULE_TEMPLATE(QuadDrawModuleTemplate, QuadDrawModuleInfo)
FX_MODULE_TEMPLATE(StreakDrawModuleTemplate, StreakDrawModuleInfo)
FX_MODULE_TEMPLATE(ButterflyDrawModuleTemplate, ButterflyDrawModuleInfo)

#define FX_EVENT_MODULE_TEMPLATE(NAME, INFO)                                                        class NAME : public CategoryModuleTemplate<8>, public INFO                                     {                                                                                                  public:                                                                                            NAME();                                                                                        NAME(const NAME &that);                                                                        NAME &operator=(const NAME &that);                                                             void parse(INI *ini);                                                                      };

FX_EVENT_MODULE_TEMPLATE(LifeEventModuleTemplate, LifeEventModuleInfo)
FX_EVENT_MODULE_TEMPLATE(TerrainCollisionModuleTemplate, TerrainCollisionModuleInfo)

template <int CATEGORY>
class DefaultParticleModule;

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

template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE,
    class TEMPLATE, class DEFAULT>
class ModuleTag
{
public:
    enum { IS_DEFAULT = 0 };

    typedef TEMPLATE TemplateType;
    typedef CategoryModuleClass<CATEGORY> ClassBase;

    // Static REFERENCES, not accessors: MSVC 7.1 gives each one a hidden
    // pointer global, so reading them is a load of that pointer and a load
    // through it - which is the double indirection retail does here.
    static const char *const &s_key;
    static const char *const &s_name;
};

template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE,
    class TEMPLATE, class DEFAULT>
const char *const &ModuleTag<CATEGORY, KEY, NAME, MODULE, TEMPLATE, DEFAULT>::s_key = KEY;

template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE,
    class TEMPLATE, class DEFAULT>
const char *const &ModuleTag<CATEGORY, KEY, NAME, MODULE, TEMPLATE, DEFAULT>::s_name = NAME;

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

template <class TAG>
typename TAG::TemplateType *ConcreteModuleTemplate<TAG>::clone() const
{
    return new ConcreteModuleTemplate<TAG>(*this);
}

// These clones bind to the byte-exact wrapper definitions in the module unit.
extern const char *const CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME;
class CylindricalEmissionVelocityModule;
template <> CylindricalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4> > >::clone() const;
extern const char *const HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME;
class HemisphericalEmissionVelocityModule;
template <> HemisphericalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4> > >::clone() const;
extern const char *const OUTWARD_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const OUTWARD_EMISSION_VELOCITY_MODULE_NAME;
class OutwardEmissionVelocityModule;
template <> OutwardEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4> > >::clone() const;
extern const char *const SPHERICAL_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const SPHERICAL_EMISSION_VELOCITY_MODULE_NAME;
class SphericalEmissionVelocityModule;
template <> SphericalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4> > >::clone() const;
extern const char *const LIGHTNING_DRAW_MODULE_KEY;
extern const char *const LIGHTNING_DRAW_MODULE_NAME;
class LightningDrawModule;
template <> LightningDrawModuleTemplate *ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6> > >::clone() const;
extern const char *const TERRAIN_FIRE_EMISSION_MODULE_KEY;
extern const char *const TERRAIN_FIRE_EMISSION_MODULE_NAME;
class TerrainFireEmissionModule;
template <> TerrainFireEmissionModuleTemplate *ConcreteModuleTemplate<ModuleTag<5, TERRAIN_FIRE_EMISSION_MODULE_KEY, TERRAIN_FIRE_EMISSION_MODULE_NAME, TerrainFireEmissionModule, TerrainFireEmissionModuleTemplate, DefaultParticleModule<5> > >::clone() const;
extern const char *const LIGHTNING_EMISSION_MODULE_KEY;
extern const char *const LIGHTNING_EMISSION_MODULE_NAME;
class LightningEmissionModule;
template <> LightningEmissionModuleTemplate *ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5> > >::clone() const;
extern const char *const RENDEROBJECT_UPDATE_MODULE_KEY;
extern const char *const RENDEROBJECT_UPDATE_MODULE_NAME;
class RenderObjectUpdateModule;
class RenderObjectParticleUpdateModule;
template <> RenderObjectUpdateModuleTemplate *ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule > >::clone() const;

template <> RenderObjectUpdateModuleTemplate *ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, DefaultParticleModule<2> > >::clone() const;

// The module class that builds them. createTemplate is one operator new for the
// wrapper's size and a tail jump into its default constructor.
template <class TAG>
class ConcreteModuleClass : public TAG::ClassBase
{
public:
    virtual typename TAG::TemplateType *createTemplate() const;
    virtual typename TAG::TemplateType *createTemplate(INI *ini) const;

private:
    // Private, and its only caller is the class's own single instance - which is
    // how a self-registering singleton is written, and the only way a private
    // constructor gets called at all.
    ConcreteModuleClass();

    static ConcreteModuleClass<TAG> s_instance;
};

template <class TAG>
ConcreteModuleClass<TAG> ConcreteModuleClass<TAG>::s_instance;

template <class TAG>
ConcreteModuleClass<TAG>::ConcreteModuleClass()
    : TAG::ClassBase(TAG::IS_DEFAULT != 0, TAG::s_key, TAG::s_name)
{
}

template <class TAG>
typename TAG::TemplateType *ConcreteModuleClass<TAG>::createTemplate() const
{
    return new ConcreteModuleTemplate<TAG>();
}

// The INI-taking overload: allocate inside an auto_ptr, then hand the block
// straight to the module template's own parser. BFME1's bulk file proves the
// auto_ptr shape (std::auto_ptr<T> moduleTemplate(new ...); get()->parse;
// release); the holder is what keeps the parse call inside a second unwind
// region (state 1) and emits the extra mov [ebp-0x10],esi store. 0x003AC857
// is the TerrainCollision slot-0 (vslot of 0x0081BEB8, ctor 0x003A8826,
// parse 0x00564497, push 0x28).
template <class TAG>
typename TAG::TemplateType *ConcreteModuleClass<TAG>::createTemplate(INI *ini) const
{
    std::auto_ptr<ConcreteModuleTemplate<TAG> > moduleTemplate(
        new ConcreteModuleTemplate<TAG>());

    moduleTemplate.get()->parse(ini);

    return moduleTemplate.release();
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
    extern MOD##Concrete g_##MOD##Concrete;                                                       \
    template class ConcreteModuleClass<MOD##Tag>;                                                                                                                                                       extern MOD##Tag &(MOD##Tag::*g_##MOD##TagAssign)(const MOD##Tag &);

// The emission-volume wrappers' INI createTemplate (0x003AB3D5 and the four
// FX_WRAPPER_NOTHROW_CTOR ones after it) open no unwind state around the new
// and the wrapper constructor call - only around parse - which is what VC7.1
// emits when the constructor is declared not to throw. The throw() is chosen
// to reproduce that codegen; no reference source shows it.
#define FX_WRAPPER_NOTHROW_CTOR(CATEGORY, KEY, MOD, TMPL)                                                      \
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
    extern MOD##Concrete g_##MOD##Concrete;                                                       \
    template <> MOD##Concrete::ConcreteModuleTemplate() throw();                                  \
    template class ConcreteModuleClass<MOD##Tag>;                                                                                                                                                       extern MOD##Tag &(MOD##Tag::*g_##MOD##TagAssign)(const MOD##Tag &);

// The point volume's tag is a plain struct rather than a ModuleTag
// instantiation - the U rather than V in the decorated name is what says so.
extern const char *const POINT_EMISSION_VOLUME_MODULE_KEY;
extern const char *const POINT_EMISSION_VOLUME_MODULE_NAME;

struct PointEmissionVolumeModuleTag
{
    enum { IS_DEFAULT = 1 };

    typedef PointEmissionVolumeModuleTemplate TemplateType;
    typedef CategoryModuleClass<5> ClassBase;

    static const char *const &s_key;
    static const char *const &s_name;
};

// LINK-DUP: s_key/s_name owned by FXParticleSystemModules.cpp; declare only here.

typedef ConcreteModuleTemplate<PointEmissionVolumeModuleTag> PointEmissionVolumeModuleConcrete;
typedef ConcreteModuleClass<PointEmissionVolumeModuleTag> PointEmissionVolumeModuleClassConcrete;
template <> PointEmissionVolumeModuleConcrete::ConcreteModuleTemplate() throw();

extern PointEmissionVolumeModuleConcrete g_pointEmissionVolumeModuleConcrete;
template class ConcreteModuleClass<PointEmissionVolumeModuleTag>;

FX_WRAPPER_NOTHROW_CTOR(5, SPHERE_EMISSION_VOLUME, SphereEmissionVolumeModule,
    SphereEmissionVolumeModuleTemplate)
FX_WRAPPER_NOTHROW_CTOR(5, BOX_EMISSION_VOLUME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate)

// Retail's vtable slot 0 for these wrappers is the vector deleting destructor, and
// its body uses the eh vector destructor iterator, so an EH unit emitted it: Point
// 0x003A9057 (vtable 0x00C1C0A0), Sphere 0x003A91E3 (0x00C1C10C) and Box
// 0x003A9152 (0x00C1C0E8). cl 7.1 emits it in a unit that array-news the class;
// their constructors stay out of line here, so this unit emits no competing copy
// of the vtables (FXParticleSystemModules.cpp owns them and the W7 thunks).
// ?<bfmeVectorDeleteAnchorEmissionVolumes> absent-from-retail
void bfmeVectorDeleteAnchorEmissionVolumes()
{
    new PointEmissionVolumeModuleConcrete[2];
    new SphereEmissionVolumeModuleConcrete[2];
    new BoxEmissionVolumeModuleConcrete[2];
}
FX_WRAPPER_NOTHROW_CTOR(5, LINE_EMISSION_VOLUME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate)
FX_WRAPPER_NOTHROW_CTOR(5, CYLINDER_EMISSION_VOLUME, CylinderEmissionVolumeModule,
    CylinderEmissionVolumeModuleTemplate)

FX_WRAPPER(4, SPHERICAL_EMISSION_VELOCITY, SphericalEmissionVelocityModule,
    SphericalEmissionVelocityModuleTemplate)
FX_WRAPPER(4, HEMISPHERICAL_EMISSION_VELOCITY, HemisphericalEmissionVelocityModule,
    HemisphericalEmissionVelocityModuleTemplate)
FX_WRAPPER(4, CYLINDRICAL_EMISSION_VELOCITY, CylindricalEmissionVelocityModule,
    CylindricalEmissionVelocityModuleTemplate)
FX_WRAPPER(4, OUTWARD_EMISSION_VELOCITY, OutwardEmissionVelocityModule,
    OutwardEmissionVelocityModuleTemplate)

// The ortho velocity tag is the other plain struct.
extern const char *const ORTHO_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const ORTHO_EMISSION_VELOCITY_MODULE_NAME;

struct OrthoEmissionVelocityModuleTag
{
    enum { IS_DEFAULT = 1 };

    typedef OrthoEmissionVelocityModuleTemplate TemplateType;
    typedef CategoryModuleClass<4> ClassBase;

    static const char *const &s_key;
    static const char *const &s_name;
};

// LINK-DUP: s_key/s_name owned by FXParticleSystemModules.cpp; declare only here.

typedef ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> OrthoEmissionVelocityModuleConcrete;
typedef ConcreteModuleClass<OrthoEmissionVelocityModuleTag>
    OrthoEmissionVelocityModuleClassConcrete;

template <> OrthoEmissionVelocityModuleTemplate *OrthoEmissionVelocityModuleConcrete::clone() const;

extern OrthoEmissionVelocityModuleConcrete g_orthoEmissionVelocityModuleConcrete;
template class ConcreteModuleClass<OrthoEmissionVelocityModuleTag>;

// The per-category default templates, each over the info its own category uses.
#define FX_DEFAULT_TEMPLATE(CATEGORY, INFO)                                                            template <>                                                                                        class DefaultModuleTemplate<CATEGORY> : public ModuleTemplate, public SecondaryModuleBase,                                                 public INFO                                                {                                                                                                  public:                                                                                                DefaultModuleTemplate();                                                                           DefaultModuleTemplate(const DefaultModuleTemplate<CATEGORY> &that); virtual ~DefaultModuleTemplate();                                                                                                                                   void parse(INI *ini);                                                                          };

template <int CATEGORY>
class DefaultModuleTemplate;

FX_DEFAULT_TEMPLATE(0, DefaultColorModuleInfo)
FX_DEFAULT_TEMPLATE(1, DefaultAlphaModuleInfo)
FX_DEFAULT_TEMPLATE(2, DefaultUpdateModuleInfo)
FX_DEFAULT_TEMPLATE(3, DefaultPhysicsModuleInfo)
FX_DEFAULT_TEMPLATE(6, DefaultDrawModuleInfo)
class WindModuleInfo
{
public:
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
};

template <>
class CategoryModuleTemplate<7> : public ModuleTemplate, public SecondaryModuleBase,
                                  public WindModuleInfo
{
public:
    CategoryModuleTemplate();
    CategoryModuleTemplate(const CategoryModuleTemplate &that);
    virtual ~CategoryModuleTemplate();
};


template <>
class DefaultModuleTemplate<7> : public CategoryModuleTemplate<7>
{
public:
    DefaultModuleTemplate();
    DefaultModuleTemplate(const DefaultModuleTemplate<7> &that);
    void parse(INI *ini);
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
class DefaultModuleTag
{
public:
    // The default tag of a category, and the one whose registration flag is set:
    // its key and name come from the pair of accessors in
    // FXParticleSystemDefaults.cpp rather than from a string literal.
    enum { IS_DEFAULT = 1 };

    typedef DefaultModuleTemplate<CATEGORY> TemplateType;
    typedef CategoryModuleClass<CATEGORY> ClassBase;

    static const char *const &s_key;
    static const char *const &s_name;
};

template <int CATEGORY>
const char *const &DefaultModuleTag<CATEGORY>::s_key = DefaultModuleKey<CATEGORY>::VALUE;

template <int CATEGORY>
const char *const &DefaultModuleTag<CATEGORY>::s_name = DefaultModuleName<CATEGORY>::VALUE;

#define FX_DEFAULT_WRAPPER(CATEGORY)                                                                   typedef ConcreteModuleTemplate<DefaultModuleTag<CATEGORY> > DefaultConcrete##CATEGORY;                                                                                                                template <> DefaultModuleTemplate<CATEGORY> *DefaultConcrete##CATEGORY::clone() const; extern DefaultConcrete##CATEGORY g_defaultConcrete##CATEGORY;                                                                                                                                                              template class ConcreteModuleClass<DefaultModuleTag<CATEGORY> >;

FX_DEFAULT_WRAPPER(0)
FX_DEFAULT_WRAPPER(1)
FX_DEFAULT_WRAPPER(2)
FX_DEFAULT_WRAPPER(3)
FX_DEFAULT_WRAPPER(6)
FX_DEFAULT_WRAPPER(7)

FX_WRAPPER(6, LIGHTNING_DRAW, LightningDrawModule, LightningDrawModuleTemplate)
FX_WRAPPER(5, TERRAIN_FIRE_EMISSION, TerrainFireEmissionModule, TerrainFireEmissionModuleTemplate)
FX_WRAPPER(5, LIGHTNING_EMISSION, LightningEmissionModule, LightningEmissionModuleTemplate)
FX_WRAPPER(2, RENDEROBJECT_UPDATE, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate)

// Five tags whose sixth argument is a plain class rather than a
// DefaultParticleModule instantiation. Only the constructors are claimed from
// them; their clones carry an EH prologue and are a separate problem.
#define FX_NAMED_WRAPPER(CATEGORY, KEY, MOD, TMPL, DFLT)                                               extern const char *const KEY##_MODULE_KEY;                                                         extern const char *const KEY##_MODULE_NAME;                                                                                                                                                           class MOD;                                                                                         class DFLT;                                                                                                                                                                                           typedef ConcreteModuleTemplate<                                                                        ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL, DFLT> >                        MOD##NamedConcrete;                                                                                                                                                                               extern MOD##NamedConcrete g_##MOD##NamedConcrete;                                                                                                                                                               typedef ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL, DFLT>                     MOD##NamedTag;                                                                                                                                                                                  extern MOD##NamedTag &(MOD##NamedTag::*g_##MOD##NamedTagAssign)(const MOD##NamedTag &);

FX_NAMED_WRAPPER(2, RENDEROBJECT_UPDATE, RenderObjectUpdateModule,
    RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule)
FX_NAMED_WRAPPER(8, LIFE_EVENT, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule)
// Construction binds to the module unit; destruction and cloning are defined here.
extern const char *const TERRAIN_COLLISION_MODULE_KEY;
extern const char *const TERRAIN_COLLISION_MODULE_NAME;
class TerrainCollisionModule;
class ParticleTerrainCollisionModule;
typedef ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME,
    TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule>
    TerrainCollisionModuleNamedTag;
template <>
class __declspec(novtable) ConcreteModuleTemplate<TerrainCollisionModuleNamedTag>
    : public TerrainCollisionModuleTemplate
{
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate &that);
    virtual ~ConcreteModuleTemplate();
    virtual void v1();
    virtual TerrainCollisionModuleTemplate *clone() const;
};

ConcreteModuleTemplate<TerrainCollisionModuleNamedTag>::~ConcreteModuleTemplate() {}

TerrainCollisionModuleTemplate *ConcreteModuleTemplate<TerrainCollisionModuleNamedTag>::clone() const
{
    return new ConcreteModuleTemplate(*this);
}
FX_NAMED_WRAPPER(8, TERRAIN_COLLISION, TerrainCollisionModule, TerrainCollisionModuleTemplate,
    ParticleTerrainCollisionModule)

// LINK-DUP: RenderObjectUpdate NamedConcrete global is extern (owned elsewhere),
// but this unit owns its ??_G (0x003AA1EA). Explicitly instantiate its wrapper
// so the deleting dtor still emits without defining the global.
template <> RenderObjectUpdateModuleNamedConcrete::ConcreteModuleTemplate();
template class ConcreteModuleTemplate<RenderObjectUpdateModuleNamedTag>;
template class ConcreteModuleClass<RenderObjectUpdateModuleNamedTag>;

FX_WRAPPER(6, RENDEROBJECT_DRAW, RenderObjectDrawModule, RenderObjectDrawModuleTemplate)
FX_WRAPPER(6, GPU_DRAW, GpuDrawModule, GpuDrawModuleTemplate)
FX_WRAPPER(6, QUAD_DRAW, QuadDrawModule, QuadDrawModuleTemplate)
FX_WRAPPER(6, STREAK_DRAW, StreakDrawModule, StreakDrawModuleTemplate)
FX_WRAPPER(6, BUTTERFLY_DRAW, ButterflyDrawModule, ButterflyDrawModuleTemplate)

// LINK-DUP: only QUAD/STREAK/BUTTERFLY concretes stay defined here; the rest
// are owned by FXParticleSystemModules.cpp / FXParticleSystem.cpp (see packet).
QuadDrawModuleConcrete g_QuadDrawModuleConcrete;
QuadDrawModuleTag &(QuadDrawModuleTag::*g_QuadDrawModuleTagAssign)(const QuadDrawModuleTag &)
    = &QuadDrawModuleTag::operator=;
StreakDrawModuleConcrete g_StreakDrawModuleConcrete;
StreakDrawModuleTag &(StreakDrawModuleTag::*g_StreakDrawModuleTagAssign)(const StreakDrawModuleTag &)
    = &StreakDrawModuleTag::operator=;
ButterflyDrawModuleConcrete g_ButterflyDrawModuleConcrete;
ButterflyDrawModuleTag &(ButterflyDrawModuleTag::*g_ButterflyDrawModuleTagAssign)(
    const ButterflyDrawModuleTag &)
    = &ButterflyDrawModuleTag::operator=;

// The named-tag classes: same treatment, over the tags FX_NAMED_WRAPPER made.
// Their createTemplate bodies carry the same EH prologue as the rest of this
// unit (slot 0 is the INI-taking overload, slot 1 the plain one).
template class ConcreteModuleClass<LifeEventModuleNamedTag>;
template class ConcreteModuleClass<TerrainCollisionModuleNamedTag>;

// The wrappers' generated assignments. They forward to the module template's own
// assignment, which this unit only declares - beside the definitions MSVC 7.1
// inlines it instead.

typedef PointEmissionVolumeModuleConcrete &(PointEmissionVolumeModuleConcrete::*PointEmissionVolumeModuleConcreteAssign)(const PointEmissionVolumeModuleConcrete &);

extern PointEmissionVolumeModuleConcreteAssign g_pointEmissionVolumeModuleConcreteAssign;

typedef SphereEmissionVolumeModuleConcrete &(SphereEmissionVolumeModuleConcrete::*SphereEmissionVolumeModuleConcreteAssign)(const SphereEmissionVolumeModuleConcrete &);

extern SphereEmissionVolumeModuleConcreteAssign g_sphereEmissionVolumeModuleConcreteAssign;

typedef BoxEmissionVolumeModuleConcrete &(BoxEmissionVolumeModuleConcrete::*BoxEmissionVolumeModuleConcreteAssign)(const BoxEmissionVolumeModuleConcrete &);

extern BoxEmissionVolumeModuleConcreteAssign g_boxEmissionVolumeModuleConcreteAssign;

typedef LineEmissionVolumeModuleConcrete &(LineEmissionVolumeModuleConcrete::*LineEmissionVolumeModuleConcreteAssign)(const LineEmissionVolumeModuleConcrete &);

extern LineEmissionVolumeModuleConcreteAssign g_lineEmissionVolumeModuleConcreteAssign;

typedef CylinderEmissionVolumeModuleConcrete &(CylinderEmissionVolumeModuleConcrete::*CylinderEmissionVolumeModuleConcreteAssign)(const CylinderEmissionVolumeModuleConcrete &);

extern CylinderEmissionVolumeModuleConcreteAssign g_cylinderEmissionVolumeModuleConcreteAssign;

typedef OrthoEmissionVelocityModuleConcrete &(OrthoEmissionVelocityModuleConcrete::*OrthoEmissionVelocityModuleConcreteAssign)(const OrthoEmissionVelocityModuleConcrete &);

extern OrthoEmissionVelocityModuleConcreteAssign g_orthoEmissionVelocityModuleConcreteAssign;

typedef LightningDrawModuleConcrete &(LightningDrawModuleConcrete::*LightningDrawModuleConcreteAssign)(const LightningDrawModuleConcrete &);

extern LightningDrawModuleConcreteAssign g_lightningDrawModuleConcreteAssign;

typedef TerrainFireEmissionModuleConcrete &(TerrainFireEmissionModuleConcrete::*TerrainFireEmissionModuleConcreteAssign)(const TerrainFireEmissionModuleConcrete &);

extern TerrainFireEmissionModuleConcreteAssign g_terrainFireEmissionModuleConcreteAssign;

typedef LightningEmissionModuleConcrete &(LightningEmissionModuleConcrete::*LightningEmissionModuleConcreteAssign)(const LightningEmissionModuleConcrete &);

extern LightningEmissionModuleConcreteAssign g_lightningEmissionModuleConcreteAssign;

typedef RenderObjectUpdateModuleConcrete &(RenderObjectUpdateModuleConcrete::*RenderObjectUpdateModuleConcreteAssign)(const RenderObjectUpdateModuleConcrete &);

extern RenderObjectUpdateModuleConcreteAssign g_renderObjectUpdateModuleConcreteAssign;

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

typedef RenderObjectUpdateModuleNamedConcrete &(RenderObjectUpdateModuleNamedConcrete::*RenderObjectUpdateModuleNamedConcreteAssign)(const RenderObjectUpdateModuleNamedConcrete &);

extern RenderObjectUpdateModuleNamedConcreteAssign g_renderObjectUpdateModuleNamedConcreteAssign;

typedef LifeEventModuleNamedConcrete &(LifeEventModuleNamedConcrete::*LifeEventModuleNamedConcreteAssign)(const LifeEventModuleNamedConcrete &);

extern LifeEventModuleNamedConcreteAssign g_lifeEventModuleNamedConcreteAssign;

typedef TerrainCollisionModuleNamedConcrete &(TerrainCollisionModuleNamedConcrete::*TerrainCollisionModuleNamedConcreteAssign)(const TerrainCollisionModuleNamedConcrete &);

extern TerrainCollisionModuleNamedConcreteAssign g_terrainCollisionModuleNamedConcreteAssign;


// The alpha runtime module has four vptrs and an extent of 0xA0.
// Its copy constructor installs the same tables as the createModule result.
template <int CATEGORY>
class __declspec(novtable) DefaultModule
{
public:
    __declspec(noinline) DefaultModule(const DefaultModule &that);
    virtual DefaultModule *clone() const;

private:
    char m_storage[0x9C];
};

template <int CATEGORY>
DefaultModule<CATEGORY> *DefaultModule<CATEGORY>::clone() const
{
    return new DefaultModule<CATEGORY>(*this);
}

template class DefaultModule<1>;

}
