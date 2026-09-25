// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: CylindricalEmissionVelocityModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class CylindricalEmissionVelocityModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class CylindricalEmissionVelocityModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char CylindricalEmissionVelocityModuleTemplate_cvtbl0;
extern "C" char CylindricalEmissionVelocityModuleTemplate_cvtbl4;
extern "C" char CylindricalEmissionVelocityModuleTemplate_csub_vtbl;

class CylindricalEmissionVelocityModuleTemplate
{
public:
	CylindricalEmissionVelocityModuleTemplate(const CylindricalEmissionVelocityModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
CylindricalEmissionVelocityModuleTemplate::CylindricalEmissionVelocityModuleTemplate(
	const CylindricalEmissionVelocityModuleTemplate &that)
{
	const void *src = &that;
	((CylindricalEmissionVelocityModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	CylindricalEmissionVelocityModuleTemplateSubCopyShim *sub =
		(CylindricalEmissionVelocityModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &CylindricalEmissionVelocityModuleTemplate_csub_vtbl;
	m_v0 = &CylindricalEmissionVelocityModuleTemplate_cvtbl0;
	m_v4 = &CylindricalEmissionVelocityModuleTemplate_cvtbl4;
}
}
