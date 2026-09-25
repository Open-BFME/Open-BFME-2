// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: HemisphericalEmissionVelocityModuleTemplate copy ctor
// Retail: reuses the Spherical copy at 0x3A734E, then installs its own
// triple vtable (outer dual + sub).

namespace FXParticleSystem
{

class SphericalEmissionVelocityModuleTemplate
{
public:
	SphericalEmissionVelocityModuleTemplate(const SphericalEmissionVelocityModuleTemplate &that);

protected:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

extern "C" char HemisphericalEmissionVelocityModuleTemplate_cvtbl0;
extern "C" char HemisphericalEmissionVelocityModuleTemplate_cvtbl4;
extern "C" char HemisphericalEmissionVelocityModuleTemplate_csub_vtbl;

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
	self[1] = &HemisphericalEmissionVelocityModuleTemplate_cvtbl4;
	self[2] = &HemisphericalEmissionVelocityModuleTemplate_csub_vtbl;
}
}
