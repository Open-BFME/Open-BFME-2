// cl: /O1 /EHsc /arch:SSE2

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

namespace FXParticleSystem
{

class ModuleTemplate
{
public:
    virtual ~ModuleTemplate();
    virtual void v1() = 0;
};

class SecondaryModuleBase
{
public:
    virtual ~SecondaryModuleBase();
    virtual void v1() = 0;
};

struct FXCoord3D
{
    float x;
    float y;
    float z;
};

class EmissionVolumeInfo
{
public:
    virtual ~EmissionVolumeInfo();
    virtual void v1() = 0;

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

#define FX_VTABLE_ONLY_INFO(NAME)                                                                      class NAME                                                                                         {                                                                                                  public:                                                                                                virtual ~NAME();                                                                                   virtual void v1() = 0;                                                                         };

FX_VTABLE_ONLY_INFO(DefaultDrawModuleInfo)
FX_VTABLE_ONLY_INFO(RenderObjectDrawModuleInfo)
FX_VTABLE_ONLY_INFO(GpuDrawModuleInfo)
FX_VTABLE_ONLY_INFO(LifeEventModuleInfo)
// TerrainCollisionModuleTemplate puts its info's vtable at 0x0C rather than
// 0x08, so there is a four-byte base or member between the secondary base and
// the info that the rest of the family has not got. Until that is identified
// this info stays declared and its wrapper's constructors stay unclaimed.
FX_VTABLE_ONLY_INFO(TerrainCollisionModuleInfo)

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
    FXCoord3D m_unknown40;
};

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
        NAME(const NAME &that);                                                                    \
                                                                                                   \
        NAME &operator=(const NAME &that);                                                         \
    };

FX_MODULE_TEMPLATE(PointEmissionVolumeModuleTemplate, EmissionVolumeInfo)
FX_MODULE_TEMPLATE(SphereEmissionVolumeModuleTemplate, SphereEmissionVolumeInfo)
FX_MODULE_TEMPLATE(BoxEmissionVolumeModuleTemplate, BoxEmissionVolumeInfo)
FX_MODULE_TEMPLATE(LineEmissionVolumeModuleTemplate, LineEmissionVolumeInfo)
FX_MODULE_TEMPLATE(CylinderEmissionVolumeModuleTemplate, CylinderEmissionVolumeInfo)
FX_MODULE_TEMPLATE(SphericalEmissionVelocityModuleTemplate, SphericalEmissionVelocityInfo)
FX_MODULE_TEMPLATE(HemisphericalEmissionVelocityModuleTemplate, HemisphericalEmissionVelocityInfo)
FX_MODULE_TEMPLATE(CylindricalEmissionVelocityModuleTemplate, CylindricalEmissionVelocityInfo)
FX_MODULE_TEMPLATE(OutwardEmissionVelocityModuleTemplate, OutwardEmissionVelocityInfo)
FX_MODULE_TEMPLATE(OrthoEmissionVelocityModuleTemplate, OrthoEmissionVelocityInfo)
FX_MODULE_TEMPLATE(LightningDrawModuleTemplate, LightningDrawModuleInfo)
FX_MODULE_TEMPLATE(TerrainFireEmissionModuleTemplate, TerrainFireEmissionInfo)
FX_MODULE_TEMPLATE(LightningEmissionModuleTemplate, LightningEmissionInfo)
FX_MODULE_TEMPLATE(RenderObjectUpdateModuleTemplate, RenderObjectUpdateModuleInfo)
FX_MODULE_TEMPLATE(RenderObjectDrawModuleTemplate, RenderObjectDrawModuleInfo)
FX_MODULE_TEMPLATE(GpuDrawModuleTemplate, GpuDrawModuleInfo)
FX_MODULE_TEMPLATE(LifeEventModuleTemplate, LifeEventModuleInfo)
FX_MODULE_TEMPLATE(TerrainCollisionModuleTemplate, TerrainCollisionModuleInfo)

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
    virtual void v1() = 0;
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

// The module class that builds them. createTemplate is one operator new for the
// wrapper's size and a tail jump into its default constructor.
class INI;

