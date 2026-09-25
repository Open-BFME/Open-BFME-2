// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: OutwardEmissionVelocityModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class OutwardEmissionVelocityModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class OutwardEmissionVelocityModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char OutwardEmissionVelocityModuleTemplate_cvtbl0;
extern "C" char OutwardEmissionVelocityModuleTemplate_cvtbl4;
extern "C" char OutwardEmissionVelocityModuleTemplate_csub_vtbl;

class OutwardEmissionVelocityModuleTemplate
{
public:
	OutwardEmissionVelocityModuleTemplate(const OutwardEmissionVelocityModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0OutwardEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
OutwardEmissionVelocityModuleTemplate::OutwardEmissionVelocityModuleTemplate(
	const OutwardEmissionVelocityModuleTemplate &that)
{
	const void *src = &that;
	((OutwardEmissionVelocityModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	OutwardEmissionVelocityModuleTemplateSubCopyShim *sub =
		(OutwardEmissionVelocityModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &OutwardEmissionVelocityModuleTemplate_csub_vtbl;
	m_v0 = &OutwardEmissionVelocityModuleTemplate_cvtbl0;
	m_v4 = &OutwardEmissionVelocityModuleTemplate_cvtbl4;
}
}
