// cl: /O1 /GX- /arch:SSE2
// BFME1 DefaultModuleTemplate<1> empty triple-vtbl dtor transferred to BFME2.
// Like its BFME1 model it stands apart from the wrapper TU: the template is
// redeclared here with no bases, so the destructor is three null-guarded
// vtable stores and nothing else - the 41 bytes retail folds every
// module-template destructor onto. Named templates whose destructors share
// the fold ride in the same TU under the same standalone shape.

extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[];  // folded, 35 classes

extern "C" const void *const __identifier("??_7Snapshot@@6B@")[];  // folded, 23 classes

extern "C" const void *const __identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int CATEGORY>
class DefaultModuleTemplate
{
};

template <>
class __declspec(novtable) DefaultModuleTemplate<1>
{
public:
    virtual ~DefaultModuleTemplate();
};

inline DefaultModuleTemplate<1>::~DefaultModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

template <>
class __declspec(novtable) DefaultModuleTemplate<2>
{
public:
    virtual ~DefaultModuleTemplate();
};

inline DefaultModuleTemplate<2>::~DefaultModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

template <>
class __declspec(novtable) DefaultModuleTemplate<3>
{
public:
    virtual ~DefaultModuleTemplate();
};

inline DefaultModuleTemplate<3>::~DefaultModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

template <>
class __declspec(novtable) DefaultModuleTemplate<0>
{
public:
    virtual ~DefaultModuleTemplate();
};

inline DefaultModuleTemplate<0>::~DefaultModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

template <>
class __declspec(novtable) DefaultModuleTemplate<6>
{
public:
    virtual ~DefaultModuleTemplate();
};

inline DefaultModuleTemplate<6>::~DefaultModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

// Category 7 delegates: its template destructor is a bare tail call into the
// category template destructor, the five bytes retail folds with the concrete
// wrappers rather than the forty-one of its siblings.
template <int CATEGORY>
class CategoryModuleTemplate
{
public:
    virtual ~CategoryModuleTemplate();
    CategoryModuleTemplate &operator=(const CategoryModuleTemplate &that);
};

template <>
class DefaultModuleTemplate<7> : public CategoryModuleTemplate<7>
{
};

// The default wrapper of category 7. Its assignment (retail export 566) and
// the template's own (export 603) are the same eighteen bytes at 0x003A8CF1,
// next to the destructor fold: a call into the category base's assignment.
// DefaultModuleTemplate<7> adds no members, so its assignment is the implicit
// one; the wrapper's assignment inlines it, and MSVC emits that implicit
// definition beside it.
template <int CATEGORY>
class DefaultModuleTag
{
public:
    typedef DefaultModuleTemplate<CATEGORY> TemplateType;
};

template <class TAG>
class ConcreteModuleTemplate : public TAG::TemplateType
{
public:
    ConcreteModuleTemplate<TAG> &operator=(const ConcreteModuleTemplate<TAG> &that);
};

template <class TAG>
ConcreteModuleTemplate<TAG> &ConcreteModuleTemplate<TAG>::operator=(const ConcreteModuleTemplate<TAG> &that)
{
    TAG::TemplateType::operator=(that);
    return *this;
}

template class ConcreteModuleTemplate<DefaultModuleTag<7> >;

// The named templates below repeat the same standalone triple-store shape,
// one class each, for the destructors retail folds onto the same address.
class __declspec(novtable) CylindricalEmissionVelocityModuleTemplate
{
public:
    virtual ~CylindricalEmissionVelocityModuleTemplate();
};

inline CylindricalEmissionVelocityModuleTemplate::~CylindricalEmissionVelocityModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

class __declspec(novtable) OrthoEmissionVelocityModuleTemplate
{
public:
    virtual ~OrthoEmissionVelocityModuleTemplate();
};

inline OrthoEmissionVelocityModuleTemplate::~OrthoEmissionVelocityModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

class __declspec(novtable) LightningDrawModuleTemplate
{
public:
    virtual ~LightningDrawModuleTemplate();
};

