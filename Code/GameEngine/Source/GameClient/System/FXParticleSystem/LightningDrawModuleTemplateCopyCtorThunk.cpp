// cl: /DNDEBUG /MD /GX- /O1 /Ob2

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

extern "C" char LightningDrawModuleTemplate_cvtbl0;
extern "C" char LightningDrawModuleTemplate_cvtbl4;
extern "C" char LightningDrawModuleTemplate_csub_vtbl;

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