template <class TAG>
class ConcreteModuleClass : public TAG::ClassBase
{
public:
    virtual typename TAG::TemplateType *createTemplate() const;
    virtual void v1();

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
void ConcreteModuleClass<TAG>::v1()
{
}

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
    MOD##Concrete g_##MOD##Concrete;                                                              \
    template class ConcreteModuleClass<MOD##Tag>;                                                                                                                                                       MOD##Tag &(MOD##Tag::*g_##MOD##TagAssign)(const MOD##Tag &) = &MOD##Tag::operator=;

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

const char *const &PointEmissionVolumeModuleTag::s_key = POINT_EMISSION_VOLUME_MODULE_KEY;
const char *const &PointEmissionVolumeModuleTag::s_name = POINT_EMISSION_VOLUME_MODULE_NAME;

typedef ConcreteModuleTemplate<PointEmissionVolumeModuleTag> PointEmissionVolumeModuleConcrete;
typedef ConcreteModuleClass<PointEmissionVolumeModuleTag> PointEmissionVolumeModuleClassConcrete;

PointEmissionVolumeModuleConcrete g_pointEmissionVolumeModuleConcrete;
template class ConcreteModuleClass<PointEmissionVolumeModuleTag>;

FX_WRAPPER(5, SPHERE_EMISSION_VOLUME, SphereEmissionVolumeModule,
    SphereEmissionVolumeModuleTemplate)
FX_WRAPPER(5, BOX_EMISSION_VOLUME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate)
FX_WRAPPER(5, LINE_EMISSION_VOLUME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate)
FX_WRAPPER(5, CYLINDER_EMISSION_VOLUME, CylinderEmissionVolumeModule,
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

const char *const &OrthoEmissionVelocityModuleTag::s_key = ORTHO_EMISSION_VELOCITY_MODULE_KEY;
const char *const &OrthoEmissionVelocityModuleTag::s_name = ORTHO_EMISSION_VELOCITY_MODULE_NAME;

typedef ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> OrthoEmissionVelocityModuleConcrete;
typedef ConcreteModuleClass<OrthoEmissionVelocityModuleTag>
    OrthoEmissionVelocityModuleClassConcrete;

OrthoEmissionVelocityModuleConcrete g_orthoEmissionVelocityModuleConcrete;
template class ConcreteModuleClass<OrthoEmissionVelocityModuleTag>;

// The per-category default templates, each over the info its own category uses.
#define FX_DEFAULT_TEMPLATE(CATEGORY, INFO)                                                            template <>                                                                                        class DefaultModuleTemplate<CATEGORY> : public ModuleTemplate, public SecondaryModuleBase,                                                 public INFO                                                {                                                                                                  public:                                                                                                DefaultModuleTemplate();                                                                           DefaultModuleTemplate(const DefaultModuleTemplate<CATEGORY> &that);                            };

template <int CATEGORY>
class DefaultModuleTemplate;

FX_DEFAULT_TEMPLATE(0, DefaultColorModuleInfo)
FX_DEFAULT_TEMPLATE(1, DefaultAlphaModuleInfo)
FX_DEFAULT_TEMPLATE(2, DefaultUpdateModuleInfo)
FX_DEFAULT_TEMPLATE(3, DefaultPhysicsModuleInfo)
FX_DEFAULT_TEMPLATE(6, DefaultDrawModuleInfo)
FX_DEFAULT_TEMPLATE(7, DefaultCategory7ModuleInfo)

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

#define FX_DEFAULT_WRAPPER(CATEGORY)                                                                   typedef ConcreteModuleTemplate<DefaultModuleTag<CATEGORY> > DefaultConcrete##CATEGORY;                                                                                                                DefaultConcrete##CATEGORY g_defaultConcrete##CATEGORY;                                                                                                                                                              template class ConcreteModuleClass<DefaultModuleTag<CATEGORY> >;

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
#define FX_NAMED_WRAPPER(CATEGORY, KEY, MOD, TMPL, DFLT)                                               extern const char *const KEY##_MODULE_KEY;                                                         extern const char *const KEY##_MODULE_NAME;                                                                                                                                                           class MOD;                                                                                         class DFLT;                                                                                                                                                                                           typedef ConcreteModuleTemplate<                                                                        ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL, DFLT> >                        MOD##NamedConcrete;                                                                                                                                                                               MOD##NamedConcrete g_##MOD##NamedConcrete;                                                                                                                                                               typedef ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, TMPL, DFLT>                     MOD##NamedTag;                                                                                                                                                                                  MOD##NamedTag &(MOD##NamedTag::*g_##MOD##NamedTagAssign)(const MOD##NamedTag &) =                     &MOD##NamedTag::operator=;

FX_NAMED_WRAPPER(2, RENDEROBJECT_UPDATE, RenderObjectUpdateModule,
    RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule)
FX_NAMED_WRAPPER(8, LIFE_EVENT, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule)
FX_NAMED_WRAPPER(8, TERRAIN_COLLISION, TerrainCollisionModule, TerrainCollisionModuleTemplate,
    ParticleTerrainCollisionModule)

FX_WRAPPER(6, RENDEROBJECT_DRAW, RenderObjectDrawModule, RenderObjectDrawModuleTemplate)
FX_WRAPPER(6, GPU_DRAW, GpuDrawModule, GpuDrawModuleTemplate)

// The wrappers' generated assignments. They forward to the module template's own
// assignment, which this unit only declares - beside the definitions MSVC 7.1
// inlines it instead.

typedef PointEmissionVolumeModuleConcrete &(PointEmissionVolumeModuleConcrete::*PointEmissionVolumeModuleConcreteAssign)(const PointEmissionVolumeModuleConcrete &);

PointEmissionVolumeModuleConcreteAssign g_pointEmissionVolumeModuleConcreteAssign = &PointEmissionVolumeModuleConcrete::operator=;

typedef SphereEmissionVolumeModuleConcrete &(SphereEmissionVolumeModuleConcrete::*SphereEmissionVolumeModuleConcreteAssign)(const SphereEmissionVolumeModuleConcrete &);

SphereEmissionVolumeModuleConcreteAssign g_sphereEmissionVolumeModuleConcreteAssign = &SphereEmissionVolumeModuleConcrete::operator=;

typedef BoxEmissionVolumeModuleConcrete &(BoxEmissionVolumeModuleConcrete::*BoxEmissionVolumeModuleConcreteAssign)(const BoxEmissionVolumeModuleConcrete &);

BoxEmissionVolumeModuleConcreteAssign g_boxEmissionVolumeModuleConcreteAssign = &BoxEmissionVolumeModuleConcrete::operator=;

typedef LineEmissionVolumeModuleConcrete &(LineEmissionVolumeModuleConcrete::*LineEmissionVolumeModuleConcreteAssign)(const LineEmissionVolumeModuleConcrete &);

LineEmissionVolumeModuleConcreteAssign g_lineEmissionVolumeModuleConcreteAssign = &LineEmissionVolumeModuleConcrete::operator=;

typedef CylinderEmissionVolumeModuleConcrete &(CylinderEmissionVolumeModuleConcrete::*CylinderEmissionVolumeModuleConcreteAssign)(const CylinderEmissionVolumeModuleConcrete &);

CylinderEmissionVolumeModuleConcreteAssign g_cylinderEmissionVolumeModuleConcreteAssign = &CylinderEmissionVolumeModuleConcrete::operator=;

typedef OrthoEmissionVelocityModuleConcrete &(OrthoEmissionVelocityModuleConcrete::*OrthoEmissionVelocityModuleConcreteAssign)(const OrthoEmissionVelocityModuleConcrete &);

OrthoEmissionVelocityModuleConcreteAssign g_orthoEmissionVelocityModuleConcreteAssign = &OrthoEmissionVelocityModuleConcrete::operator=;

typedef LightningDrawModuleConcrete &(LightningDrawModuleConcrete::*LightningDrawModuleConcreteAssign)(const LightningDrawModuleConcrete &);

LightningDrawModuleConcreteAssign g_lightningDrawModuleConcreteAssign = &LightningDrawModuleConcrete::operator=;

typedef TerrainFireEmissionModuleConcrete &(TerrainFireEmissionModuleConcrete::*TerrainFireEmissionModuleConcreteAssign)(const TerrainFireEmissionModuleConcrete &);

TerrainFireEmissionModuleConcreteAssign g_terrainFireEmissionModuleConcreteAssign = &TerrainFireEmissionModuleConcrete::operator=;

typedef LightningEmissionModuleConcrete &(LightningEmissionModuleConcrete::*LightningEmissionModuleConcreteAssign)(const LightningEmissionModuleConcrete &);

LightningEmissionModuleConcreteAssign g_lightningEmissionModuleConcreteAssign = &LightningEmissionModuleConcrete::operator=;

typedef RenderObjectUpdateModuleConcrete &(RenderObjectUpdateModuleConcrete::*RenderObjectUpdateModuleConcreteAssign)(const RenderObjectUpdateModuleConcrete &);

RenderObjectUpdateModuleConcreteAssign g_renderObjectUpdateModuleConcreteAssign = &RenderObjectUpdateModuleConcrete::operator=;

typedef RenderObjectDrawModuleConcrete &(RenderObjectDrawModuleConcrete::*RenderObjectDrawModuleConcreteAssign)(const RenderObjectDrawModuleConcrete &);

RenderObjectDrawModuleConcreteAssign g_renderObjectDrawModuleConcreteAssign = &RenderObjectDrawModuleConcrete::operator=;

typedef GpuDrawModuleConcrete &(GpuDrawModuleConcrete::*GpuDrawModuleConcreteAssign)(const GpuDrawModuleConcrete &);

GpuDrawModuleConcreteAssign g_gpuDrawModuleConcreteAssign = &GpuDrawModuleConcrete::operator=;

typedef DefaultConcrete0 &(DefaultConcrete0::*DefaultConcrete0Assign)(const DefaultConcrete0 &);

DefaultConcrete0Assign g_defaultConcrete0Assign = &DefaultConcrete0::operator=;

typedef DefaultConcrete1 &(DefaultConcrete1::*DefaultConcrete1Assign)(const DefaultConcrete1 &);

DefaultConcrete1Assign g_defaultConcrete1Assign = &DefaultConcrete1::operator=;

typedef DefaultConcrete2 &(DefaultConcrete2::*DefaultConcrete2Assign)(const DefaultConcrete2 &);

DefaultConcrete2Assign g_defaultConcrete2Assign = &DefaultConcrete2::operator=;

typedef DefaultConcrete3 &(DefaultConcrete3::*DefaultConcrete3Assign)(const DefaultConcrete3 &);

DefaultConcrete3Assign g_defaultConcrete3Assign = &DefaultConcrete3::operator=;

typedef RenderObjectUpdateModuleNamedConcrete &(RenderObjectUpdateModuleNamedConcrete::*RenderObjectUpdateModuleNamedConcreteAssign)(const RenderObjectUpdateModuleNamedConcrete &);

RenderObjectUpdateModuleNamedConcreteAssign g_renderObjectUpdateModuleNamedConcreteAssign = &RenderObjectUpdateModuleNamedConcrete::operator=;

typedef LifeEventModuleNamedConcrete &(LifeEventModuleNamedConcrete::*LifeEventModuleNamedConcreteAssign)(const LifeEventModuleNamedConcrete &);

LifeEventModuleNamedConcreteAssign g_lifeEventModuleNamedConcreteAssign = &LifeEventModuleNamedConcrete::operator=;

typedef TerrainCollisionModuleNamedConcrete &(TerrainCollisionModuleNamedConcrete::*TerrainCollisionModuleNamedConcreteAssign)(const TerrainCollisionModuleNamedConcrete &);

TerrainCollisionModuleNamedConcreteAssign g_terrainCollisionModuleNamedConcreteAssign = &TerrainCollisionModuleNamedConcrete::operator=;

}
