// cl: /O1 /GX- /arch:SSE2
// BFME1 DefaultModuleTemplate<1> empty triple-vtbl dtor transferred to BFME2.
// Like its BFME1 model it stands apart from the wrapper TU: the template is
// redeclared here with no bases, so the destructor is three null-guarded
// vtable stores and nothing else - the 41 bytes retail folds every
// module-template destructor onto. Named templates whose destructors share
// the fold ride in the same TU under the same standalone shape.

extern "C" const void *const vtbl_00C1C780[];  // folded, 35 classes; via ??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C1C780=??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")

extern "C" const void *const vtbl_00BBB554[];  // folded, 23 classes; via ??_7BfmeBaseVUQ@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@")

extern "C" const void *const vtbl_00BBB52C[];  // ??_7ModuleTemplate@FXParticleSystem@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBB52C=??_7ModuleTemplate@FXParticleSystem@@6B@")

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
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
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
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
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
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
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
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
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
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
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
public:
    DefaultModuleTemplate<7> &operator=(const DefaultModuleTemplate<7> &that);
};

// A file-scope instance forces the implicit destructor out; it is what the
// ledger compares.
DefaultModuleTemplate<7> g_defaultModuleTemplate7;

// The assignment hands straight through to the category base, the eighteen
// bytes retail keeps next to the destructor fold.
DefaultModuleTemplate<7> &DefaultModuleTemplate<7>::operator=(
    const DefaultModuleTemplate<7> &that)
{
    CategoryModuleTemplate<7>::operator=(that);
    return *this;
}

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
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
}

class __declspec(novtable) OrthoEmissionVelocityModuleTemplate
{
public:
    virtual ~OrthoEmissionVelocityModuleTemplate();
};

inline OrthoEmissionVelocityModuleTemplate::~OrthoEmissionVelocityModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
}

class __declspec(novtable) LightningDrawModuleTemplate
{
public:
    virtual ~LightningDrawModuleTemplate();
};

inline LightningDrawModuleTemplate::~LightningDrawModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
}

class __declspec(novtable) LightningEmissionModuleTemplate
{
public:
    virtual ~LightningEmissionModuleTemplate();
};

inline LightningEmissionModuleTemplate::~LightningEmissionModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
}

class __declspec(novtable) RenderObjectUpdateModuleTemplate
{
public:
    virtual ~RenderObjectUpdateModuleTemplate();
};

inline RenderObjectUpdateModuleTemplate::~RenderObjectUpdateModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
}

class __declspec(novtable) TerrainFireEmissionModuleTemplate
{
public:
    virtual ~TerrainFireEmissionModuleTemplate();
};

inline TerrainFireEmissionModuleTemplate::~TerrainFireEmissionModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
}

class __declspec(novtable) OutwardEmissionVelocityModuleTemplate
{
public:
    virtual ~OutwardEmissionVelocityModuleTemplate();
};

inline OutwardEmissionVelocityModuleTemplate::~OutwardEmissionVelocityModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = ((unsigned int)vtbl_00BBB554);

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = ((unsigned int)vtbl_00C1C780);
    *(volatile unsigned int *)this = ((unsigned int)vtbl_00BBB52C);
}

}

// These twelve destructors are header inlines in copier units. The anchor retains
// this unit's row copies; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeFXParticleSystemDefaultTemplateDtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeFXParticleSystemDefaultTemplateDtorInlineAnchor()
{
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
