// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: HemisphericalEmissionVelocityModuleTemplate copy ctor
// Retail: reuses the Spherical copy at 0x3A734E, then installs its own
// triple vtable (outer dual + sub).

namespace FXParticleSystem
{

class SphericalEmissionVelocityModuleTemplate
{
public:
	SphericalEmissionVelocityModuleTemplate(const SphericalEmissionVelocityModuleTemplate &that);
	SphericalEmissionVelocityModuleTemplate &operator=(const SphericalEmissionVelocityModuleTemplate &that);

protected:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// HemisphericalEmissionVelocityModuleTemplate_cvtbl0: matched references place it at VA 0xc1bc60 (retail .rdata value 62).
extern "C" char HemisphericalEmissionVelocityModuleTemplate_cvtbl0 = 62;
extern "C" char __identifier("?vftable_0112B89C@@3HA");
// HemisphericalEmissionVelocityModuleTemplate_csub_vtbl: matched references place it at VA 0xc1c00c (retail .rdata value 85).
extern "C" char HemisphericalEmissionVelocityModuleTemplate_csub_vtbl = 85;

class HemisphericalEmissionVelocityModuleTemplate : public SphericalEmissionVelocityModuleTemplate
{
public:
	HemisphericalEmissionVelocityModuleTemplate(const HemisphericalEmissionVelocityModuleTemplate &that);
};

// ??0HemisphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
HemisphericalEmissionVelocityModuleTemplate::HemisphericalEmissionVelocityModuleTemplate(
	const HemisphericalEmissionVelocityModuleTemplate &that)
	: SphericalEmissionVelocityModuleTemplate((const SphericalEmissionVelocityModuleTemplate &)that)
{
	void **self = (void **)this;
	self[0] = &HemisphericalEmissionVelocityModuleTemplate_cvtbl0;
	self[1] = &__identifier("?vftable_0112B89C@@3HA");
	self[2] = &HemisphericalEmissionVelocityModuleTemplate_csub_vtbl;
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
// _HemisphericalEmissionVelocityModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
