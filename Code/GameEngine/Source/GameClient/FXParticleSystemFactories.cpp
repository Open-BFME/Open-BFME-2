// cl: /EHsc /Ireference/shims/fxparticle_link
#include "ModuleTemplate.h"
#include "../../Include/GameClient/FXConcreteEventModuleTemplate.h"

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
#include "../../Include/GameClient/QuadDrawModuleInfo.h"
#include "../../Include/GameClient/StreakDrawModuleInfo.h"
namespace FXParticleSystem
{

// The draw-template destructors inline both base vptr restores in retail.
inline ModuleTemplate::~ModuleTemplate() {}

template <int CATEGORY>
class CategoryModuleClass;

// Retail's nested category shape (LINK-584): one pure slot, protected non-virtual destructor.
// The slot is getClass: every concrete wrapper's CategoryModuleInfo table holds its 5-byte
// getClass forwarder there (0x003AD036 for DefaultModuleTag<1>, rowed with the forwarders),
// and the overrider's covariant return needs no adjustment, so it adds no primary slot.
template <int CATEGORY_ARG>
class CategoryModuleInfo
{
public:
    virtual const CategoryModuleClass<CATEGORY_ARG> &getClass() const = 0;

protected:
    ~CategoryModuleInfo() {}
};

template <int CATEGORY_ARG>
class CategoryModuleTemplateBase : public ModuleTemplate, public CategoryModuleInfo<CATEGORY_ARG>
{
public:
    CategoryModuleTemplateBase();
    CategoryModuleTemplateBase(const CategoryModuleTemplateBase<CATEGORY_ARG> &that);
};

#define FX_CATEGORY_MODULE_TEMPLATE(NAME, INFO, CAT) \
    class NAME : public CategoryModuleTemplateBase<CAT>, public INFO \
    { \
    public: \
        NAME(); \
        virtual ~NAME(); \
        NAME(const NAME &that); \
        NAME &operator=(const NAME &that); \
        void parse(INI *ini); \
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
class ButterflyDrawModuleInfo : public ::Snapshot
{
public:
    virtual ~ButterflyDrawModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);
};

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

class TerrainCollisionModuleInfo : public ::Snapshot
{
public:
    virtual ~TerrainCollisionModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);

