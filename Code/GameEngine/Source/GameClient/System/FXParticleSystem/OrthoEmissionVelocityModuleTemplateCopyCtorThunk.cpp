// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: OrthoEmissionVelocityModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class OrthoEmissionVelocityModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class OrthoEmissionVelocityModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

// OrthoEmissionVelocityModuleTemplate_cvtbl0: matched references place it at VA 0xc1bc10 (retail .rdata value -44).
extern "C" char OrthoEmissionVelocityModuleTemplate_cvtbl0 = -44;
extern "C" char OrthoEmissionVelocityModuleTemplate_cvtbl4;
// OrthoEmissionVelocityModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bc20 (retail .rdata value -35).
extern "C" char OrthoEmissionVelocityModuleTemplate_csub_vtbl = -35;

class OrthoEmissionVelocityModuleTemplate
{
public:
	OrthoEmissionVelocityModuleTemplate(const OrthoEmissionVelocityModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
OrthoEmissionVelocityModuleTemplate::OrthoEmissionVelocityModuleTemplate(
	const OrthoEmissionVelocityModuleTemplate &that)
{
	const void *src = &that;
	((OrthoEmissionVelocityModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	OrthoEmissionVelocityModuleTemplateSubCopyShim *sub =
		(OrthoEmissionVelocityModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &OrthoEmissionVelocityModuleTemplate_csub_vtbl;
	m_v0 = &OrthoEmissionVelocityModuleTemplate_cvtbl0;
	m_v4 = &OrthoEmissionVelocityModuleTemplate_cvtbl4;
}
}
// _OrthoEmissionVelocityModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_OrthoEmissionVelocityModuleTemplate_cvtbl4=?vftable_0112B89C@@3HA")
