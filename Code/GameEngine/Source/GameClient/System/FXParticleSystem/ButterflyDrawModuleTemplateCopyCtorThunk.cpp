// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: ButterflyDrawModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class ButterflyDrawModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class ButterflyDrawModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char ButterflyDrawModuleTemplate_cvtbl0;
extern "C" char ButterflyDrawModuleTemplate_cvtbl4;
// ButterflyDrawModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bd70 (retail .rdata value 109).
extern "C" char ButterflyDrawModuleTemplate_csub_vtbl = 109;

class ButterflyDrawModuleTemplate
{
public:
	ButterflyDrawModuleTemplate(const ButterflyDrawModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0ButterflyDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
ButterflyDrawModuleTemplate::ButterflyDrawModuleTemplate(
	const ButterflyDrawModuleTemplate &that)
{
	const void *src = &that;
	((ButterflyDrawModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	ButterflyDrawModuleTemplateSubCopyShim *sub =
		(ButterflyDrawModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &ButterflyDrawModuleTemplate_csub_vtbl;
	m_v0 = &ButterflyDrawModuleTemplate_cvtbl0;
	m_v4 = &ButterflyDrawModuleTemplate_cvtbl4;
}
}
// _ButterflyDrawModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_ButterflyDrawModuleTemplate_cvtbl4=?vftable_0112B89C@@3HA")
// _ButterflyDrawModuleTemplate_cvtbl0: the global at VA 0xc1bd60 is _DefaultModuleTemplate05_vtbl0.
#pragma comment(linker, "/alternatename:_ButterflyDrawModuleTemplate_cvtbl0=_DefaultModuleTemplate05_vtbl0")
