// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: HemisphericalEmissionVelocityModuleTemplate copy ctor
// Retail: reuses the Spherical copy at 0x3A734E, then installs its own
// triple vtable (outer dual + sub).

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/SphericalEmissionVelocityInfo.h"

namespace FXParticleSystem
{

class ModuleTemplate
{
public:
    ModuleTemplate();
    ModuleTemplate(const ModuleTemplate &that);
    virtual ~ModuleTemplate();
};

// Retail's nested category shape (LINK-584).
template <int CATEGORY_ARG>
class CategoryModuleInfo
{
public:
    virtual void v1() = 0;

protected:
    ~CategoryModuleInfo();
};

template <int CATEGORY_ARG>
class CategoryModuleTemplateBase : public ModuleTemplate, public CategoryModuleInfo<CATEGORY_ARG>
{
public:
    CategoryModuleTemplateBase();
    CategoryModuleTemplateBase(const CategoryModuleTemplateBase<CATEGORY_ARG> &that);
    virtual ~CategoryModuleTemplateBase();
};

class SphericalEmissionVelocityModuleTemplate : public CategoryModuleTemplateBase<4>,
    public SphericalEmissionVelocityInfo
{
public:
    SphericalEmissionVelocityModuleTemplate();
    SphericalEmissionVelocityModuleTemplate(const SphericalEmissionVelocityModuleTemplate &that);
    virtual ~SphericalEmissionVelocityModuleTemplate();
    SphericalEmissionVelocityModuleTemplate &operator=(const SphericalEmissionVelocityModuleTemplate &that);
};

class HemisphericalEmissionVelocityModuleTemplate : public SphericalEmissionVelocityModuleTemplate
{
public:
    HemisphericalEmissionVelocityModuleTemplate(const HemisphericalEmissionVelocityModuleTemplate &that);
    virtual ~HemisphericalEmissionVelocityModuleTemplate();
};

// ??0HemisphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
HemisphericalEmissionVelocityModuleTemplate::HemisphericalEmissionVelocityModuleTemplate(
    const HemisphericalEmissionVelocityModuleTemplate &that)
    : SphericalEmissionVelocityModuleTemplate(that)
{
}

// Retail exports three assignments at 0x003A8EFC (18B), the call into
// Spherical's assignment 0x003A738E and `return *this`: the Spherical wrapper's
// (owner row, FXParticleSystemModules.cpp), Hemispherical's own (export 666) and
// the Hemispherical wrapper's (export 570). Hemispherical adds no members, so
// its assignment is the implicit one; the wrapper's assignment below inlines
// it, and MSVC emits that implicit definition beside it.
extern const char *const HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME;
class HemisphericalEmissionVelocityModule;
template <int CATEGORY> class DefaultParticleModule;

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
	ConcreteModuleTemplate<TAG> &operator=(const ConcreteModuleTemplate<TAG> &that);
};

template <class TAG>
ConcreteModuleTemplate<TAG> &ConcreteModuleTemplate<TAG>::operator=(const ConcreteModuleTemplate<TAG> &that)
{
	TAG::TemplateType::operator=(that);
	return *this;
}

typedef ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME,
	HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4> >
	HemisphericalEmissionVelocityModuleTag;

template class ConcreteModuleTemplate<HemisphericalEmissionVelocityModuleTag>;
}