inline LightningDrawModuleTemplate::~LightningDrawModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

class __declspec(novtable) LightningEmissionModuleTemplate
{
public:
    virtual ~LightningEmissionModuleTemplate();
};

inline LightningEmissionModuleTemplate::~LightningEmissionModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

class __declspec(novtable) RenderObjectUpdateModuleTemplate
{
public:
    virtual ~RenderObjectUpdateModuleTemplate();
};

inline RenderObjectUpdateModuleTemplate::~RenderObjectUpdateModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

class __declspec(novtable) TerrainFireEmissionModuleTemplate
{
public:
    virtual ~TerrainFireEmissionModuleTemplate();
};

inline TerrainFireEmissionModuleTemplate::~TerrainFireEmissionModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

class __declspec(novtable) OutwardEmissionVelocityModuleTemplate
{
public:
    virtual ~OutwardEmissionVelocityModuleTemplate();
};

inline OutwardEmissionVelocityModuleTemplate::~OutwardEmissionVelocityModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)__identifier("??_7Snapshot@@6B@"));

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@"));
}

}

// These header-inline destructors retain their row copies through this anchor.
// The anchor is absent from retail.
#pragma inline_depth(0)
// ?_bfmeFXParticleSystemDefaultTemplateDtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeFXParticleSystemDefaultTemplateDtorInlineAnchor()
{
    static_cast<FXParticleSystem::DefaultModuleTemplate<7> *>(0)->FXParticleSystem::DefaultModuleTemplate<7>::~DefaultModuleTemplate();
    static_cast<FXParticleSystem::DefaultModuleTemplate<0> *>(0)->FXParticleSystem::DefaultModuleTemplate<0>::~DefaultModuleTemplate();
    static_cast<FXParticleSystem::DefaultModuleTemplate<1> *>(0)->FXParticleSystem::DefaultModuleTemplate<1>::~DefaultModuleTemplate();
    static_cast<FXParticleSystem::DefaultModuleTemplate<2> *>(0)->FXParticleSystem::DefaultModuleTemplate<2>::~DefaultModuleTemplate();
    static_cast<FXParticleSystem::DefaultModuleTemplate<3> *>(0)->FXParticleSystem::DefaultModuleTemplate<3>::~DefaultModuleTemplate();
    static_cast<FXParticleSystem::DefaultModuleTemplate<6> *>(0)->FXParticleSystem::DefaultModuleTemplate<6>::~DefaultModuleTemplate();
    static_cast<FXParticleSystem::CylindricalEmissionVelocityModuleTemplate *>(0)->FXParticleSystem::CylindricalEmissionVelocityModuleTemplate::~CylindricalEmissionVelocityModuleTemplate();
    static_cast<FXParticleSystem::OrthoEmissionVelocityModuleTemplate *>(0)->FXParticleSystem::OrthoEmissionVelocityModuleTemplate::~OrthoEmissionVelocityModuleTemplate();
    static_cast<FXParticleSystem::LightningDrawModuleTemplate *>(0)->FXParticleSystem::LightningDrawModuleTemplate::~LightningDrawModuleTemplate();
    static_cast<FXParticleSystem::LightningEmissionModuleTemplate *>(0)->FXParticleSystem::LightningEmissionModuleTemplate::~LightningEmissionModuleTemplate();
    static_cast<FXParticleSystem::RenderObjectUpdateModuleTemplate *>(0)->FXParticleSystem::RenderObjectUpdateModuleTemplate::~RenderObjectUpdateModuleTemplate();
    static_cast<FXParticleSystem::TerrainFireEmissionModuleTemplate *>(0)->FXParticleSystem::TerrainFireEmissionModuleTemplate::~TerrainFireEmissionModuleTemplate();
    static_cast<FXParticleSystem::OutwardEmissionVelocityModuleTemplate *>(0)->FXParticleSystem::OutwardEmissionVelocityModuleTemplate::~OutwardEmissionVelocityModuleTemplate();
}
#pragma inline_depth()
