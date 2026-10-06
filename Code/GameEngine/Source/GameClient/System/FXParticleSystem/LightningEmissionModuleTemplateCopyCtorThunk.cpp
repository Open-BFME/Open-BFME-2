// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: LightningEmissionModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class LightningEmissionModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class LightningEmissionModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

// LightningEmissionModuleTemplate_cvtbl0: matched references place it at VA 0xc1bbb0 (retail .rdata value 17).
extern "C" char LightningEmissionModuleTemplate_cvtbl0 = 17;
extern "C" char LightningEmissionModuleTemplate_cvtbl4;
// LightningEmissionModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bbc0 (retail .rdata value 53).
extern "C" char LightningEmissionModuleTemplate_csub_vtbl = 53;

class LightningEmissionModuleTemplate
{
public:
	LightningEmissionModuleTemplate(const LightningEmissionModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0LightningEmissionModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
LightningEmissionModuleTemplate::LightningEmissionModuleTemplate(
	const LightningEmissionModuleTemplate &that)
{
	const void *src = &that;
	((LightningEmissionModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	LightningEmissionModuleTemplateSubCopyShim *sub =
		(LightningEmissionModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &LightningEmissionModuleTemplate_csub_vtbl;
	m_v0 = &LightningEmissionModuleTemplate_cvtbl0;
	m_v4 = &LightningEmissionModuleTemplate_cvtbl4;
}
}
// _LightningEmissionModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_LightningEmissionModuleTemplate_cvtbl4=?vftable_0112B89C@@3HA")
