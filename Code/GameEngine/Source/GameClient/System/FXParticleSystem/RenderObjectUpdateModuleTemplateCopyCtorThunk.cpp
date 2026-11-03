// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: RenderObjectUpdateModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

#include "../../../../Include/GameClient/RenderObjectUpdateModuleInfo.h"
namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};


// RenderObjectUpdateModuleTemplate_cvtbl0: matched references place it at VA 0xc1bdc0 (retail .rdata value 96).
extern "C" char RenderObjectUpdateModuleTemplate_cvtbl0 = 96;
extern "C" char __identifier("?vftable_0112B89C@@3HA");
// RenderObjectUpdateModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bdd0 (retail .rdata value 13).
extern "C" char RenderObjectUpdateModuleTemplate_csub_vtbl = 13;

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
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	RenderObjectUpdateModuleInfo *sub = (RenderObjectUpdateModuleInfo *)((char *)this + 8);
	sub->RenderObjectUpdateModuleInfo::RenderObjectUpdateModuleInfo(*(const RenderObjectUpdateModuleInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &RenderObjectUpdateModuleTemplate_csub_vtbl;
	m_v0 = &RenderObjectUpdateModuleTemplate_cvtbl0;
	m_v4 = &__identifier("?vftable_0112B89C@@3HA");
}
}
// _RenderObjectUpdateModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
