// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: StreakDrawModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class StreakDrawModuleTemplateBaseCopyShim
{
public:
	void construct_from(const void *src);
};

class StreakDrawModuleTemplateSubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char DefaultModuleTemplate05_vtbl0;
extern "C" char StreakDrawModuleTemplate_cvtbl4;
// StreakDrawModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bd20 (retail .rdata value 109).
extern "C" char StreakDrawModuleTemplate_csub_vtbl = 109;

class StreakDrawModuleTemplate
{
public:
	StreakDrawModuleTemplate(const StreakDrawModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0StreakDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
StreakDrawModuleTemplate::StreakDrawModuleTemplate(
	const StreakDrawModuleTemplate &that)
{
	const void *src = &that;
	((StreakDrawModuleTemplateBaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	StreakDrawModuleTemplateSubCopyShim *sub =
		(StreakDrawModuleTemplateSubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &StreakDrawModuleTemplate_csub_vtbl;
	m_v0 = &DefaultModuleTemplate05_vtbl0;
	m_v4 = &StreakDrawModuleTemplate_cvtbl4;
}
}
// _StreakDrawModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_StreakDrawModuleTemplate_cvtbl4=?vftable_0112B89C@@3HA")
