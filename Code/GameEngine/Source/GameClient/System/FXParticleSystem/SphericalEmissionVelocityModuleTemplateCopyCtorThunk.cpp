// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: SphericalEmissionVelocityModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class SphericalEmissionVelocityModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class SphericalEmissionVelocityModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char SphericalEmissionVelocityModuleTemplate_cvtbl0;
extern "C" char SphericalEmissionVelocityModuleTemplate_cvtbl4;
extern "C" char SphericalEmissionVelocityModuleTemplate_csub_vtbl;

class SphericalEmissionVelocityModuleTemplate
{
public:
	SphericalEmissionVelocityModuleTemplate(const SphericalEmissionVelocityModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
SphericalEmissionVelocityModuleTemplate::SphericalEmissionVelocityModuleTemplate(
	const SphericalEmissionVelocityModuleTemplate &that)
{
	const void *src = &that;
	((SphericalEmissionVelocityModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	SphericalEmissionVelocityModuleTemplateSubCopyShim *sub =
		(SphericalEmissionVelocityModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &SphericalEmissionVelocityModuleTemplate_csub_vtbl;
	m_v0 = &SphericalEmissionVelocityModuleTemplate_cvtbl0;
	m_v4 = &SphericalEmissionVelocityModuleTemplate_cvtbl4;
}
}
