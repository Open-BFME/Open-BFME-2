// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: LightningDrawModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

#include "../../../../Include/GameClient/LightningDrawModuleInfo.h"
namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};


// LightningDrawModuleTemplate_cvtbl0: matched references place it at VA 0xc1bd90 (retail .rdata value -123).
extern "C" char LightningDrawModuleTemplate_cvtbl0 = -123;
extern "C" char __identifier("?vftable_0112B89C@@3HA");
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
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	LightningDrawModuleInfo *sub = (LightningDrawModuleInfo *)((char *)this + 8);
	sub->LightningDrawModuleInfo::LightningDrawModuleInfo(*(const LightningDrawModuleInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &LightningDrawModuleTemplate_csub_vtbl;
	m_v0 = &LightningDrawModuleTemplate_cvtbl0;
	m_v4 = &__identifier("?vftable_0112B89C@@3HA");
}
}
// _LightningDrawModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