    void *m_eventName;
    unsigned int m_eventTime[3];
    bool m_flag;
    unsigned int m_cached;
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



#include "../../Include/Common/BfmeAccessorMacros.h"

FX_CATEGORY_MODULE_TEMPLATE(PointEmissionVolumeModuleTemplate, EmissionVolumeInfo, 5)
FX_CATEGORY_MODULE_TEMPLATE(SphereEmissionVolumeModuleTemplate, SphereEmissionVolumeInfo, 5)
FX_CATEGORY_MODULE_TEMPLATE(BoxEmissionVolumeModuleTemplate, BoxEmissionVolumeInfo, 5)
FX_CATEGORY_MODULE_TEMPLATE(LineEmissionVolumeModuleTemplate, LineEmissionVolumeInfo, 5)
FX_CATEGORY_MODULE_TEMPLATE(CylinderEmissionVolumeModuleTemplate, CylinderEmissionVolumeInfo, 5)
FX_CATEGORY_MODULE_TEMPLATE(SphericalEmissionVelocityModuleTemplate, SphericalEmissionVelocityInfo, 4)
class HemisphericalEmissionVelocityModuleTemplate : public CategoryModuleTemplateBase<4>,
    public HemisphericalEmissionVelocityInfo
{
public:
    HemisphericalEmissionVelocityModuleTemplate();
    HemisphericalEmissionVelocityModuleTemplate(const HemisphericalEmissionVelocityModuleTemplate &);
    HemisphericalEmissionVelocityModuleTemplate &operator=(const HemisphericalEmissionVelocityModuleTemplate &);
    void parse(INI *ini);
};
FX_CATEGORY_MODULE_TEMPLATE(CylindricalEmissionVelocityModuleTemplate, CylindricalEmissionVelocityInfo, 4)
FX_CATEGORY_MODULE_TEMPLATE(OutwardEmissionVelocityModuleTemplate, OutwardEmissionVelocityInfo, 4)
FX_CATEGORY_MODULE_TEMPLATE(OrthoEmissionVelocityModuleTemplate, OrthoEmissionVelocityInfo, 4)
FX_CATEGORY_MODULE_TEMPLATE(LightningDrawModuleTemplate, LightningDrawModuleInfo, 6)
FX_CATEGORY_MODULE_TEMPLATE(TerrainFireEmissionModuleTemplate, TerrainFireEmissionInfo, 5)
FX_CATEGORY_MODULE_TEMPLATE(LightningEmissionModuleTemplate, LightningEmissionInfo, 5)
FX_CATEGORY_MODULE_TEMPLATE(RenderObjectUpdateModuleTemplate, RenderObjectUpdateModuleInfo, 2)


FX_DRAW_MODULE_TEMPLATE(RenderObjectDrawModuleTemplate, RenderObjectDrawModuleInfo)
FX_DRAW_MODULE_TEMPLATE(GpuDrawModuleTemplate, GpuDrawModuleInfo)

FX_CATEGORY_MODULE_TEMPLATE(QuadDrawModuleTemplate, QuadDrawModuleInfo, 6)
FX_CATEGORY_MODULE_TEMPLATE(StreakDrawModuleTemplate, StreakDrawModuleInfo, 6)
FX_CATEGORY_MODULE_TEMPLATE(ButterflyDrawModuleTemplate, ButterflyDrawModuleInfo, 6)

class LifeEventModule;
class TerrainCollisionModule;

#define FX_EVENT_MODULE_TEMPLATE(NAME, INFO, MODULE)                                                        class NAME : public CategoryModuleTemplate<8>, public INFO                                     {                                                                                                  public:                                                                                            NAME();                                                                                        NAME(const NAME &that);                                                                        NAME &operator=(const NAME &that);                                                             void parse(INI *ini);                                                                      virtual MODULE *createModule(TrackingPtr<ParticleSystem> &system) = 0; virtual void writeINI(File &file, unsigned int indent) const; };

FX_EVENT_MODULE_TEMPLATE(LifeEventModuleTemplate, LifeEventModuleInfo, LifeEventModule)
FX_EVENT_MODULE_TEMPLATE(TerrainCollisionModuleTemplate, TerrainCollisionModuleInfo, TerrainCollisionModule)

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

template <int CATEGORY, const char *const &Key, const char *const &Name, class MODULE,
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
    static const char *const &KEY;
    static const char *const &NAME;
    static __declspec(dllimport) __forceinline const char *const &keyReference() { return KEY; }
    static __declspec(dllimport) __forceinline const char *const &nameReference() { return NAME; }
};

// KEY and NAME are declared only. Retail sets each one once, from
// FXParticleSystemModules.cpp's object (its dynamic initializers, e.g. 0x007AF6F3
// `mov [0x00E02D28], &SPHERE_EMISSION_VOLUME_MODULE_KEY`); defining them here as well
// gave this unit a second initializer per global that retail does not have.

// The module class that builds them. createTemplate is one operator new for the
// wrapper's size and a tail jump into its default constructor.
template <class TAG>
class ConcreteModuleClass : public TAG::ClassBase
{
public:
    virtual typename TAG::TemplateType *createTemplate() const;
    virtual typename TAG::TemplateType *createTemplate(INI *ini) const;

private:
    // Private. Retail builds the one instance lazily, as getInstance()'s local
    // static (0x003AB3AA for the point volume), never from a static initializer:
    // a class-static instance here ran ahead of the tag's KEY/NAME
    // initializers and read them while still null.
    ConcreteModuleClass();
};

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

