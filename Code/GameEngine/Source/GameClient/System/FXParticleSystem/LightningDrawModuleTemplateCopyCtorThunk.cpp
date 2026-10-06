// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: LightningDrawModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class LightningDrawModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class LightningDrawModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

// LightningDrawModuleTemplate_cvtbl0: matched references place it at VA 0xc1bd90 (retail .rdata value -123).
extern "C" char LightningDrawModuleTemplate_cvtbl0 = -123;
extern "C" char LightningDrawModuleTemplate_cvtbl4;
// LightningDrawModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bda0 (retail .rdata value 77).
extern "C" char LightningDrawModuleTemplate_csub_vtbl = 77;

class LightningDrawModuleTemplate
{
public:
	LightningDrawModuleTemplate(const LightningDrawModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0LightningDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
LightningDrawModuleTemplate::LightningDrawModuleTemplate(
	const LightningDrawModuleTemplate &that)
{
	const void *src = &that;
	((LightningDrawModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	LightningDrawModuleTemplateSubCopyShim *sub =
		(LightningDrawModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &LightningDrawModuleTemplate_csub_vtbl;
	m_v0 = &LightningDrawModuleTemplate_cvtbl0;
	m_v4 = &LightningDrawModuleTemplate_cvtbl4;
}
}
// _LightningDrawModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_LightningDrawModuleTemplate_cvtbl4=?vftable_0112B89C@@3HA")
