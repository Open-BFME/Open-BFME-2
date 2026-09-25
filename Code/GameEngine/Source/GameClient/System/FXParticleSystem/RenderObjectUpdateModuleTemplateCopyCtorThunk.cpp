// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Open-BFME5: RenderObjectUpdateModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class RenderObjectUpdateModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class RenderObjectUpdateModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char RenderObjectUpdateModuleTemplate_cvtbl0;
extern "C" char RenderObjectUpdateModuleTemplate_cvtbl4;
extern "C" char RenderObjectUpdateModuleTemplate_csub_vtbl;

class RenderObjectUpdateModuleTemplate
{
public:
	RenderObjectUpdateModuleTemplate(const RenderObjectUpdateModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0RenderObjectUpdateModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
RenderObjectUpdateModuleTemplate::RenderObjectUpdateModuleTemplate(
	const RenderObjectUpdateModuleTemplate &that)
{
	const void *src = &that;
	((RenderObjectUpdateModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	RenderObjectUpdateModuleTemplateSubCopyShim *sub =
		(RenderObjectUpdateModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &RenderObjectUpdateModuleTemplate_csub_vtbl;
	m_v0 = &RenderObjectUpdateModuleTemplate_cvtbl0;
	m_v4 = &RenderObjectUpdateModuleTemplate_cvtbl4;
}
}