// Keep the plain class tag's ABI. This specialization owns only its exported references.
class PointEmissionVolumeModule;
template <> class ModuleTag<5, POINT_EMISSION_VOLUME_MODULE_KEY, POINT_EMISSION_VOLUME_MODULE_NAME,
    PointEmissionVolumeModule, PointEmissionVolumeModuleTemplate, DefaultParticleModule<5> >
{
public:
    static const char *const &KEY;
    static const char *const &NAME;
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

// The reference specialization is defined in FXParticleSystemModules.cpp.

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

// The clone binds to the byte-exact wrapper definition in the module unit. It is declared
// just before its wrapper's explicit instantiation: declaring it instantiates the wrapper
// template, and with it (through getClass's covariant return) the wrapper class, so this keeps
// the tags' KEY/NAME initializers in wrapper order.
extern const char *const SPHERICAL_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const SPHERICAL_EMISSION_VELOCITY_MODULE_NAME;
class SphericalEmissionVelocityModule;
template <> SphericalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4> > >::clone() const;
FX_WRAPPER(4, SPHERICAL_EMISSION_VELOCITY, SphericalEmissionVelocityModule,
    SphericalEmissionVelocityModuleTemplate)
// Its clone binds to the module unit's definition, declared here as above.
extern const char *const HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME;
class HemisphericalEmissionVelocityModule;
template <> HemisphericalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4> > >::clone() const;
FX_WRAPPER(4, HEMISPHERICAL_EMISSION_VELOCITY, HemisphericalEmissionVelocityModule,
    HemisphericalEmissionVelocityModuleTemplate)
// Its clone binds to the module unit's definition, declared here as above.
extern const char *const CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME;
class CylindricalEmissionVelocityModule;
template <> CylindricalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4> > >::clone() const;
FX_WRAPPER(4, CYLINDRICAL_EMISSION_VELOCITY, CylindricalEmissionVelocityModule,
    CylindricalEmissionVelocityModuleTemplate)
// Its clone binds to the module unit's definition, declared here as above.
extern const char *const OUTWARD_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const OUTWARD_EMISSION_VELOCITY_MODULE_NAME;
class OutwardEmissionVelocityModule;
template <> OutwardEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4> > >::clone() const;
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

// The reference specialization is defined in FXParticleSystemModules.cpp.

typedef ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> OrthoEmissionVelocityModuleConcrete;
typedef ConcreteModuleClass<OrthoEmissionVelocityModuleTag>
    OrthoEmissionVelocityModuleClassConcrete;

template <> OrthoEmissionVelocityModuleTemplate *OrthoEmissionVelocityModuleConcrete::clone() const;

extern OrthoEmissionVelocityModuleConcrete g_orthoEmissionVelocityModuleConcrete;
template class ConcreteModuleClass<OrthoEmissionVelocityModuleTag>;

// The per-category default templates, each over the info its own category uses.
#define FX_DEFAULT_TEMPLATE(CATEGORY, INFO)                                                            template <>                                                                                        class DefaultModuleTemplate<CATEGORY> : public CategoryModuleTemplateBase<CATEGORY>,                                                 public INFO                                                {                                                                                                  public:                                                                                                DefaultModuleTemplate();                                                                           DefaultModuleTemplate(const DefaultModuleTemplate<CATEGORY> &that); virtual ~DefaultModuleTemplate();                                                                                                                                   void parse(INI *ini);                                                                          };

template <int CATEGORY>
class DefaultModuleTemplate;

FX_DEFAULT_TEMPLATE(0, DefaultColorModuleInfo)
FX_DEFAULT_TEMPLATE(1, DefaultAlphaModuleInfo)
FX_DEFAULT_TEMPLATE(2, DefaultUpdateModuleInfo)
FX_DEFAULT_TEMPLATE(3, DefaultPhysicsModuleInfo)
FX_DEFAULT_TEMPLATE(6, DefaultDrawModuleInfo)

template <>
class CategoryModuleTemplate<7> : public CategoryModuleTemplateBase<7>,
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

#define FX_DEFAULT_WRAPPER(CATEGORY)                                                                   typedef ConcreteModuleTemplate<DefaultModuleTag<CATEGORY> > DefaultConcrete##CATEGORY;                                                                                                                template <> DefaultModuleTemplate<CATEGORY> *DefaultConcrete##CATEGORY::clone() const; extern DefaultConcrete##CATEGORY g_defaultConcrete##CATEGORY;                                                                                                                                                              template class ConcreteModuleClass<DefaultModuleTag<CATEGORY> >;

FX_DEFAULT_WRAPPER(0)
FX_DEFAULT_WRAPPER(1)
FX_DEFAULT_WRAPPER(2)
FX_DEFAULT_WRAPPER(3)
FX_DEFAULT_WRAPPER(6)
FX_DEFAULT_WRAPPER(7)

// Its clone binds to the module unit's definition, declared here as above.
extern const char *const LIGHTNING_DRAW_MODULE_KEY;
extern const char *const LIGHTNING_DRAW_MODULE_NAME;
class LightningDrawModule;
template <> LightningDrawModuleTemplate *ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6> > >::clone() const;
FX_WRAPPER(6, LIGHTNING_DRAW, LightningDrawModule, LightningDrawModuleTemplate)
// Its clone binds to the module unit's definition, declared here as above.
extern const char *const TERRAIN_FIRE_EMISSION_MODULE_KEY;
extern const char *const TERRAIN_FIRE_EMISSION_MODULE_NAME;
class TerrainFireEmissionModule;
template <> TerrainFireEmissionModuleTemplate *ConcreteModuleTemplate<ModuleTag<5, TERRAIN_FIRE_EMISSION_MODULE_KEY, TERRAIN_FIRE_EMISSION_MODULE_NAME, TerrainFireEmissionModule, TerrainFireEmissionModuleTemplate, DefaultParticleModule<5> > >::clone() const;
FX_WRAPPER(5, TERRAIN_FIRE_EMISSION, TerrainFireEmissionModule, TerrainFireEmissionModuleTemplate)
// Its clone binds to the module unit's definition, declared here as above.
extern const char *const LIGHTNING_EMISSION_MODULE_KEY;
extern const char *const LIGHTNING_EMISSION_MODULE_NAME;
class LightningEmissionModule;
template <> LightningEmissionModuleTemplate *ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5> > >::clone() const;
FX_WRAPPER(5, LIGHTNING_EMISSION, LightningEmissionModule, LightningEmissionModuleTemplate)
// Its clone binds to the module unit's definition, declared here as above.
extern const char *const RENDEROBJECT_UPDATE_MODULE_KEY;
extern const char *const RENDEROBJECT_UPDATE_MODULE_NAME;
class RenderObjectUpdateModule;
template <> RenderObjectUpdateModuleTemplate *ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, DefaultParticleModule<2> > >::clone() const;
// No retail wrapper has this tag (retail's update wrapper is the named one below), so no getClass
// exists for it: its constructor stays with FXParticleSystemModules.cpp's copy, and this unit emits
// no table for it.
template <> ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, DefaultParticleModule<2> > >::ConcreteModuleTemplate();
FX_WRAPPER(2, RENDEROBJECT_UPDATE, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate)

// Five tags whose sixth argument is a plain class rather than a
// DefaultParticleModule instantiation. Only the constructors are claimed from
// them; their clones carry an EH prologue and are a separate problem.
#define FX_NAMED_WRAPPER(CATEGORY, KEY, MOD, TMPL, DFLT)                                               extern const char *const KEY##_MODULE_KEY;                                                         extern const char *const KEY##_MODULE_NAME;                                                                                                                                                           class MOD;                                                                                         class DFLT;                                                                                                                                                                                           typedef ConcreteModuleTemplate<                                                                        ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL, DFLT> >                        MOD##NamedConcrete;                                                                                                                                                                               extern MOD##NamedConcrete g_##MOD##NamedConcrete;                                                                                                                                                               typedef ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL, DFLT>                     MOD##NamedTag;                                                                                                                                                                                  extern MOD##NamedTag &(MOD##NamedTag::*g_##MOD##NamedTagAssign)(const MOD##NamedTag &);

// Its clone binds to the module unit's definition, declared here as above.
extern const char *const RENDEROBJECT_UPDATE_MODULE_KEY;
extern const char *const RENDEROBJECT_UPDATE_MODULE_NAME;
class RenderObjectUpdateModule;
class RenderObjectParticleUpdateModule;
template <> RenderObjectUpdateModuleTemplate *ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule > >::clone() const;
FX_NAMED_WRAPPER(2, RENDEROBJECT_UPDATE, RenderObjectUpdateModule,
    RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule)

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

// The event wrappers follow the draw wrappers: declaring one instantiates its wrapper
// template and, through getClass, its wrapper class, so their tags' KEY/NAME initializers
// keep their place after the draw tags'.
extern const char *const LIFE_EVENT_MODULE_KEY;
extern const char *const LIFE_EVENT_MODULE_NAME;
BFME_FX_EVENT_CONCRETE(LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME)
FX_NAMED_WRAPPER(8, LIFE_EVENT, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule)
// Construction binds to the module unit; destruction and cloning are defined here. The
// specialization comes after the draw wrappers: its getClass instantiates the wrapper class,
// so this keeps the tag's KEY/NAME initializers after theirs.
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
    virtual const ConcreteModuleClass<TerrainCollisionModuleNamedTag> &getClass() const;
    virtual TerrainCollisionModuleTemplate *clone() const;
    virtual TerrainCollisionModule *createModule(TrackingPtr<ParticleSystem> &system);
};

ConcreteModuleTemplate<TerrainCollisionModuleNamedTag>::~ConcreteModuleTemplate() {}

TerrainCollisionModuleTemplate *ConcreteModuleTemplate<TerrainCollisionModuleNamedTag>::clone() const
{
    return new ConcreteModuleTemplate(*this);
}
FX_NAMED_WRAPPER(8, TERRAIN_COLLISION, TerrainCollisionModule, TerrainCollisionModuleTemplate,
    ParticleTerrainCollisionModule)

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
