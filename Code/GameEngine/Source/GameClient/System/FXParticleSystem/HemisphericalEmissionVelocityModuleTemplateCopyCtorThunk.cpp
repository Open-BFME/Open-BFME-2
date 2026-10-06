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

protected:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// HemisphericalEmissionVelocityModuleTemplate_cvtbl0: matched references place it at VA 0xc1bc60 (retail .rdata value 62).
extern "C" char HemisphericalEmissionVelocityModuleTemplate_cvtbl0 = 62;
extern "C" char HemisphericalEmissionVelocityModuleTemplate_cvtbl4;
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
	self[1] = &HemisphericalEmissionVelocityModuleTemplate_cvtbl4;
	self[2] = &HemisphericalEmissionVelocityModuleTemplate_csub_vtbl;
}
}
// _HemisphericalEmissionVelocityModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_HemisphericalEmissionVelocityModuleTemplate_cvtbl4=?vftable_0112B89C@@3HA")
