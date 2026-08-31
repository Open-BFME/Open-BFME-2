// cl: /O1 /GX- /arch:SSE2

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

template <class TAG>
typename TAG::TemplateType *ConcreteModuleTemplate<TAG>::clone() const
{
    return new ConcreteModuleTemplate<TAG>(*this);
}

// The module class that builds them. createTemplate is one operator new for the
// wrapper's size and a tail jump into its default constructor.
class INI;

template <class TAG>
class ConcreteModuleClass
{
public:
    virtual typename TAG::TemplateType *createTemplate() const;
};

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
    MOD##ClassConcrete g_##MOD##ClassConcrete;

// The point volume's tag is a plain struct rather than a ModuleTag
// instantiation - the U rather than V in the decorated name is what says so.
struct PointEmissionVolumeModuleTag
{
    typedef PointEmissionVolumeModuleTemplate TemplateType;
};

typedef ConcreteModuleTemplate<PointEmissionVolumeModuleTag> PointEmissionVolumeModuleConcrete;
typedef ConcreteModuleClass<PointEmissionVolumeModuleTag> PointEmissionVolumeModuleClassConcrete;

PointEmissionVolumeModuleConcrete g_pointEmissionVolumeModuleConcrete;
PointEmissionVolumeModuleClassConcrete g_pointEmissionVolumeModuleClassConcrete;

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
struct OrthoEmissionVelocityModuleTag
{
    typedef OrthoEmissionVelocityModuleTemplate TemplateType;
};

typedef ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> OrthoEmissionVelocityModuleConcrete;
typedef ConcreteModuleClass<OrthoEmissionVelocityModuleTag>
    OrthoEmissionVelocityModuleClassConcrete;

OrthoEmissionVelocityModuleConcrete g_orthoEmissionVelocityModuleConcrete;
OrthoEmissionVelocityModuleClassConcrete g_orthoEmissionVelocityModuleClassConcrete;

}
