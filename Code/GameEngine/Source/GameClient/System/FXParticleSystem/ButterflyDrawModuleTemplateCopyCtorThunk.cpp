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
extern "C" char ButterflyDrawModuleTemplate_csub_vtbl;

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
