// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: ButterflyDrawModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};

class ButterflyDrawModuleInfo
{
public:
	ButterflyDrawModuleInfo(const ButterflyDrawModuleInfo &that);
	virtual void dummy();
};

extern "C" char ButterflyDrawModuleTemplate_cvtbl0;
extern "C" char __identifier("?vftable_0112B89C@@3HA");
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
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	ButterflyDrawModuleInfo *sub = (ButterflyDrawModuleInfo *)((char *)this + 8);
	sub->ButterflyDrawModuleInfo::ButterflyDrawModuleInfo(*(const ButterflyDrawModuleInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &ButterflyDrawModuleTemplate_csub_vtbl;
	m_v0 = &ButterflyDrawModuleTemplate_cvtbl0;
	m_v4 = &__identifier("?vftable_0112B89C@@3HA");
}
}
// _ButterflyDrawModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
// _ButterflyDrawModuleTemplate_cvtbl0: the global at VA 0xc1bd60 is DefaultModuleTemplate<6>'s +0 table,
// which DefaultModuleTemplate.h now emits under its real name.
#pragma comment(linker, "/alternatename:_ButterflyDrawModuleTemplate_cvtbl0=??_7?$DefaultModuleTemplate@$05@FXParticleSystem@@6BModuleTemplate@1@@")
